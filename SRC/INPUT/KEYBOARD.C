#include "INVADER.H"

#define KEY_DOWN 0xFF
#define KEY_UP   0x00

#define KEYBOARD_INTERRUPT 0x09
#define KEYBOARD_PORT      0x60
#define PIC_PORT           0x20
#define PIC_EOI            0x20

static volatile uint8_t isr_keys[KEY_MAX]; /* ISR writes here */
static uint8_t keys[KEY_MAX];               /* frame snapshot */
static uint8_t previous_keys[KEY_MAX];      /* previous frame */

static void interrupt (*OldKeyboardISR)(void);

void interrupt KeyboardISR(void)
{
    uint8_t scancode;
    uint8_t aux;

    scancode = inportb(KEYBOARD_PORT);

    /*
       Optional XT-style keyboard acknowledge.
       Usually harmless on classic DOS PCs, and useful for compatibility
       with older keyboard controller behavior.
    */
    aux = inportb(0x61);
    outportb(0x61, aux | 0x80);
    outportb(0x61, aux);

    if (scancode < 0x80)
    {
        if (scancode < KEY_MAX){
            isr_keys[scancode] = KEY_DOWN;
        }
    }
    else
    {
        scancode -= 0x80;

        if (scancode < KEY_MAX){
            isr_keys[scancode] = KEY_UP;
        }
    }

    outportb(PIC_PORT, PIC_EOI);
}

void Keyboard_Init(){

    memset((void *)isr_keys, KEY_UP, sizeof(isr_keys));
    memset((void *)keys, KEY_UP, sizeof(keys));
    memset((void *)previous_keys, KEY_UP, sizeof(previous_keys));

    OldKeyboardISR = getvect(KEYBOARD_INTERRUPT);
    setvect(KEYBOARD_INTERRUPT, KeyboardISR);
}

bool Keyboard_IsKeyDown(KEY _key){
    return isr_keys[_key] != KEY_UP;
}

bool Keyboard_IsKeyReleased(KEY _key){
    return previous_keys[_key] != KEY_UP && keys[_key] == KEY_UP;
}

bool Keyboard_IsKeyPressed(KEY _key){
    return previous_keys[_key] != KEY_UP && keys[_key] == KEY_UP;
}

void Keyboard_Update(void){
    memcpy(previous_keys, keys, sizeof(keys));

    disable();
    memcpy(keys, (const void *)isr_keys, sizeof(isr_keys));
    enable();
}

void Keyboard_DeInit() {
   setvect(KEYBOARD_INTERRUPT, OldKeyboardISR);
}
