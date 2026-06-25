#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

typedef enum {
     KEY_ESC   =1
    ,KEY_P     =25     
    ,KEY_UP    =72
    ,KEY_RIGHT =77
    ,KEY_LEFT  =75
    ,KEY_DOWN  =80
    ,KEY_INSERT=82
    ,KEY_DEL   =83
    ,KEY_MAX   =128
}KEY;



void Keyboard_Init();
bool Keyboard_IsKeyPressed(KEY _key);
void Keyboard_DeInit();

#endif