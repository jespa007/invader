#ifndef __POINT_H__
#define __POINT_H__

typedef struct Point Point;

struct Point
{
    int16_t x;
    int16_t y;
};

Point Point_New(int16_t _x, int16_t _y);

#endif