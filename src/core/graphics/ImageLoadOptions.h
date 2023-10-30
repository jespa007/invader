/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

class ImageLoadOptions{
public:
	int color_key;


	ImageLoadOptions(){
		color_key=-1;
	}

	ImageLoadOptions(
		int _color_key
	){
		color_key=_color_key;
	}

};
