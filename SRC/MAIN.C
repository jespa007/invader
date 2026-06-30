#include "INVADER.H"

int main(void){
    #ifdef DEBUG
        printf("Hello world DEBUG!\n");
    #else
        printf("Hello world RELEASE!\n");
    #endif

    //Graphics_Init(SCREEN_WIDTH, SCREEN_HEIGHT);
/*ModeX_Init();

ModeX_PutPixel(MODEX_PAGE0, 10, 10, 4);
ModeX_PutPixel(MODEX_PAGE1, 20, 20, 2);
ModeX_PutPixel(MODEX_PAGE2, 30, 30, 1);
ModeX_PutPixel(MODEX_PAGE3, 40, 40, 15);    */
    Mode13_Init();
    Key_Init();

    do{ 
        //Graphics_Begin();
       /* FntMono_PutChar(0,0,'A',0,0);
        Graphics_PutPixel(
            Graphics_GetWidth()>>1
            ,Graphics_GetHeight()>>1
            ,123
        );*/
    
     /*Graphics_WaitVRetrace();
    ModeX_SetPage(MODEX_PAGE0);

    Graphics_WaitVRetrace();
    ModeX_SetPage(MODEX_PAGE1);

    Graphics_WaitVRetrace();
    ModeX_SetPage(MODEX_PAGE2);

    Graphics_WaitVRetrace();
    ModeX_SetPage(MODEX_PAGE3);*/
        //Graphics_End();
    }while(!Key_IsDown(KEY_ESC));


    Key_DeInit();
    //ModeX_DeInit();
    Mode13_DeInit();
    


    return 0;
}