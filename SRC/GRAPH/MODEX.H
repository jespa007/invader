#ifndef __MODEX_H__
#define __MODEX_H__


#define MODEX_MODE1X4 0
#define MODEX_MODE2X2 1
#define MODEX_MODE4X1 2

#define MODEX_PLANE0 0x01
#define MODEX_PLANE1 0x02
#define MODEX_PLANE2 0x04
#define MODEX_PLANE3 0x08

typedef enum ModeXPage{
    MODEX_PAGE0=0
    ,MODEX_PAGE1
    ,MODEX_PAGE2
    ,MODEX_PAGE3
}ModeXPage;

bool  ModeX_Init(uint16_t _width, uint16_t _height);
Surface * ModeX_GetSurface();


void        ModeX_SetDim(uint8_t _dim);
void        ModeX_SetPage(ModeXPage _page);
void        ModeX_SetOffset(uint16_t _offset_segment);
uint16_t    ModeX_GetPageOffset(ModeXPage _page);

void        ModeX_ClearPage(ModeXPage _page, uint8_t _color);
void        ModeX_ClearAllVRAM(uint8_t color);
void        ModeX_PutPixel(ModeXPage _page, int16_t _x,int16_t _y,uint8_t _color);
uint8_t     ModeX_GetPixel(ModeXPage _page, int16_t _x, int16_t _y);
bool        ModeX_LoadRawImage(ModeXPage _page,int16_t _x,int16_t _y,char *_filename,uint16_t _image_width ,uint16_t _image_height);
void        ModeX_Begin(void);
void        ModeX_Clear(uint8_t _color);


bool ModeX_PutBlock(
   Point _dst,Rect _src,
    const Surface *_surface
);

bool ModeX_PutSprite(
    Point _dst,Rect _src,
    const Surface *_surface,
    uint8_t _transparent_color
);

void        ModeX_Flush();


void ModeX_DeInit();

#endif