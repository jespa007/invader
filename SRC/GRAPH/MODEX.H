#ifndef __MODEX_H__
#define __MODEX_H__


#define MODEX_MODE1X4 0
#define MODEX_MODE2X2 1
#define MODEX_MODE4X1 2

#define MODEX_PLANE0 0x01
#define MODEX_PLANE1 0x02
#define MODEX_PLANE2 0x04
#define MODEX_PLANE3 0x08

#define MODEX_PAGE0 0
#define MODEX_PAGE1 1
#define MODEX_PAGE2 2
#define MODEX_PAGE3 3

void ModeX_Init();
void ModeX_SetDim(uint8_t _dim);
void ModeX_ClearAllVRAM(uint8_t color);
void ModeX_PutPixel(
    uint8_t _page
    , int16_t _x
    ,int16_t _y
    ,uint8_t _color
);

bool ModeX_LoadRawImage(
    uint8_t _page
    ,int16_t _x
    ,int16_t _y
    ,char *_filename
    ,uint16_t _image_width
    ,uint16_t _image_height
);

uint8_t ModeX_GetPixel(uint8_t _page, int16_t _x, int16_t _y);
void    ModeX_SetPage(uint8_t _page);
void    ModeX_SetOffset(uint16_t _offset_segment);

void ModeX_DeInit();

#endif