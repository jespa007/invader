/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

#include "FontDrawOptions.h"
#include "FontLoadOptions.h"

class Font:public Image{

public:

	static Font *getDefaultFont();
	static Font *newFont(
			const std::string & _name
			,const std::string & _file
			,int _char_width
			,int _char_height
			,const FontLoadOptions & _font_load_options=FontLoadOptions()
	);
	static Font *get(const std::string & name);
	static void unloadAll();
	static void destroy();


	int getCharWidth();
	int getCharHeight();
	int getTextWith(const std::string & str, const FontDrawOptions &_font_draw_options=FontDrawOptions());
	SDL_Rect getRectChar(char c);


private:

	static Font *default_font;
	static std::map<std::string,Font *> *s_fonts;
	static std::map<std::string, Font *> *getMap();

	int totalchars_x, totalchars_y,totalchars;
	SDL_Rect m_aux_rect;
	int char_width,char_height;

	Font();

	bool load(
			unsigned char *buf
			, size_t buf_size
			,int char_width
			,int char_height
			,const FontLoadOptions &_font_load_options=FontLoadOptions()
	);

	bool load(
			 const std::string & _file
			,int _char_width
			,int _char_height
			,const FontLoadOptions &_font_load_options=FontLoadOptions());



	~Font();

};
