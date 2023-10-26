/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "Invader.h"

//-------
// Static
std::map<std::string, Image *> *Image::s_images=NULL;

std::map<std::string, Image *> *Image::getMap(){
	if(s_images == NULL){
		s_images=new std::map<std::string,Image *>;
	}

	return s_images;

}

SDL_Texture *  Image::convertSurfaceToTexture(SDL_Surface *_srf){

	SDL_Texture *text=SDL_CreateTextureFromSurface(
			Graphics::getRenderer()
			, _srf
	);

	if(!text){
		fprintf(stderr,"Error converting surface %s\n",SDL_GetError());
	}
	return text;
}


Image *Image::newImage(const std::string & _name,const std::string & _file,const ImageLoadOptions &_image_load_options){

	Image *image=Image::get(_name);

	if(image != NULL){
		fprintf(stderr,"Image::newImage: Image '%s' already exists\n",_name.c_str());
		return image;
	}

	image=new Image();

	if(!image->loadImage(_file,_image_load_options)){
		delete image;
		return NULL;
	}

	(*s_images)[_name]=image;

	return image;

}

Image *Image::newImage(const std::string & _name,int _width,int _height){
	Image *image=Image::get(_name);

	if(image != NULL){
		fprintf(stderr,"Image::newImage: Image '%s' already exists\n",_name.c_str());
		return image;
	}

	image=new Image(_width,_height);


	(*s_images)[_name]=image;

	return image;

}

Image *Image::get(const std::string & _name){
	auto textures=getMap();
	if(textures->count(_name)!=0){
		return (*textures)[_name];
	}

	return NULL;
}

void Image::unloadAll(){
	auto textures=getMap();
	for(auto v=textures->begin(); v != textures->end(); v++){
		delete v->second;
	}

	textures->clear();

}

void Image::destroy(){
	unloadAll();

	if(s_images != NULL){
		delete s_images;
		s_images=NULL;
	}
}



//-------
// Member

Image::Image(){
	width=	height=0;
	sdl_texture=NULL;
	// default pixmap..
}

void Image::createTexture(int _width,int _height){
	if(sdl_texture!=NULL){
		freeImage();
	}

	SDL_Renderer *renderer=Graphics::getRenderer();

	if(_width>0 && _height > 0){
		width=_width;
		height=_height;

		sdl_texture = SDL_CreateTexture(
			renderer
			,SDL_PIXELFORMAT_RGBA8888//SDL_GetWindowPixelFormat( Graphics::getWindow() )
			,SDL_TEXTUREACCESS_TARGET
			,_width
			,_height );

		if(sdl_texture==NULL){
			fprintf(stderr,"Error creating surface %s\n",SDL_GetError());
			return;

		}

		// render image with alpha
		SDL_SetRenderTarget(renderer, sdl_texture);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		// this sets renderer back to default target (the window)
		SDL_SetRenderTarget(renderer, NULL);
	}

}


Image::Image(int _width,int _height){
	sdl_texture=NULL;
	createTexture(_width,_height);
}

bool Image::loadImage(const std::string & _file,const ImageLoadOptions &_texture_load_options){

	SDL_Surface *srf=SDL_LoadBMP(_file.c_str());
	bool ok=false;
	if(srf!=NULL){
		if(_texture_load_options.color_key!=-1){
			SDL_SetColorKey(
					srf
					,SDL_TRUE
					,SDL_MapRGB(srf ->format
						,SDL_COLOR32B_TO_RED8B(_texture_load_options.color_key)
						,SDL_COLOR32B_TO_GREEN8B(_texture_load_options.color_key)
						,SDL_COLOR32B_TO_BLUE8B(_texture_load_options.color_key)
					)
			);
		}

		if((sdl_texture=Image::convertSurfaceToTexture(srf)) !=NULL){
			width=srf->w;
			height=srf->h;

			// free surface...
			printf("Loaded image %s (%ix%i).\n",_file.c_str(),width,height);

			ok=true;
		}
		else{
			fprintf(stderr,"SurfaceToTexture:%s\n",SDL_GetError());
		}

		SDL_FreeSurface(srf);
	}
	else{
		fprintf(stderr,"SDL_LoadBMP:%s\n",SDL_GetError());
	}


	return ok;
}


void Image::begin(){
	SDL_Renderer *renderer=Graphics::getRenderer();

	// render image with alpha
	SDL_SetRenderTarget(renderer, sdl_texture);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	SDL_SetTextureBlendMode(sdl_texture, SDL_BLENDMODE_BLEND);
}

void Image::setColor3i(int8_t _r, int8_t _g, int8_t _b){
	SDL_Renderer *renderer=Graphics::getRenderer();
	SDL_SetRenderDrawColor(renderer, _r, _g, _b, 0xFF);
}

void Image::putPoint(int x, int y){
	SDL_Renderer *renderer=Graphics::getRenderer();
	SDL_RenderDrawPoint(renderer, x, y);
}

void Image::end(){
	SDL_Renderer *renderer=Graphics::getRenderer();
	SDL_SetRenderTarget(renderer, NULL);
}
/*
void Image::update(
	uint8_t *_pixels
	,int _width
	,int _height
){
	// image expects RGB

	if(sdl_texture == NULL){
		createTexture(_width,_height);
	}


	if(_width==this->width && _height == this->height){

		// draw image
		SDL_Renderer *renderer=Graphics::getRenderer();

		// render image with alpha
		SDL_SetRenderTarget(renderer, sdl_texture);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		SDL_SetTextureBlendMode(sdl_texture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		uint8_t pixels=_pixels;

		for(int y=0; y < this->height;y++){
			for(int x=0; x < this->width;x++){
				Uint8 r=*(pixels+0);
				Uint8 g=*(pixels+1);
				Uint8 b=*(pixels+2);

				SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
				SDL_RenderDrawPoint(renderer, x, y);
				pixels+=3
			}
		}

		// this sets renderer back to default target (the window)
		SDL_SetRenderTarget(renderer, NULL);
	}
	else{
		fprintf(stderr,"Image::update : Dimensions out of boundy\n");
	}

}*/

SDL_Texture * Image::getSdlTexture(){
	return sdl_texture;
}

int Image::getWidth(){
	return width;
}

int Image::getHeight(){
	return height;
}

void Image::freeImage(){
	if(sdl_texture != NULL){
#ifdef __DEBUG__
		printf("Image unloaded!\n");
#endif
		SDL_DestroyTexture(sdl_texture);
		sdl_texture=NULL;
	}

}

Image::~Image(){
	freeImage();
}
