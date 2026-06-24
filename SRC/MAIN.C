#include "INVADER.H"

int main(void){
    #ifdef DEBUG
        printf("Hello world DEBUG!\n");
    #else
        printf("Hello world RELEASE!\n");
    #endif

    Graphics_Init();
    Key_Init();

    do{ 
        Graphics_PutPixel(rand()%320,rand()%200,rand()&0xff);
    }while(!Key_IsDown(KEY_ESC));


    Key_DeInit();
    Graphics_DeInit();
    


    return 0;
}