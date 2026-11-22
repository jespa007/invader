#include "GRAPH\@GRAPH.H"

#define MODEX_SCREEN_WIDTH  320
#define MODEX_SCREEN_HEIGHT 200
#define MODEX_PITCH 80
#define MODEX_MAX_COMMANDS  256


typedef enum ModeXCommandType {
    MODEX_COMMAND_BLOCK,
    MODEX_COMMAND_SPRITE
} ModeXCommandType;

typedef struct ModeXCommand {
    ModeXCommandType type;

    Rect dst_rect;
    Rect src_rect;

    uint8_t transparent_color;

    const Surface *surface;
} ModeXCommand;

typedef struct ModeXPlaneBlit {
    const uint8_t far *src;
    uint8_t far *dst;

    uint16_t width;
    uint16_t height;

    uint16_t src_pitch;
    uint16_t dst_pitch;

    uint8_t transparent_color;
    bool transparent;
} ModeXPlaneBlit;

struct{
    uint16_t        width;
    uint16_t        height;
    uint8_t         mode;
    Surface       * surface;

    ModeXCommand    commands[MODEX_MAX_COMMANDS];
    uint16_t        command_count;
    ModeXPage       display_page;
    ModeXPage       draw_page;
    bool            initialized;
}g_modex;



#define MODEX_Y_OFFSET(y) \
    (((((uint16_t)(y)) << 6) + (((uint16_t)(y)) << 4)) << g_array_offset[g_modex.mode])

static uint16_t g_modex_offset_page[3][4] ={ // MAX_MODES = 3 i MAX_PAGINES = 4

 { 0, 16000, 32000, 48000 },           // MODE 1x4
 { 0, 80,    32000, 32080 },           // MODE 2x2
 { 0, 80,    160,   240   }            // MODE 4x1
};

static uint8_t g_array_offset[3] = {0,1,2};

Surface *Surface_NewModeX(
    uint16_t _segment,
    uint16_t _offset,
    uint16_t _width,
    uint16_t _height,
    uint16_t _pitch
);


/* Rectangles are clipped once on submission. No scaling in this iteration. */
static bool ModeX_ClipCommand(ModeXCommand *_command){
    SurfaceMemoryView view;
    int32_t sx, sy, dx, dy, w, h, trim;

    if(!Surface_GetMemoryView(_command->surface, &view)){
        return false;
    }

    sx = _command->src_rect.x;
    sy = _command->src_rect.y;
    dx = _command->dst_rect.x;
    dy = _command->dst_rect.y;
    w = _command->src_rect.width;
    h = _command->src_rect.height;

    if(w > _command->dst_rect.width) w = _command->dst_rect.width;
    if(h > _command->dst_rect.height) h = _command->dst_rect.height;
    if(w == 0 || h == 0) return false;

    if(sx < 0){ trim = -sx; sx += trim; dx += trim; w -= trim; }
    if(sy < 0){ trim = -sy; sy += trim; dy += trim; h -= trim; }
    if(dx < 0){ trim = -dx; sx += trim; dx += trim; w -= trim; }
    if(dy < 0){ trim = -dy; sy += trim; dy += trim; h -= trim; }
    if(w <= 0 || h <= 0) {
        return false;
    }

    if(     sx >= view.width 
        ||  sy >= view.height 
        ||  dx >= g_modex.width 
        ||  dy >= g_modex.height
    ){ 
        return false;
    }

    if(w > (int32_t)view.width - sx) w = (int32_t)view.width - sx;
    if(h > (int32_t)view.height - sy) h = (int32_t)view.height - sy;
    if(w > (int32_t)g_modex.width - dx) w = (int32_t)g_modex.width - dx;
    if(h > (int32_t)g_modex.height - dy) h = (int32_t)g_modex.height - dy;
    if(w <= 0 || h <= 0) {
        return false;
    }

    _command->src_rect.x = (int16_t)sx;
    _command->src_rect.y = (int16_t)sy;
    _command->src_rect.width = (uint16_t)w;
    _command->src_rect.height = (uint16_t)h;
    _command->dst_rect.x = (int16_t)dx;
    _command->dst_rect.y = (int16_t)dy;
    _command->dst_rect.width = (uint16_t)w;
    _command->dst_rect.height = (uint16_t)h;
    return true;
}

// Plane mask is selected by Graphics_Update, not by individual pixels.
static void ModeX_DrawCommandPlane(
    const ModeXCommand *_command,
    uint8_t _plane,
    uint16_t _page_offset
){
    SurfaceMemoryView view;
    uint16_t row, col, first, count;
    uint32_t source_offset, destination_offset;
    const uint8_t far *src;
    uint8_t far *dst;
    uint8_t color;

    if(!Surface_GetMemoryView(_command->surface, &view)) {
        return;
    }

    first = (uint16_t)((_plane - (_command->dst_rect.x & 3)) & 3);
    if(first >= _command->src_rect.width) return;
    count = (uint16_t)((_command->src_rect.width - first + 3) / 4);

    for(row = 0; row < _command->src_rect.height; ++row){
        source_offset = (uint32_t)(_command->src_rect.y + row) * view.pitch + (uint16_t)_command->src_rect.x + first;
        destination_offset = (uint32_t)_page_offset + (uint32_t)(_command->dst_rect.y + row) * MODEX_PITCH + ((uint16_t)(_command->dst_rect.x + first) >> 2);
        src = view.pixels + source_offset;
        dst = (uint8_t far *)MK_FP(VIDEO_SEGMENT, (uint16_t)destination_offset);

        if(_command->type == MODEX_COMMAND_BLOCK){
            for(col = 0; col < count; ++col){
                *dst++ = *src;
                src += 4;
            }
        }else{
            for(col = 0; col < count; ++col){
                color = *src;
                if(color != _command->transparent_color) {
                    *dst = color;
                }
                ++dst;
                src += 4;
            }
        }
    }
}

static bool ModeX_Queue(
    ModeXCommandType _type,
    Point _dst,Rect _src,
    const Surface *_surface,
    uint8_t _transparent_color
){
    ModeXCommand command;

    if(!g_modex.initialized 
    ||  g_modex.command_count >= MODEX_MAX_COMMANDS
    ) return false;

    command.type = _type;
    command.dst_rect.x = _dst.x;
    command.dst_rect.y = _dst.y;
    command.dst_rect.width = _src.width;
    command.dst_rect.height = _src.height;
    command.src_rect = _src;
    command.transparent_color = _transparent_color;
    command.surface = _surface;
    if(!ModeX_ClipCommand(&command)) return false;

    g_modex.commands[g_modex.command_count++] = command;
    return true;
}

bool ModeX_Init(uint16_t _width, uint16_t _height) {

    /* Current Mode X register setup supports 320x200, four 16KB pages. */
    if(_width != MODEX_SCREEN_WIDTH ||
       _height != MODEX_SCREEN_HEIGHT){
        LOG_ERROR("Mode X requires 320x200");
        return false;
    }    

    if( g_modex.initialized == true ){
        return true;
    }

    memset(&g_modex,0,sizeof(g_modex));

    asm{
         mov ah,00h  // AH = 0: Inicia el mode de Video 
        mov al,13h  // AL Mode 320 x 200 a 256 colors. 
        int 10h
    }

    // configure vga regs per plane
    VgaRegs_WaitVRetrace();

    VgaRegs_RegisterOut(SEQU_ADDR,0x04,0x06); //  forcem el bit CHAIN-4 a 0.
    VgaRegs_RegisterOut(CRTC_ADDR,0x17,0xe3); // ajust mode paraules.
    VgaRegs_RegisterOut(CRTC_ADDR,0x14,0x00); // ajust mode dobles paraules.


    g_modex.mode = MODEX_MODE1X4;
    VgaRegs_SetOffsetRegister(40 << g_modex.mode); 
    ModeX_ClearAllVRAM(0);

    g_modex.display_page = MODEX_PAGE0;
    g_modex.draw_page = MODEX_PAGE1;

    ModeX_SetPage(g_modex.display_page);

    // init surface here
    g_modex.surface = Surface_NewModeX(
        0xA000,
        0,
        _width,
        _height,
        MODEX_PITCH
    );

    if (g_modex.surface == NULL){
        return false;
    }    

    g_modex.initialized = true;
    g_modex.width = _width;
    g_modex.height = _height;

    return true;
}

Surface * ModeX_GetSurface(){
    return g_modex.surface;
}

void ModeX_ClearAllVRAM(uint8_t _color)
{
    VgaRegs_EnableAllPlanes();

    asm {
        push es
        push di

        cld

        mov ax, VIDEO_SEGMENT
        mov es, ax

        xor di, di

        mov al, [_color]
        mov ah, al

        mov cx, 32000
        rep stosw

        pop di
        pop es
    }
}

// This renderer uses MODEX_MODE1X4 only (four 320x200 pages)
uint16_t ModeX_GetPageOffset(ModeXPage _page){
    return g_modex_offset_page[MODEX_MODE1X4][_page & 3];
}

void ModeX_ClearPage(ModeXPage _page, uint8_t _color){
    uint16_t page_start = ModeX_GetPageOffset(_page);
    VgaRegs_EnableAllPlanes();
    asm {
        push es
        push di
        cld
        mov ax, VIDEO_SEGMENT
        mov es, ax
        mov di, [page_start]
        mov al, _color
        mov ah, al
        mov cx, 8000
        rep stosw
        pop di
        pop es
    }
}

void ModeX_PutPixel(ModeXPage page, int16_t x, int16_t y, uint8_t color){
    uint16_t offset_segment;

    VgaRegs_MaskPlanes(1 << (x & 3));

    offset_segment =
    g_modex_offset_page[g_modex.mode][page] +
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
    ModeXPage _page
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

uint8_t ModeX_GetPixel(ModeXPage page, int16_t x, int16_t y) {
    uint16_t offset_segment;
    uint8_t plane;

    plane = x & 3;

    VgaRegs_RegisterOut(GRAC_ADDR, 0x04, plane);

    offset_segment =
        g_modex_offset_page[g_modex.mode][page] +
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
     uint16_t offset_segment = g_modex_offset_page[g_modex.mode][_page];
 int i,j;

    if(g_modex.mode != MODEX_MODE1X4){
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

void ModeX_SetPage(ModeXPage _page) {
 // Ens coloca directament a la pagina de 4 que hi han.
 VgaRegs_SetStartAddress(g_modex_offset_page[g_modex.mode][_page]);
}

void ModeX_SetOffset(uint16_t _offset_segment){
 VgaRegs_SetStartAddress(_offset_segment);
}

void ModeX_SetMode(uint8_t _mode) {
 // Ens posar la configuracio de 1x4,2x2 o 4x1.

 if(_mode == MODEX_MODE1X4) {
    g_modex.mode = 0;
 }else if(_mode == MODEX_MODE2X2){
    g_modex.mode = 1;
 }else {
   g_modex.mode = 2;
 }

 VgaRegs_SetOffsetRegister(40 << g_modex.mode);

}

void ModeX_Begin(void){
    g_modex.command_count = 0;
}

void ModeX_Clear(uint8_t _color){
    ModeX_ClearPage(
        g_modex.draw_page,
        _color
    );
}

bool ModeX_PutBlock(
    Point _dst,Rect _src,
    const Surface *_surface
){
    return ModeX_Queue(
        MODEX_COMMAND_BLOCK,
        _dst,
        _src,
        _surface,
        0
    );
}

bool ModeX_PutSprite(
    Point _dst,Rect _src,
    const Surface *_surface,
    uint8_t _transparent_color
){
    return ModeX_Queue(
        MODEX_COMMAND_SPRITE,
        _dst,
        _src,
        _surface,
        _transparent_color
    );
}

void ModeX_Update(void){
    uint8_t plane;
    uint16_t i;
    uint16_t page_offset;

    if(!g_modex.initialized){
        return;
    }

    page_offset = ModeX_GetPageOffset(g_modex.draw_page);

    for(plane = 0; plane < 4; ++plane){
        VgaRegs_MaskPlanes((uint8_t)(1U << plane));
        for(i = 0; i < g_modex.command_count; ++i){
            ModeX_DrawCommandPlane(&g_modex.commands[i], plane, page_offset);
        }
    }
    VgaRegs_EnableAllPlanes();
    g_modex.command_count = 0;
}


void ModeX_Flush(){
    if(!g_modex.initialized) {
        return;
    }

    ModeX_SetPage(g_modex.draw_page);

    g_modex.display_page = g_modex.draw_page;
    g_modex.draw_page = (g_modex.draw_page == MODEX_PAGE0)
        ? MODEX_PAGE1 : MODEX_PAGE0;    


    // TODO : Verify page-flip timing on real VGA hardware
    VgaRegs_WaitVRetrace();
}


void ModeX_DeInit(){

    Surface_Delete(g_modex.surface);
    g_modex.surface = NULL;
    
    asm{
        mov ah,00h  // AH = 0: Inicia el mode de Video 
        mov al,3h  // AL (00,02,03,07 = TEXTE). 
        int 10h
    }
   
}