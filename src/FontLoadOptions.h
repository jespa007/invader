/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

class FontLoadOptions{
public:
	int color_key;


	FontLoadOptions(){
		color_key=-1;
	}

	FontLoadOptions(
		int _color_key
	){
		color_key=_color_key;
	}

};
