/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

class Tilemap;
class Entity;
class Frame;
class Collider;
class Graphics{

public:



	static int 				getWidth();
	static int 				getHeight();

	static void 				createWindow(
			int _width
			, int _height
			,const std::string & _title="invader"
			,const std::string & _icon=""
			,bool _fullscreen=false
	);
	static void 				toggleFullscreen();
	static void 				toggleShowSpriteColliders();
	static SDL_Renderer 	*	getRenderer();
	static SDL_Window 		*	getWindow();

	static void 				clear(Uint8 r, Uint8 g, Uint8 b);
	static void 				setTitle(const std::string & _tile);
	static void 				setIcon(const std::string & _file);
	static void 				drawEllipse( int _x_center, int _y_center, int radius_x, int radius_y,  int _rgb=-1);
	static void 				drawPoint( int _x, int _y, int _rgb=-1);
	static void 				drawRectangle( int _x_center, int _y_center, int _width, int _height,  int _rgb=-1);
	static void					drawFilledRectangle( int _x_center, int _y_center, int _width, int _height,  int _rgb=-1);
	static void 				drawCross( int _x_center, int _y_center, int _width, int _height, int _thickness,  int _rgb=-1);
	static void 				drawImage(Image *img,int _x_center, int _y_center,  const ImageDrawOptions & _draw_image_options=ImageDrawOptions());
	static void 				drawText(Font * font,int _x,int _y,  const std::string & text, const FontDrawOptions & _draw_font_options=FontDrawOptions());
	static void 				drawEntity(Entity *_entity);
	static void 				drawEntity(Entity *_entity,int _x_center, int _y_center);
	static void 				drawFrameInfo(Frame *_frame_info,int _x_center, int _y_center);
	static void 				drawFrameInfo(Frame *_frame_info);
	static void 				drawTilemap(Tilemap *_tilemap);
	static void					drawCollider(Collider *_collider,int _x_center, int _y_center,int _color=-1);
	static Uint8  				getBytesPerPixel(void);


	static void 				update();
	static void 				deInit();

private:

	static void 				setFullscreen(bool _fullscreen);
	static void 				calculeScaleFactors();


};

