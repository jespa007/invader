/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

class ImageDrawOptions{
public:
	int color;
	float scalex;
	float scaley;
	SDL_Rect crop;

	ImageDrawOptions(){
		color=-1;
		scalex=1;
		scaley=1;
		crop={0,0,0,0};
	}

	ImageDrawOptions(
		int _color
		,SDL_Rect _crop={0,0,0,0}
		,float _scalex=1
		,float _scaley=1

	){
		color=_color;
		crop=_crop;
		scalex=_scalex;
		scaley=_scaley;
	}

};
