#include "INVADER.H"

#define KEY_DOWN 0xFF
#define KEY_UP   0x00

#define KEYBOARD_INTERRUPT 0x09
#define KEYBOARD_PORT      0x60
#define PIC_PORT           0x20
#define PIC_EOI            0x20

static volatile uint8_t keys[KEY_MAX];

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
            keys[scancode] = KEY_DOWN;
        }
    }
    else
    {
        scancode -= 0x80;

        if (scancode < KEY_MAX){
            keys[scancode] = KEY_UP;
        }
    }

    outportb(PIC_PORT, PIC_EOI);
}

void Keyboard_Init(){

    memset((void *)keys, KEY_UP, sizeof(keys));

    OldKeyboardISR = getvect(KEYBOARD_INTERRUPT);
    setvect(KEYBOARD_INTERRUPT, KeyboardISR);
}


bool Keyboard_IsKeyDown(KEY _key){
    return keys[_key] != KEY_UP;
}

void Keyboard_DeInit()
{
   setvect(KEYBOARD_INTERRUPT, OldKeyboardISR);
}
