/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

class TilemapGridFormat{
public:
	int offset_u;
	int offset_v;
	int offset_tile_u;
	int offset_tile_v;
	int margin_u;
	int margin_v;
	int width;


	TilemapGridFormat(){
		offset_u=0;
		offset_v=0;
		offset_tile_u=0;
		offset_tile_v=0;
		margin_u=0;
		margin_v=0;
		width=0;

	}

	TilemapGridFormat(
		int _offset_u
		,int _offset_v
		,int _offset_tile_u
		,int _offset_tile_v
		,int _margin_u
		,int _margin_v
		,int _width

	){
		offset_u=_offset_u;
		offset_v=_offset_v;
		offset_tile_u=_offset_tile_u;
		offset_tile_v=_offset_tile_v;
		margin_u=_margin_u;
		margin_v=_margin_v;
		width=_width;
	}

};
