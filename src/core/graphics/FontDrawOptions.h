/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

class FontDrawOptions{
public:
	int font_height;
	int color;


	FontDrawOptions(){
		font_height=-1;
		color=-1;
	}

	FontDrawOptions(
		int _font_height
		,int _color

	){
		font_height=_font_height;
		color=_color;
	}

};
