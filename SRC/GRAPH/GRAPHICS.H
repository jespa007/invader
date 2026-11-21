#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__


void        Graphics_Init(uint16_t _width, uint16_t _height);
uint16_t    Graphics_GetWidth();
uint16_t    Graphics_GetHeight();
void        Graphics_Begin();
void        Graphics_DrawText(int _x, int _y, uint8_t _color, const char *_text, ...);
void        Graphics_PutPixel(int _x, int _y, uint8_t _color);
void        Graphics_PutBlock(Point _dst,Rect _src, const Surface * _surface);
void        Graphics_PutSprite(Point _dst,Rect _src, const Surface * _surface, uint8_t _transparent_color);
void        Graphics_Update();
void        Graphics_End();
void        Graphics_DeInit();


#endif