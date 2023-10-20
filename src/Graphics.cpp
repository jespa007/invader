/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "invader.h"

#define RMASK32 0x000000ff
#define GMASK32 0x0000ff00
#define BMASK32 0x00ff0000
#define AMASK32 0xff000000

#define TICKS_FOR_NEXT_FRAME (1000 / 60)

static Graphics *g_graphics_render=NULL;
static SDL_Renderer *g_graphics_renderer = NULL;
static SDL_Event g_graphics_event;
static bool g_graphics_fullscreen=false;
static int g_graphics_width=0, g_graphics_height=0;
static bool g_graphics_show_sprite_colliders=false;
static Uint32	g_graphics_last_time=0;
static SDL_Rect *g_graphics_rect_display=NULL;
static float g_graphics_display_scalex=1,g_graphics_display_scaley=1;
static float g_graphics_aspect=1;
static int g_graphics_fullscreen_startx=0;
static float g_graphics_startx=0;
static int g_graphics_num_displays=0;
static int g_graphics_active_display=0;
static SDL_Window* g_graphics_window = NULL;


void Graphics::setIcon(const std::string & _file){
	if(g_graphics_window == NULL){
		fprintf(stderr,"Cannot set icon. Window is not initialized\n");
		return;
	}

	SDL_Surface *src=SDL_LoadBMP(_file.c_str());
	if(src != NULL){

		SDL_SetWindowIcon(g_graphics_window, src);
		SDL_FreeSurface(src);

	}else{
		fprintf(stderr,"Cannot load icon '%s': %s\n",_file.c_str(),SDL_GetError());
		return;
	}
}

void Graphics::createWindow(
	int _width
	,int _height
	,const std::string & _title
	,const std::string & _icon
	,bool _fullscreen
){
	if (SDL_WasInit(SDL_INIT_VIDEO) != SDL_INIT_VIDEO) {
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
			fprintf(stderr,"Unable to init video subsystem: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}

	if(g_graphics_rect_display==NULL){
		g_graphics_num_displays=SDL_GetNumVideoDisplays();
		if(g_graphics_num_displays < 0){
			fprintf(stderr,"SDL_GetNumVideoDisplays error : %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		g_graphics_rect_display=(SDL_Rect *)malloc(sizeof(SDL_Rect)*g_graphics_num_displays);
		for(int i=0 ; i < g_graphics_num_displays; i++){
			if(SDL_GetDisplayBounds(i, &g_graphics_rect_display[i])!=0){
				fprintf(stderr,"SDL_GetDisplayBounds error : %s\n", SDL_GetError());
				exit(EXIT_FAILURE);
			}
		}
	}

	g_graphics_width=_width;
	g_graphics_height=_height;

	g_graphics_window = SDL_CreateWindow(
		_title.c_str()
		,_fullscreen?g_graphics_rect_display[g_graphics_active_display].x:g_graphics_rect_display[g_graphics_active_display].x+(g_graphics_rect_display[g_graphics_active_display].w>>1)
		,_fullscreen?g_graphics_rect_display[g_graphics_active_display].y-1:g_graphics_rect_display[g_graphics_active_display].y+(g_graphics_rect_display[g_graphics_active_display].h>>1)
		,_fullscreen?g_graphics_rect_display[g_graphics_active_display].w:_width
		,_fullscreen?g_graphics_rect_display[g_graphics_active_display].h:_height
		,_fullscreen?SDL_WINDOW_FULLSCREEN_DESKTOP :0
	);

	if (!g_graphics_window) {
		fprintf(stderr,"Unable to create g_graphics_window: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if(_icon.empty()==false){
		setIcon(_icon);
	}

    printf( "Graphics\n");
    printf( "--------\n");
    printf("- Resolution: %ix%i\n"
    		,g_graphics_width
			,g_graphics_height
	);

    for(int i=0; i < g_graphics_num_displays; i++){
		printf("- Display dimensions display %i: [%i,%i,%i,%i]\n"
				,i
				,g_graphics_rect_display[i].x
				,g_graphics_rect_display[i].y
				,g_graphics_rect_display[i].w
				,g_graphics_rect_display[i].h
		);
    }

    printf("\n");

	g_graphics_renderer = SDL_CreateRenderer(g_graphics_window, -1, SDL_WINDOW_SHOWN | SDL_RENDERER_ACCELERATED);

    if (!g_graphics_renderer) {
		fprintf(stderr,"Unable to create g_graphics_renderer: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
    }

    SDL_RendererInfo info;
    SDL_GetRendererInfo(g_graphics_renderer, &info);
    printf( "Render\n");
    printf( "------\n");
	printf("- Name : %s\n", info.name);
	printf("- Flags : ");
	if (info.flags & SDL_RENDERER_SOFTWARE) printf("SDL_RENDERER_SOFTWARE");
	if (info.flags & SDL_RENDERER_ACCELERATED) printf( "SDL_RENDERER_ACCELERATED ");
	if (info.flags & SDL_RENDERER_PRESENTVSYNC) printf( "SDL_RENDERER_PRESENTVSYNC ");
	if (info.flags & SDL_RENDERER_TARGETTEXTURE) printf( "SDL_RENDERER_TARGETTEXTURE ");
	printf( "\n- Num.textures formats : %d\n", info.num_texture_formats);
	printf( "- Image size max : %dx%d \n", info.max_texture_width, info.max_texture_height);
	printf( "- Current driver : %s\n", SDL_GetCurrentVideoDriver());
	printf( "\n");


	if(_fullscreen){
		calculeScaleFactors();
	}

	g_graphics_fullscreen=_fullscreen;
}

int Graphics::getWidth(){
	return g_graphics_width;
}

int Graphics::getHeight(){
	return g_graphics_height;
}


SDL_Renderer * Graphics::getRenderer(){
	return g_graphics_renderer;
}

SDL_Window * Graphics::getWindow(){
	return g_graphics_window;
}

void Graphics::clear(Uint8 r, Uint8 g, Uint8 b){
	//Clear screen
	SDL_SetRenderDrawColor( g_graphics_renderer, r, g, b, 0xFF );
	SDL_RenderClear( g_graphics_renderer );
}

void 				 Graphics::drawPoint( int _x, int _y, int _rgb){
    SDL_SetRenderDrawColor(
      g_graphics_renderer
		,_rgb&0xFF 			// r
		,(_rgb>>8)&0xFF 	// g
		,(_rgb>>16)&0xFF	// b
		,0					// alpha
	);  
  SDL_RenderDrawPoint(g_graphics_renderer, _x, _y);
}

//draw one quadrant arc, and mirror the other 4 quadrants
// source: https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
void Graphics::drawEllipse( int _x_center, int _y_center, int _radius_x, int _radius_y, int _rgb)
{
    float pi  = 3.14159265358979323846264338327950288419716939937510;
    float pih = pi / 2.0; //half of pi

    //drew  28 lines with   4x4  circle with precision of 150 0ms
    //drew 132 lines with  25x14 circle with precision of 150 0ms
    //drew 152 lines with 100x50 circle with precision of 150 3ms
    const int prec = 27; // precision value; value of 1 will draw a diamond, 27 makes pretty smooth circles.
    float theta = 0;     // angle that will be increased each loop

    int x0=_x_center*g_graphics_display_scalex+g_graphics_startx;
    int y0=_y_center*g_graphics_display_scaley;
    int radius_x=_radius_x*g_graphics_display_scalex;
    int radius_y=_radius_y*g_graphics_display_scaley;


    //starting point
    int x  = (float)radius_x * cos(theta);//start point
    int y  = (float)radius_y * sin(theta);//start point
    int x1 = x;
    int y1 = y;

    SDL_SetRenderDrawColor(
      g_graphics_renderer
		,_rgb&0xFF 			// r
		,(_rgb>>8)&0xFF 	// g
		,(_rgb>>16)&0xFF	// b
		,0					// alpha
	);

    //repeat until theta >= 90;
    float step = pih/(float)prec; // amount to add to theta each time (degrees)
    for(theta=step;  theta <= pih;  theta+=step)//step through only a 90 arc (1 quadrant)
    {
        //get new point location
        x1 = (float)radius_x * cosf(theta) + 0.5; //new point (+.5 is a quick rounding method)
        y1 = (float)radius_y * sinf(theta) + 0.5; //new point (+.5 is a quick rounding method)

        //draw line from previous point to new point, ONLY if point incremented
        if( (x != x1) || (y != y1) )//only draw if coordinate changed
        {
            SDL_RenderDrawLine(g_graphics_renderer, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
            SDL_RenderDrawLine(g_graphics_renderer, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
            SDL_RenderDrawLine(g_graphics_renderer, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
            SDL_RenderDrawLine(g_graphics_renderer, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
        }
        //save previous points
        x = x1;//save new previous point
        y = y1;//save new previous point
    }
    //arc did not finish because of rounding, so finish the arc
    if(x!=0)
    {
        x=0;
        SDL_RenderDrawLine(g_graphics_renderer, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
        SDL_RenderDrawLine(g_graphics_renderer, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
        SDL_RenderDrawLine(g_graphics_renderer, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
        SDL_RenderDrawLine(g_graphics_renderer, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
    }
}

//draw one quadrant arc, and mirror the other 4 quadrants
void Graphics::drawRectangle( int _x_center, int _y_center, int _width, int _height,  int _rgb){

	SDL_Rect rect;

	rect.x=(_x_center-(_width>>1))*g_graphics_display_scalex+g_graphics_startx;
	rect.y=(_y_center-(_height>>1))*g_graphics_display_scaley;
	rect.w=_width*g_graphics_display_scalex;
	rect.h=_height*g_graphics_display_scaley;

    SDL_SetRenderDrawColor(
      g_graphics_renderer
		,_rgb&0xFF 			// r
		,(_rgb>>8)&0xFF 	// g
		,(_rgb>>16)&0xFF	// b
		,0					// alpha
	);

    SDL_RenderDrawRect(g_graphics_renderer, &rect);
}

//draw one quadrant arc, and mirror the other 4 quadrants
void Graphics::drawFilledRectangle( int _x_center, int _y_center, int _width, int _height,  int _rgb){

	SDL_Rect rect;

	rect.x=(_x_center-(_width>>1))*g_graphics_display_scalex+g_graphics_startx;
	rect.y=(_y_center-(_height>>1))*g_graphics_display_scaley;
	rect.w=_width*g_graphics_display_scalex;
	rect.h=_height*g_graphics_display_scaley;


    SDL_SetRenderDrawColor(g_graphics_renderer
		,_rgb&0xFF 			// r
		,(_rgb>>8)&0xFF 	// g
		,(_rgb>>16)&0xFF	// b
		,0					// alpha
	);

    SDL_RenderFillRect(g_graphics_renderer, &rect);

}

void 	Graphics::drawCross( int _x_center, int _y_center, int _width, int _height, int _thickness,  int _rgb){
	// horizontal
	drawFilledRectangle(_x_center,_y_center,_width,_thickness,_rgb);
	// vertical
	drawFilledRectangle(_x_center,_y_center,_thickness,_height,_rgb);
}


void Graphics::drawImage(
	Image *_img
	, int _x_center
	, int _y_center
	, const ImageDrawOptions & _draw_image_options
){
	//Apply the image
	if(_img){
		SDL_Texture *sdl_texture=_img->getSdlTexture();
		int image_width=_img->getWidth();
		int image_height=_img->getHeight();
		//_img->draw(this,_x,_y,_draw_image_options);
		if(sdl_texture!=NULL){

			int rgb=_draw_image_options.color;
			SDL_Rect image_crop={
				0
				,0
				,image_width
				,image_height
			};


			SDL_Rect dst_rect={
				_x_center-(int)((image_width>>1)*_draw_image_options.scalex)
				,_y_center-(int)((image_height>>1)*_draw_image_options.scaley)
				,(int)(image_width*_draw_image_options.scalex)
				,(int)(image_height*_draw_image_options.scaley)
			};

			// crop from image ...
			if(_draw_image_options.crop.w>0 && _draw_image_options.crop.h>0){
				image_crop=_draw_image_options.crop;
				dst_rect={_x_center-( image_crop.w>>1),_y_center-( image_crop.h>>1), image_crop.w, image_crop.h};
			}

			// ajusts positions size in function of scale
			dst_rect.x*=g_graphics_display_scalex;
			dst_rect.y*=g_graphics_display_scaley;

			dst_rect.w*=g_graphics_display_scalex;
			dst_rect.h*=g_graphics_display_scaley;

			// offset in function resolution g_graphics_aspect
			dst_rect.x+=g_graphics_startx;

			// apply color
			SDL_SetTextureColorMod(sdl_texture,
					SDL_COLOR32B_TO_RED8B(rgb),
					SDL_COLOR32B_TO_GREEN8B(rgb),
					SDL_COLOR32B_TO_BLUE8B(rgb)
			);

			SDL_RenderCopy(g_graphics_renderer, sdl_texture, &image_crop, &dst_rect);
		}
	}
}

void Graphics::drawText(
		Font *_font
		,int _x
		,int _y
		,const std::string & _text
		,const FontDrawOptions  & _draw_font_options
){
	if(_font){
		//_font->draw(this, _x ,_y,_text,_draw_font_options);
		float scale=1;


		if(_draw_font_options.font_height>0){
			if(_draw_font_options.font_height!=_font->getCharHeight()){
				scale=_draw_font_options.font_height/((float)_font->getCharHeight());
			}
		}


		int total_width=_font->getTextWith(_text,_draw_font_options);

		// by default, text is aligned to left
		_x-=total_width>>1;

		SDL_Rect dst_rect={
			(int)(_x*g_graphics_display_scalex+g_graphics_startx)
			,(int)(_y*g_graphics_display_scaley)
			,(int)((_font->getCharWidth()*scale)*g_graphics_display_scalex)
			,(int)((_font->getCharHeight()*scale)*g_graphics_display_scaley)
		};

		for(unsigned i=0; i < _text.size(); i++){
			char c=_text[i];
			SDL_Rect src_rect=_font->getRectChar(c);
			SDL_RenderCopy(g_graphics_renderer, _font->getSdlTexture(), &src_rect, &dst_rect);
			dst_rect.x+=dst_rect.w;
		}
	}
}

void Graphics::drawEntity(Entity *_entity){
	drawEntity(_entity, 0,0);
}

void Graphics::drawEntity(Entity *_entity,int _x_center, int _y_center){


	if(_entity->is_visible==false){
		return;
	}

	drawFrameInfo(_entity->getCurrentFrameData(),_x_center+_entity->x,_y_center+_entity->y);

	if(g_graphics_show_sprite_colliders){
		auto collider=_entity->getCollider();
		if(collider!=NULL && collider->collider_type!=Collider::ColliderType::COLLIDER_TYPE_NONE){
			drawCollider(_entity->getCollider(),_x_center+_entity->x,_y_center+_entity->y);
		}
	}
}

void Graphics::drawFrameInfo(Frame *_frame_info,int _x, int _y){
	if(_frame_info != NULL){
		drawImage(
			_frame_info->image
			,_x
			,_y
			,ImageDrawOptions(
				_frame_info->color
				,_frame_info->crop
		));
	}
}

void Graphics::drawFrameInfo(Frame *_frame_info){
	drawFrameInfo(_frame_info, 0,0);
}

void Graphics::drawTilemap(
	Tilemap *_tilemap
){
	if(_tilemap != NULL){
		//_tilemap->draw(this);
		Image *image=_tilemap->getImage();
		if(image!=NULL){
			SDL_Texture *sdl_texture=image->getSdlTexture();
			if(image != NULL){

				int offset_x=_tilemap->offset_x;
				int offset_y=_tilemap->offset_y;
				int tile_width=_tilemap->getTileWidth();
				int tile_height=_tilemap->getTileHeight();
				int tilemap_width=_tilemap->getTilemapWidth();
				int tilemap_height=_tilemap->getTilemapHeight();
				//int tilemap_size=_tilemap->getTotalTiles();
				auto tiles=_tilemap->getTiles();
				auto tm_grid_format = _tilemap->getTilemapGridFormat();//tm_grid_format;
				auto tm_tiles_per_span=_tilemap->getTilesPerSpan();//tm_tiles_per_span;
				int tilemap_size=tiles->size();

				float dst_x=offset_x*g_graphics_display_scalex;
				float dst_y=offset_y*g_graphics_display_scaley;
				float dst_w=tile_width*g_graphics_display_scalex;
				float dst_h=tile_height*g_graphics_display_scaley;

				SDL_Rect dst_rect={
					0
					,0
					,(int)(dst_w)+1
					,(int)(dst_h)+1
				};


				SDL_Rect src_rect={
					0
					,0
					,tile_width
					,tile_height
				};

				// for each tile
				for(int y=0; y < tilemap_height;y++,dst_y+=dst_h){
					dst_x=g_graphics_startx+offset_x*g_graphics_display_scalex;
					for(int x=0; x < tilemap_width;x++,dst_x+=dst_w){
						int offset=y*tilemap_width+x;

						if(offset<tilemap_size){

							short tile=tiles->at(offset);

							// get only tile >0
							if(tile > 0){
								int tile_x=((tile-1)%tm_tiles_per_span);
								int tile_y=((tile-1)/tm_tiles_per_span);

								tile_x+=tm_grid_format.offset_tile_u;
								tile_y+=tm_grid_format.offset_tile_v;

								src_rect.x=tile_x*(tile_width+tm_grid_format.margin_u)+tm_grid_format.offset_u;
								src_rect.y=tile_y*(tile_height+tm_grid_format.margin_v)+tm_grid_format.offset_v;

								dst_rect.x=dst_x-1;
								dst_rect.y=dst_y-1;

								// render image at current position
								if(SDL_RenderCopy(
										g_graphics_renderer
										,sdl_texture
										,&src_rect
										,&dst_rect)!=0){
									fprintf(stderr
										,"SDL_RenderCopy: %s"
										,SDL_GetError()
									);
								}
							}
						}
					}
				}
			}
		}
	}
}

void Graphics::drawCollider(
		Collider *_collider
		,int _x_center
		,int _y_center
		, int _color
){
	//BitMaskCollider *bitmask_collider=NULL;

	switch(_collider->collider_type){
	case Collider::COLLIDER_TYPE_RECTANGLE:
		drawRectangle(
			_x_center
			,_y_center
			,_collider->width
			,_collider->height
			,_color
		);
		break;
	case Collider::COLLIDER_TYPE_CIRCLE:
		drawEllipse(
			_x_center
			,_y_center
			,_collider->width
			,_collider->height
			,_color
		);
		break;
	default:
		break;

	}
}

void Graphics::update(){

	// if g_graphics_fullscreen draws left/right block
	if(g_graphics_fullscreen){
		SDL_Rect rect;

		SDL_SetRenderDrawColor(g_graphics_renderer
			,0
			,0
			,0
			,0					// alpha
		);

		rect.x=0;
		rect.y=0;
		rect.w=g_graphics_fullscreen_startx;
		rect.h=g_graphics_rect_display[g_graphics_active_display].h;

		SDL_RenderFillRect(g_graphics_renderer, &rect);

		rect.x=g_graphics_rect_display[g_graphics_active_display].w-g_graphics_fullscreen_startx;
		rect.y=0;
		rect.w=g_graphics_fullscreen_startx;
		rect.h=g_graphics_rect_display[g_graphics_active_display].h;

		SDL_RenderFillRect(g_graphics_renderer, &rect);
	}

	// using a software g_graphics_renderer there's no wait vertical synchronization, so
	// it waits 60FPS (~16ms) by software
    while (SDL_GetTicks() < g_graphics_last_time) {
        SDL_Delay(1);
    }

	SDL_RenderPresent( g_graphics_renderer );

	// save current time to wait other 16 ms
	g_graphics_last_time=SDL_GetTicks()+TICKS_FOR_NEXT_FRAME;
}

void Graphics::toggleFullscreen(){

	setFullscreen(!g_graphics_fullscreen);
}

void Graphics::calculeScaleFactors(){
	g_graphics_aspect=((float)g_graphics_width/(float)g_graphics_height)/((float)g_graphics_rect_display[g_graphics_active_display].w/(float)g_graphics_rect_display[g_graphics_active_display].h);
	g_graphics_fullscreen_startx=(g_graphics_rect_display[g_graphics_active_display].w>>1)-(g_graphics_rect_display[g_graphics_active_display].w*g_graphics_aspect*0.5);
	g_graphics_display_scalex=((float)g_graphics_rect_display[g_graphics_active_display].w/(float)(g_graphics_width))*g_graphics_aspect;
	g_graphics_display_scaley=(float)g_graphics_rect_display[g_graphics_active_display].h/(float)(g_graphics_height);
	g_graphics_startx=g_graphics_fullscreen_startx;
}

void 	Graphics::setFullscreen(bool _fullscreen){
	if(!g_graphics_fullscreen){
		int wx=0,wy=0;
		SDL_GetWindowPosition(g_graphics_window,&wx,&wy);
		g_graphics_active_display=-1;
		for(int i=0; (i < g_graphics_num_displays) && (g_graphics_active_display==-1);i++){
			if(g_graphics_rect_display[i].x<=wx && wx<(g_graphics_rect_display[i].x+g_graphics_rect_display[i].w)){
				g_graphics_active_display=i;
			}
		}


		//SDL_SetWindowBordered( g_graphics_window, SDL_FALSE );
		SDL_SetWindowFullscreen(g_graphics_window,SDL_WINDOW_FULLSCREEN_DESKTOP);
		// FULLSCREEN
		calculeScaleFactors();

		SDL_SetWindowPosition(
			g_graphics_window
			, g_graphics_rect_display[g_graphics_active_display].x
			, g_graphics_rect_display[g_graphics_active_display].y-1
		);

		/*SDL_SetWindowSize(
			g_graphics_window
			, g_graphics_rect_display.w
			,g_graphics_rect_display.h
		);*/

	}else{
		// WINDOWED
		//SDL_SetWindowBordered( g_graphics_window, SDL_TRUE );

		g_graphics_display_scalex=1;
		g_graphics_display_scaley=1;
		g_graphics_startx=0;

		SDL_SetWindowFullscreen(g_graphics_window,0);


		SDL_SetWindowPosition(
			g_graphics_window
			, g_graphics_rect_display[g_graphics_active_display].x+(g_graphics_rect_display[g_graphics_active_display].w>>1)-(g_graphics_width>>1)
			,g_graphics_rect_display[g_graphics_active_display].y+(g_graphics_rect_display[g_graphics_active_display].h>>1)-(g_graphics_height>>1)
		);

		SDL_SetWindowSize(
			g_graphics_window
			, g_graphics_width
			,g_graphics_height
		);
	}

	g_graphics_fullscreen=_fullscreen;
}

void  Graphics::toggleShowSpriteColliders(){
	g_graphics_show_sprite_colliders=!g_graphics_show_sprite_colliders;
}

void Graphics::deInit(){
	if(g_graphics_renderer != NULL){
		SDL_DestroyRenderer(g_graphics_renderer);
	}

	if(g_graphics_window != NULL){
		SDL_DestroyWindow(g_graphics_window);
	}

	if(g_graphics_rect_display!=NULL){
		free(g_graphics_rect_display);
	}

	g_graphics_rect_display=NULL;
	g_graphics_renderer=NULL;
	g_graphics_window=NULL;
	SDL_Quit();
}
