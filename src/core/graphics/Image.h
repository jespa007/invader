/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

#include "ImageDrawOptions.h"
#include "ImageLoadOptions.h"


#if SDL_BYTEORDER == SDL_BIG_ENDIAN

#define SDL_COLOR32B_TO_RED8B(rgb) 		((rgb>>24)&0xFF)
#define SDL_COLOR32B_TO_GREEN8B(rgb) 	((rgb>>16)&0xFF)
#define SDL_COLOR32B_TO_BLUE8B(rgb) 	((rgb>>8)&0xFF)

#define SDL_RMASK	0xff000000
#define SDL_GMASK	0x00ff0000
#define SDL_BMASK	0x0000ff00
#define SDL_AMASK	0x000000ff
#else

#define SDL_COLOR32B_TO_RED8B(rgb) 		((rgb)&0xFF)
#define SDL_COLOR32B_TO_GREEN8B(rgb) 	((rgb>>8)&0xFF)
#define SDL_COLOR32B_TO_BLUE8B(rgb) 	((rgb>>16)&0xFF)

#define SDL_RMASK	0x000000ff
#define SDL_GMASK	0x0000ff00
#define SDL_BMASK	0x00ff0000
#define SDL_AMASK	0xff000000
#endif


class Graphics;
class Image{

public:

	static Image *newImage(const std::string & name,const std::string & filename,const ImageLoadOptions &_image_load_options=ImageLoadOptions());
	static Image *newImage(const std::string & name,int _width=0,int _height=0);
	static Image *newImageFromSdlSurface(const std::string & name, SDL_Surface *_surface);

	static Image *get(const std::string & name);
	static void unloadAll();
	static void destroy();


	SDL_Texture *getSdlTexture();

	bool loadImage(const std::string & filename,const ImageLoadOptions &_image_load_options=ImageLoadOptions());

	// create image from file
	//bool load(const std::string & file,const ImageLoadOptions &_image_load_options=ImageLoadOptions());

	// update pixels
	void begin();
	void setColor3i(int8_t _r, int8_t _g, int8_t _b);
	void putPoint(int x, int y);
	void end();


	int getWidth();
	int getHeight();

protected:

	static std::map<std::string,Image *> *s_images;
	static std::map<std::string, Image *> *getMap();


	SDL_Texture *sdl_texture;
	int width,height;

	Image();
	Image( int _width,int _height);
	Image(SDL_Surface *_surface);

	void setup();
	void createTexture(int _width,int _height);

	static SDL_Texture * convertSurfaceToTexture(SDL_Surface *srf);

	void freeImage();
	~Image();

};
