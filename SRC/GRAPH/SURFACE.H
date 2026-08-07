#ifndef __SURFACE_H__
#define __SURFACE_H__

typedef struct Surface Surface;

typedef enum SurfaceType
{
    SURFACE_MEMORY,
    SURFACE_MODE13,
    SURFACE_MODEX
} SurfaceType;

struct Surface
{
    void * data;
};



Surface *  Surface_New( uint16_t _width, uint16_t _height);
Surface  * Surface_NewFromPixels(uint8_t far * _pixels,  uint16_t _width, uint16_t _height);
Surface  * Surface_NewFromRaw(
    const char * _filename,
    uint16_t _width,
    uint16_t _height
);

void Surface_Clear(Surface * _this, uint8_t _color);

bool Surface_Blit(
    Surface * _this,
    int _x,
    int _y,
    const Surface *_src,
    const Rect * _src_clip
);

bool Surface_BlitColorKey(
    Surface * _this,
    int _x,
    int _y,
    const Surface *_src,
    const Rect * _src_clip,
    uint8_t _color_key
);

void Surface_Delete(Surface * _this);

#endif