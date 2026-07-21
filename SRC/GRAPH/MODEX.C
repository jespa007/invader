#include "GRAPH\@GRAPH.H"

#define MODEX_Y_OFFSET(y) \
    (((((uint16_t)(y)) << 6) + (((uint16_t)(y)) << 4)) << g_array_offset[g_current_mode])

static uint16_t g_modex_offset_page[3][4] ={ // MAX_MODES = 3 i MAX_PAGINES = 4

 { 0, 16000, 32000, 48000 },           // MODE 1x4
 { 0, 80,    32000, 32080 },           // MODE 2x2
 { 0, 80,    160,   240   }            // MODE 4x1
};

static uint8_t g_array_offset[3] =
{
 0,
 1,
 2
};

Surface *Surface_NewModeX(
    uint16_t _segment,
    uint16_t _offset,
    uint16_t _width,
    uint16_t _height,
    uint16_t _pitch
);

static uint8_t g_current_mode = 0; // VARIABLE GLOBAL QUE COMPREN EL MODE ACTUAL DEL MODE X!.
static Surface * g_modex_surface = NULL;

bool ModeX_Init() {
 // Iniciem mode GRAFIC NORMAL ...
    asm{
         mov ah,00h  // AH = 0: Inicia el mode de Video 
        mov al,13h  // AL Mode 320 x 200 a 256 colors. 
        int 10h
    }

    // configure vga regs per plane
    Graphics_WaitVRetrace();

    VgaRegs_RegisterOut(SEQU_ADDR,0x04,0x06); //  forcem el bit CHAIN-4 a 0.
    VgaRegs_RegisterOut(CRTC_ADDR,0x17,0xe3); // ajust mode paraules.
    VgaRegs_RegisterOut(CRTC_ADDR,0x14,0x00); // ajust mode dobles paraules.


    g_current_mode = MODEX_MODE1X4;
    VgaRegs_SetOffsetRegister(40 << g_current_mode); 
    ModeX_ClearAllVRAM(0);
    ModeX_SetPage(MODEX_PAGE0);

    // init surface here
    g_modex_surface = Surface_NewModeX(
        0xA000,
        0,
        320,
        240,
        80
    );

    if (g_modex_surface == NULL){
        return false;
    }    

    return true;
}

Surface * ModeX_GetSurface(){
    return g_modex_surface;
}

void ModeX_ClearAllVRAM(uint8_t color)
{
    VgaRegs_MaskPlanes(0x0F);

    asm {
        mov ax, VIDEO_SEGMENT
        mov es, ax
        xor di, di
        mov ah, [color]
        mov al, [color]
        mov cx, 32000
        rep stosw
    }
}

void ModeX_PutPixel(uint8_t page, int16_t x, int16_t y, uint8_t color){
    uint16_t offset_segment;

    VgaRegs_MaskPlanes(1 << (x & 3));

    offset_segment =
    g_modex_offset_page[g_current_mode][page] +
    MODEX_Y_OFFSET(y) +
    ((uint16_t)x >> 2);

    asm {
        mov ax, VIDEO_SEGMENT
        mov es, ax
        mov di, [offset_segment]
        mov al, [color]
        mov es:[di], al
    }
}


bool ModeX_LoadRawImage(
    uint8_t _page
    ,int16_t _x
    ,int16_t _y
    ,char *_filename
    ,uint16_t _image_width
    ,uint16_t _image_height
){
 // Carrega imatges mes grans de 320 x 200 a una PAGINA en MODE X...
 int16_t x;
 int16_t y;
 FILE *file;

 if( (file = fopen (_filename,"rb")) == NULL) {
  return false;
 }

 for(y=_y;(!feof(file)) && y<_y+_image_height;y++){
  for(x=_x;(!feof(file)) && x<_x+_image_width;x++) {
    ModeX_PutPixel(_page, x,y,fgetc(file));
  }
 }

 fclose(file);

 return true;
}

uint8_t ModeX_GetPixel(uint8_t page, int16_t x, int16_t y) {
    uint16_t offset_segment;
    uint8_t plane;

    plane = x & 3;

    VgaRegs_RegisterOut(GRAC_ADDR, 0x04, plane);

    offset_segment =
        g_modex_offset_page[g_current_mode][page] +
        MODEX_Y_OFFSET(y) +
        ((uint16_t)x >> 2);

    asm {
        push es
        mov ax, VIDEO_SEGMENT
        mov es, ax
        mov di, [offset_segment]
        mov al, es:[di]
        pop es
    }

    return _AL;
}

void ModeX_Flip1x4(uint8_t _page,uint16_t _segment) {
     uint16_t offset_segment = g_modex_offset_page[g_current_mode][_page];
 int i,j;

    if(g_current_mode != MODEX_MODE1X4){
        return;
    }

 for(i=0;i<4;i++) {

    VgaRegs_RegisterOut(SEQU_ADDR,0x02, 0x01 << i);

    asm{
      push dx
      push ds
      push es
      mov ax,VIDEO_SEGMENT
      mov es,ax
      mov di,[offset_segment]
      mov ax,_segment
      mov ds,ax
      mov si,[i]

      mov cx,16000
    }

    buclePla: 
    asm{

     mov al,ds:[si]  // AL = DS:[SI];
     mov es:[di],al  // ES:[DI] = AL;

     add si,4
     inc di

     dec cx       // mentre (cx > 0) fer

     jnz buclePla


     pop es
     pop ds
     pop dx
     
    }
 }
}

void ModeX_SetPage(uint8_t _page) {
 // Ens coloca directament a la pagina de 4 que hi han.
 VgaRegs_SetStartAddress(g_modex_offset_page[g_current_mode][_page]);
}

void ModeX_SetOffset(uint16_t _offset_segment){
 VgaRegs_SetStartAddress(_offset_segment);
}

void ModeX_SetMode(uint8_t _mode) {
 // Ens posar la configuracio de 1x4,2x2 o 4x1.

 if(_mode == MODEX_MODE1X4) {
    g_current_mode = 0;
 }else if(_mode == MODEX_MODE2X2){
    g_current_mode = 1;
 }else {
   g_current_mode = 2;
 }

 VgaRegs_SetOffsetRegister(40 << g_current_mode);

}

void ModeX_DeInit(){

    Surface_Delete(g_modex_surface);
    g_modex_surface = NULL;
    
    asm{
        mov ah,00h  // AH = 0: Inicia el mode de Video 
        mov al,3h  // AL (00,02,03,07 = TEXTE). 
        int 10h
    }
   
}