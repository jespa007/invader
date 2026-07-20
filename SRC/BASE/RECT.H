#ifndef __RECT_H__
#define __RECT_H__

typedef struct Rect Rect;

struct Rect
{
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;
};

#endif