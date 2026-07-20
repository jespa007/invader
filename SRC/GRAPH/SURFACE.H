#ifndef __SURFACE_H__
#define __SURFACE_H__

typedef enum SurfaceType
{
    SURFACE_MEMORY,
    SURFACE_MODE13,
    SURFACE_MODEX
} SurfaceType;

typedef struct Surface{
    void * data;
} Surface;


Surface * Surface_Create( uint16_t _width, uint16_t _height);

void Surface_Clear(Surface * _this, uint8_t _color);

void Surface_Blit(
    Surface * _this,
    int _x,
    int _y,
    const Surface *_src,
    Rect _src_clip
);

void Surface_BlitColorKey(
    Surface * _this,
    int _x,
    int _y,
    const Surface *_src,
    Rect _src_clip
    uint8_t _color_key
);

void Surface_Delete(Surface * _this);

#endif