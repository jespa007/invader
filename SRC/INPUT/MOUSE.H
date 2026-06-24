#ifndef __MOUSE_H__
#define __MOUSE_H__

bool Mouse_Init();
void Mouse_ShowCursor(void);
void Mouse_HideCursor(void);
int  Mouse_BPressed(void);
void Mouse_DeInit();

#endif