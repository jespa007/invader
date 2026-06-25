#include "INVADER.H"

int main(void){
    #ifdef DEBUG
        printf("Hello world DEBUG!\n");
    #else
        printf("Hello world RELEASE!\n");
    #endif

    Graphics_Init(SCREEN_WIDTH, SCREEN_HEIGHT);
    Key_Init();

    do{ 
        //Graphics_Begin();
        FntMono_PutChar(0,0,'A',0,0);
        Graphics_PutPixel(
            Graphics_GetWidth()>>1
            ,Graphics_GetHeight()>>1
            ,123
        );
        //Graphics_End();
    }while(!Key_IsDown(KEY_ESC));


    Key_DeInit();
    Graphics_DeInit();
    


    return 0;
}