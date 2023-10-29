 #pragma once
 
 #include <stdio.h>
#include  <SDL2/SDL.h>
#include  <unordered_map>
#include  <vector>
#include  <map>
#include  <functional>
#include  <string>

#define snprintf _snprintf

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifdef __MEMMANAGER__
#include "memmgr.h"
#endif

#include 		<stdexcept>
#include 		<cstddef>

#include "common.h"
#include "System.h"
#include "Input.h"
#include "Image.h"
#include "Font.h"
#include "Collider.h"
#include "Sprite.h"
#include "EntityAnimation.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Tilemap.h"
#include "Graphics.h"
#include "Sound.h"
#include "SoundPlayer.h"
#include "Color.h"
//#include "Stage1.h"


#define INVADER_WINDOW_WIDTH            320
#define INVADER_WINDOW_HEIGHT           200
#define INVADER_PALETTE_COLORS          256
#define INVADER_PALETTE_SIZE            (INVADER_PALETTE_COLORS*sizeof(Color))
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

#define INVADER_MAX_TILES               70


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

private:

    static Image *loadImage(
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

