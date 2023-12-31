#include "@graphics.h"

//--------------------------------------------------------------------------------------------------------------------------------
SDL_Surface * SDL_CreateSurfaceFrom(
		uint16_t w
		, uint16_t h,
		uint8_t _bytes_per_pixel, uint8_t *pixels) {

	// 24 bit default.
	uint32_t rmask = RMASK32, gmask = GMASK32, bmask = BMASK32, amask = 0;
	uint8_t bytes_per_pixel=_bytes_per_pixel;

	if(bytes_per_pixel == 0){
		bytes_per_pixel = Graphics::getBytesPerPixel();
	}

	switch (bytes_per_pixel) {
	default:
		LOG_ERROR("Bytes per pixel %i unsupportted", bytes_per_pixel);
		return NULL;
		break;
	case COLOR_RGB8: // paletted mode
		rmask = 0;
		gmask = 0;
		bmask = 0;
		amask = 0;
		break;
	case COLOR_RGB16:
		rmask = RMASK16;
		gmask = GMASK16;
		bmask = BMASK16;
		amask = AMASK16;

		break;
	case COLOR_RGB24:
	case COLOR_RGBA32:
		amask = AMASK32;
		break;
	}

	SDL_Surface *srf_info = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h,
			bytes_per_pixel * 8, rmask, gmask, bmask, amask);

	if(srf_info==NULL){
		LOG_ERROR("Cannot create SDL Surface %s", SDL_GetError());
		return NULL;
	}

	if (pixels) {
		memcpy(srf_info->pixels, pixels, w * h * bytes_per_pixel);
	}
	return srf_info;

}

SDL_Surface *SDL_NewSurface(uint16_t w, uint16_t h, uint8_t bytes_per_pixel){

	return SDL_CreateSurfaceFrom(w,h,bytes_per_pixel,NULL);
}

/*
 * This is a 32-bit pixel function created with help from this
 * website: http://www.libsdl.org/intro.en/usingvideo.html
 *
 * You will need to make changes if you want it to work with
 * 8-, 16- or 24-bit surfaces.  Consult the above website for
 * more information.
 */
void SDL_SetPixel(SDL_Surface *surface, int x, int y, uint32_t pixel)
{

	uint8_t bytes_per_pixel=surface->format->BytesPerPixel;
	uint8_t *target_pixel = (uint8_t *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;
	memcpy(target_pixel, &pixel,bytes_per_pixel);
}


/*
 * This is an implementation of the Midpoint Circle Algorithm
 * found on Wikipedia at the following link:
 *
 *   http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
 *
 * The algorithm elegantly draws a circle quickly, using a
 * set_pixel function for clarity.
 */
void SDL_DrawCircle(SDL_Surface *surface, int n_cx, int n_cy, int radius, uint32_t pixel)
{
	// if the first pixel in the screen is represented by (0,0) (which is in sdl)
	// remember that the beginning of the circle is not in the middle of the pixel
	// but to the left-top from it:

	double error = (double)-radius;
	double x = (double)radius -0.5;
	double y = (double)0.5;
	double cx = n_cx - 0.5;
	double cy = n_cy - 0.5;

	double transX = 0;//cx-surface->w;
	double transY = 0;//cy-surface->h;

	if(transX<0)
		transX=0;

	if(transY<0)
		transY=0;

	while (x >= y)
	{
		SDL_SetPixel(surface, (int)(cx + x+transX), (int)(cy + y+transY), pixel);
		SDL_SetPixel(surface, (int)(cx + y+transX), (int)(cy + x+transY), pixel);

		if (x != 0)
		{
			SDL_SetPixel(surface, (int)(cx - x+transX), (int)(cy + y+transY), pixel);
			SDL_SetPixel(surface, (int)(cx + y+transX), (int)(cy - x+transY), pixel);
		}

		if (y != 0)
		{
			SDL_SetPixel(surface, (int)(cx + x+transX), (int)(cy - y+transY), pixel);
			SDL_SetPixel(surface, (int)(cx - y+transX), (int)(cy + x+transY), pixel);
		}

		if (x != 0 && y != 0)
		{
			SDL_SetPixel(surface, (int)(cx - x+transX), (int)(cy - y+transY), pixel);
			SDL_SetPixel(surface, (int)(cx - y+transX), (int)(cy - x+transY), pixel);
		}

		error += y;
		++y;
		error += y;

		if (error >= 0)
		{
			--x;
			error -= x;
			error -= x;
		}
	}
}


/*
 * SDL_Surface 32-bit circle-fill algorithm without using trig
 *
 * While I humbly call this "Celdecea's Method", odds are that the
 * procedure has already been documented somewhere uint32_t ago.  All of
 * the circle-fill examples I came across utilized trig functions or
 * scanning neighbor pixels.  This algorithm identifies the width of
 * a semi-circle at each pixel height and draws a scan-line covering
 * that width.
 *
 * The code is not optimized but very fast, owing to the fact that it
 * alters pixels in the provided surface directly rather than through
 * function calls.
 *
 * WARNING:  This function does not lock surfaces before altering, so
 * use SDL_LockSurface in any release situation.
 */
void SDL_FillCircle(SDL_Surface *surface, int cx, int cy, int radius, uint32_t pixel)
{
	// Note that there is more to altering the bitrate of this
	// method than just changing this value.  See how pixels are
	// altered at the following web page for tips:
	//   http://www.libsdl.org/intro.en/usingvideo.html
	uint8_t bytes_per_pixel = surface->format->BytesPerPixel;

	double r = (double)radius;

	for (double dy = 1; dy <= r; dy += 1.0)
	{
		// This loop is unrolled a bit, only iterating through half of the
		// height of the circle.  The result is used to draw a scan line and
		// its mirror image below it.

		// The following formula has been simplified from our original.  We
		// are using half of the width of the circle because we are provided
		// with a center and we need left/right coordinates.

		double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
		int x = cx - dx;

		// Grab a pointer to the left-most pixel for each half of the circle
		uint8_t *target_pixel_a = (uint8_t *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * bytes_per_pixel;
		uint8_t *target_pixel_b = (uint8_t *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * bytes_per_pixel;

		for (; x <= cx + dx; x++)
		{
			memcpy(target_pixel_a, &pixel,bytes_per_pixel);
			memcpy(target_pixel_b, &pixel,bytes_per_pixel);

			target_pixel_a += bytes_per_pixel;
			target_pixel_b += bytes_per_pixel;
		}
	}
}

SDL_Surface * SDL_NewCircle(uint16_t radius, uint32_t fill_color, uint16_t width_border, uint32_t border_color){
	int r1 = radius*2;
	int r2 = radius*2-width_border*2;
	uint8_t bytes_per_pixel=Graphics::getBytesPerPixel();

	if((r1 > 0 && r2 > 0)){

		SDL_Surface *srf1 = SDL_NewSurface(r1,r1,bytes_per_pixel);
		SDL_Surface *srf2 = SDL_NewSurface(r2,r2,bytes_per_pixel);

		SDL_FillCircle( srf1, radius,radius,radius, border_color);
		SDL_FillCircle( srf2, radius-width_border,radius-width_border,radius-width_border, fill_color);

		SDL_Rect rect={width_border,width_border,srf2->w, srf2->h};
		SDL_BlitSurface(srf2,NULL, srf1,&rect);
		SDL_FreeSurface(srf2);


		//draw_circle();
		return srf1;
	}
	return NULL;

}

/*SDL_Surface *surface SDL_NewCircle2(int cx, int cy, int radius, uint32_t pixel)
{
	// Note that there is more to altering the bitrate of this
	// method than just changing this value.  See how pixels are
	// altered at the following web page for tips:
	//   http://www.libsdl.org/intro.en/usingvideo.html
	static const int BPP = 3;

	double r = (double)radius;

	for (double dy = 1; dy <= r; dy += 1.0)
	{
		// This loop is unrolled a bit, only iterating through half of the
		// height of the circle.  The result is used to draw a scan line and
		// its mirror image below it.

		// The following formula has been simplified from our original.  We
		// are using half of the width of the circle because we are provided
		// with a center and we need left/right coordinates.

		double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
		int x = cx - dx;

		// Grab a pointer to the left-most pixel for each half of the circle
		uint8_t *target_pixel_a = (uint8_t *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
		uint8_t *target_pixel_b = (uint8_t *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;

		for (; x <= cx + dx; x++)
		{
			*(uint32_t *)target_pixel_a = pixel;
			*(uint32_t *)target_pixel_b = pixel;
			target_pixel_a += BPP;
			target_pixel_b += BPP;
		}
	}
}*/

SDL_Surface   * SDL_NewCross(uint16_t dimension, uint32_t fill_color, uint16_t border_width){

	//ZG_UNUSUED_PARAM(border_color);

	if(dimension < 32){ // minimum is 32 ...
		dimension = 32;
	}


	int r1 = dimension*2;
	if(border_width < 2){ // be sure that the cross will be 2 for be visible ...
		border_width = 2;
	}


	SDL_Rect rect[]={
			{r1/2-(border_width/2),							  0,border_width,r1}, // vertical
			{							 0,r1/2-(border_width/2),r1,border_width}  // horizontal
	};

	SDL_Surface *srf1 = SDL_NewSurface(r1,r1,4);

	// paint a vertical line
	SDL_FillRect(srf1,&rect[0], fill_color);

	// paint a horizontal lone line
	SDL_FillRect(srf1,&rect[1], fill_color);

	return srf1;


}

SDL_Surface * SDL_NewRectangle2d(uint16_t dimension,  uint32_t fill_color, uint16_t border_width, uint32_t border_color){
	if(dimension < 32){
		dimension = 32;
	}

	if(border_width >= dimension){
		border_width = dimension -1;
	}

	int r1 = dimension*2; // border color...
	int r2 = dimension*2-border_width*2; // filled color


	SDL_Surface *srf1 = SDL_NewSurface(r1,r1,4);
	SDL_Surface *srf2 = SDL_NewSurface(r2,r2,4);

	SDL_FillRect(srf1,NULL, border_color);
	SDL_FillRect(srf2,NULL, fill_color);
	//fill_square( srf1, dimension,dimension,borderColor);//(0xff<<24)|(r<<16)|(g<<8)|(b<<0) );
	//fill_square( srf2, dimension-width_border,dimension-width_border,fillColor);//(0xff<<24)|(r<<16)|(g<<8)|(b<<0) );

	SDL_Rect rect={border_width,border_width,srf2->w, srf2->h};
	SDL_BlitSurface(srf2,NULL, srf1,&rect);
	SDL_FreeSurface(srf2);

	//draw_circle();
	return srf1;
}

/*
SDL_Surface * SDL_NewTriangle(uint16_t dimension, uint32_t fill_color, uint16_t border_width, uint32_t border_color){
	ZG_UNUSUED_PARAM(border_color);
	return NULL;
}
*/


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SDL_Surface *	SDL_ConvertSurfaceExt(SDL_Surface *src_surface, uint32_t properties_format,	uint8_t convert_to_bytes_per_pixel) {

	SDL_Surface *new_surface=NULL;
	SDL_Surface *allocated_surface = NULL;

	if(convert_to_bytes_per_pixel != 0){ // user want some bytes per pixel

		if(src_surface->format->BytesPerPixel == 1){ // special copy...
			new_surface = SDL_CreateSurfaceFrom(src_surface->w, src_surface->h, 4,NULL); // 32 bits
			uint8_t *src_p = (uint8_t *)src_surface->pixels;
			uint32_t *dst_p = (uint32_t *)new_surface->pixels;
			SDL_Color *p_color=src_surface->format->palette->colors;

			for(int y = 0; y < src_surface->h; y++)
				for(int x = 0; x < src_surface->w; x++){
					uint8_t aux_pixel = *src_p;
					(*dst_p) = (uint32_t)p_color[aux_pixel].r | ((uint32_t)p_color[aux_pixel].g << 8)| ((uint32_t)p_color[aux_pixel].b << 16) | (((uint32_t)p_color[aux_pixel].a) << 24);
					src_p++;
					dst_p++;
				}
		}
		else{
			new_surface = SDL_CreateSurfaceFrom(src_surface->w, src_surface->h, convert_to_bytes_per_pixel,NULL);
			SDL_BlitSurface(src_surface,NULL,new_surface,NULL);
		}

		src_surface = new_surface;
		allocated_surface = new_surface;
	}

	short destWidth = src_surface->w;
	short destHeight = src_surface->h;


	if((properties_format & SDL_LOAD_IMAGE_POWER_OF_2_ORIGINAL_RESOLUTION) ==SDL_LOAD_IMAGE_POWER_OF_2_ORIGINAL_RESOLUTION ||
			((destWidth == src_surface->w) && (destHeight == src_surface->h))
	){ // simple copy original image...
		new_surface = SDL_CreateSurfaceFrom(destWidth, destHeight, src_surface->format->BytesPerPixel,NULL);
		// and just blit...
		SDL_BlitSurface(src_surface,NULL,new_surface,NULL);

	}else{ //scale to fit image (warning may have a bug with copying rgb values !!!)...
		new_surface = SDL_NewSurface(destWidth,destHeight,src_surface->format->BytesPerPixel);
		if(SDL_BlitScaled(src_surface,
					   NULL,
					   new_surface,
					   NULL)!=0){
			LOG_ERROR("SDL_BlitScaled:%s",SDL_GetError());
		}

	}


	if (properties_format & SDL_LOAD_IMAGE_FLIP_Y) {
		SDL_FlipY(new_surface);
	}

	if(allocated_surface != NULL)
	{
		SDL_FreeSurface(allocated_surface);
	}

	return new_surface;

}

void SDL_FlipY(SDL_Surface *surface){
	int size_scanline = surface->w*surface->format->BytesPerPixel;
	uint8_t *src_up   = (uint8_t *)surface->pixels;
	uint8_t *src_down = ((uint8_t *)surface->pixels+(surface->h-1)*size_scanline);
	uint8_t * aux_scanline = (uint8_t *)malloc(size_scanline);
	for(int y = 0; y < surface->h/2; y++){

		memcpy(aux_scanline, src_up	  		,size_scanline);
		memcpy(src_up		, src_down		,size_scanline);
		memcpy(src_down		, aux_scanline	,size_scanline);

		src_up	+=size_scanline;
		src_down-=size_scanline;

	}

	free(aux_scanline);
}

void SDL_SetBytesPerPixel(SDL_Surface **srf, uint8_t new_bytes_per_pixel){
	if(srf != NULL && *srf != NULL){
		if((*srf)->format->BytesPerPixel !=new_bytes_per_pixel){
			SDL_Surface *new_surf = SDL_ConvertSurface(*srf,0,new_bytes_per_pixel);
			if(new_surf){
				SDL_FreeSurface(*srf);
				*srf = new_surf;
			}
		}
	}
}

SDL_Surface *	SDL_Crop(SDL_Surface *_src_surface,SDL_Rect _src_rect){
	//SDL_Rect dst_rect={0,0,_src_rect.w,_src_rect.h};
	SDL_Surface *dst_surface=SDL_CreateSurfaceFrom(
				 _src_rect.w
				, _src_rect.h
				,_src_surface->format->BytesPerPixel
				,NULL // we don't want to copy pixels
            );

	SDL_BlitSurface(_src_surface, & _src_rect, dst_surface, NULL);

	return dst_surface;

}


uint32_t SDL_Color2Html(SDL_Color c){
	return (c.a<<24) | (c.r << 16) | (c.g << 8) | (c.b << 0);
}

SDL_Color SDL_Html2Color(uint32_t html){
	SDL_Color color;
	color.r=(html&0xFF0000)>>16;
	color.g=(html&0x00FF00)>>8;
	color.b=(html&0x0000FF)>>0;
	color.a=0xFF;


	return color;
}

bool 		 	SDL_SavePNG(SDL_Surface * _srf,const char * _filename){
	unsigned error=0;
	uint8_t *out;
	size_t outsize;
	bool ok=false;

	if(_srf!=NULL){
		LodePNGColorType color_type;

		switch(_srf->format->BitsPerPixel){
		case 24:
			color_type=LCT_RGB;
			break;
		case 32:
			color_type=LCT_RGBA;
			break;
		default:
			LOG_ERROR("SDL_SavePNG : Error saving %s. Unsupported bit depth",_filename);
			return false;

		}

		//unsigned lodepng_encode_memory(unsigned char** out, size_t* outsize, const unsigned char* image,
		//                               unsigned w, unsigned h, LodePNGColorType colortype, unsigned bitdepth)
		error=lodepng_encode_memory(&out,&outsize,(const unsigned char *)_srf->pixels,_srf->w,_srf->h,color_type,8);
		if(!error){
			//ByteBuffer bb=ByteBuffer(out,outsize);
			//ok=File::write(_filename,bb);
			lodepng_save_file(out,outsize,_filename);
			free(out);
		}else{
			LOG_ERROR("SDL_SavePNG : Error saving %s. %s",_filename,lodepng_error_text(error));
		}
	}

	return ok;
}
