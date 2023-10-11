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


#define INVADER_WINDOW_WIDTH    320
#define INVADER_WINDOW_HEIGHT   200