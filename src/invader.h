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


#define INVADER_WINDOW_WIDTH            320
#define INVADER_WINDOW_HEIGHT           200
#define INVADER_PALETTE_COLORS          256
#define INVADER_PALETTE_SIZE            INVADER_PALETTE_COLORS*sizeof(Color)
#define INVADER_IMAGE_WIDTH             320
#define INVADER_IMAGE_HEIGHT            200
#define INVADER_IMAGE_SIZE              INVADER_IMAGE_WIDTH*INVADER_IMAGE_HEIGHT
#define INVADER_MED_FONT_LETTER_WIDTH   13
#define INVADER_MED_FONT_LETTER_HEIGHT  15
#define INVADER_FONT_NUM_LETTERS        48
#define INVADER_BIG_FONT_LETTER_WIDTH   26
#define INVADER_BIG_FONT_LETTER_HEIGHT  19





struct Color{
    uint8_t r,g,b;
    Color(){
        r=0;
        g=0;
        b=0;
    }
    friend bool operator==(const Color & _c1, const Color & _c2){
        return _c1.r==_c2.r
               && _c1.g==_c2.g
               && _c1.b==_c2.b;
    }

    friend bool operator!=(const Color & _c1, const Color & _c2){
        return !(_c1==_c2);
    }

};
