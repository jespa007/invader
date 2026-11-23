#include "INVADER.H"

int main(void){
    Buffer *palette = NULL;
    Surface *surface_blocks = NULL;
    Surface *surface_sprites = NULL;
    Rect src_rect = {0, 0, 32, 32};
    Point dst_block = {10, 10};
    Point dst_sprite = {10, 50};
    int i = 0;

    Graphics_Init(SCREEN_WIDTH, SCREEN_HEIGHT);
    Keyboard_Init();

    palette = File_Read("GFX\\PALETA1.PAL");
    surface_blocks = Surface_NewFromRaw("GFX\\BLOCS1.RAW", 320, 200);
    surface_sprites = Surface_NewFromRaw("GFX\\SPRITES1.RAW", 320, 200);

    Graphics_SetPalette(palette->ptr,0,255);

    if(Graphics_GetWidth() != SCREEN_WIDTH ||
       surface_blocks == NULL || surface_sprites == NULL){
        LOG_ERROR("Cannot initialize graphics or load sprite sheets");
    }else{
        do{
            Graphics_Begin();
            Graphics_PutBlock(dst_block, src_rect, surface_blocks);
            Graphics_PutSprite(dst_sprite, src_rect, surface_sprites, SPRITE_COLOR_KEY);
            Graphics_Update();
            Graphics_End();

            Input_Update();
            if(Keyboard_IsKeyPressed(KEY_RIGHT)){
                if(i < 4){ ++i; src_rect.x = 32 * i; }
            }else if(Keyboard_IsKeyPressed(KEY_LEFT)){
                if(i > 0){ --i; src_rect.x = 32 * i; }
            }
        }while(!Keyboard_IsKeyPressed(KEY_ESC));
    }

    Buffer_Delete(palette);
    Surface_Delete(surface_blocks);
    Surface_Delete(surface_sprites);
    Keyboard_DeInit();
    Graphics_DeInit();
    Memory_DumpLeaks();
    return 0;
}