#include "INVADER.H"

int main(void){
    
    Buffer * palette = NULL;
    Surface * surface_blocks = NULL; 
    Surface * surface_video = NULL; 

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

    surface_video = Mode13_GetSurface();
    palette = File_Read("GFX\\PALETA1.PAL");
    surface_blocks = Surface_NewFromRaw("GFX\\BLOCS1.RAW",320,200);


    do{ 
        Rect rect = { 0, 0, 32, 32 };

        Surface_Blit(
            surface_video
            ,0
            ,0
            ,surface_blocks
            ,&rect
        );
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

    Buffer_Delete(palette);
    Surface_Delete(surface_blocks);


    Key_DeInit();
    //ModeX_DeInit();
    Mode13_DeInit();

    Memory_DumpLeaks();
    


    return 0;
}