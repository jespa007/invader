 #pragma once
 
#include "core/core.h"


#define INVADER_WINDOW_WIDTH            320
#define INVADER_WINDOW_HEIGHT           200
#define INVADER_PALETTE_COLORS          256
#define INVADER_PALETTE_SIZE            (INVADER_PALETTE_COLORS*3)
#define INVADER_IMAGE_WIDTH             320
#define INVADER_IMAGE_HEIGHT            200
#define INVADER_IMAGE_SIZE              INVADER_IMAGE_WIDTH*INVADER_IMAGE_HEIGHT
#define INVADER_MED_FONT_LETTER_WIDTH   13
#define INVADER_MED_FONT_LETTER_HEIGHT  15
#define INVADER_FONT_NUM_LETTERS        48
#define INVADER_BIG_FONT_LETTER_WIDTH   26
#define INVADER_BIG_FONT_LETTER_HEIGHT  19
#define INVADER_TILE_WIDTH              32                       
#define INVADER_TILE_HEIGHT             32

#define INVADER_MAX_TILES               67


class Invader{
public:
    static void init();
    static void loadEntities();
    static void loadImages();
    static void loadSounds();
    static void loadStage1();
    static void unloadStage1();
    static void update();
    static void deInit();

    static void iniTestImages();
    static void updateTestImages();
    static void iniTestEntities();
    static void updateTestEntities();

private:

    static SDL_Surface *loadImage(
        const std::string _image_name
        , const std::string & _raw_image_file
        , int _image_width
        , int _image_height
        ,const std::string  & _raw_palette_file
    );


    static Tilemap *background;
    static EntityManager *entity_manager;
    static bool    initialized;


};

