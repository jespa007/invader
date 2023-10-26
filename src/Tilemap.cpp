/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "Invader.h"



//-------
// Member
Tilemap::Tilemap(){
	tilemap_width=0;
	tilemap_height=0;
	tile_width=1;
	tile_height=1;

	tm_tiles_per_span=0;
	tilemap_size=0;
	image=NULL;
	offset_x=0;
	offset_y=0;
	tilemap_width_pixels=0;
}

void Tilemap::setup(
	Image *_image
	, const std::vector<short> & _tiles
	, int _tilemap_width
	, int _tilemap_height
	, int _tile_width
	, int _tile_height
	, const TilemapGridFormat & _tm_grid_format
){

	destroy();

	if(_image==NULL){
		fprintf(stderr,"image == null\n");
		return;
	}

	if(_tile_width==0){
		fprintf(stderr,"_tile_width == 0\n");
		return;
	}

	if(_tile_height==0){
		fprintf(stderr,"_tile_height == 0\n");
		return;
	}

	if(_tilemap_width==0){
		fprintf(stderr,"_tilemap_width == 0\n");
		return;
	}

	if(_tilemap_height==0){
		fprintf(stderr,"_tilemap_height == 0\n");
		return;
	}

	image=_image;
	tiles=_tiles;

	tile_width=_tile_width;
	tile_height=_tile_height;

	tilemap_width=_tilemap_width;
	tilemap_height=_tilemap_height;

	tilemap_width_pixels=_tilemap_width*_tile_width;

	tm_grid_format=_tm_grid_format;

	tm_tiles_per_span=_image->getWidth()/tile_width;

	if(tm_grid_format.width){
		tm_tiles_per_span=tm_grid_format.width;
	}

	tilemap_size=tilemap_width*tilemap_height;

	printf(
	   "New tilemap\n"
	   "--------------\n"
	   "- Total tiles : '%i' tiles\n"
	   "- Tile resolution: '%ix%i' texels\n"
	   "- Tilemap resolution : '%ix%i' tiles ('%ix%i' texels )\n"
		,tilemap_size
		,tile_width
		,tile_height
		,tilemap_width
		,tilemap_height
		,tilemap_width*tile_width
		,tilemap_height*tile_height
	);

	printf(
		"- Offset u : %i\n"
		"- Offset v : %i\n"
		"- Offset tile u : %i\n"
		"- Offset tile v : %i\n"
		"- Margin u : %i\n"
		"- Margin v : %i\n"
		,tm_grid_format.offset_u
		,tm_grid_format.offset_v
		,tm_grid_format.offset_tile_u
		,tm_grid_format.offset_tile_v
		,tm_grid_format.margin_u
		,tm_grid_format.margin_v
	);


}

int Tilemap::getTilemapWidth(){
	return this->tilemap_width;
}

int Tilemap::getTilemapWidthPixels(){
	return this->tilemap_width_pixels;
}

int Tilemap::getTilemapHeight(){
	return this->tilemap_height;
}

int Tilemap::getTileWidth(){
	return this->tile_width;
}

int Tilemap::getTilesPerSpan(){
	return tm_tiles_per_span;
}

Image *Tilemap::getImage(){
	return image;
}

const TilemapGridFormat & Tilemap::getTilemapGridFormat(){
	return this->tm_grid_format;
}

TilemapGridFormat *Tilemap::getGridFormatReference(){
	return &this->tm_grid_format;
}

int Tilemap::getTileHeight(){
	return this->tile_height;
}

std::vector<short> *Tilemap::getTiles(){
	return &this->tiles;
}

Tile Tilemap::getTile(unsigned _offset){
	int x=_offset%this->tilemap_width;
	int y=_offset/this->tilemap_width;
	return getTile(x, y);
}

Tile Tilemap::getTile(int _tile_x, int _tile_y){


	if(_tile_x<0
	||_tile_x>=this->tilemap_width
	||_tile_y < 0
	||_tile_y>=this->tilemap_height
	){
		// out of scope, return invalid tile
		return Tile();
	}

	int offset=_tile_y*this->tilemap_width+_tile_x;

	return Tile(
		// id
		offset
		// the tile num
		,this->tiles[offset]
		// tile position in the tilemap
		,_tile_x
		,_tile_y
		,_tile_x-1>=0?this->tiles[offset-1]:-1 // left
		,_tile_x+1<tilemap_width?this->tiles[offset+1]:-1 // right
		,_tile_y-1>=0?this->tiles[offset-this->tilemap_width]:-1 // up
		,_tile_y+1<tilemap_height?this->tiles[offset+this->tilemap_width]:-1 // down
		// centered position
		,this->offset_x+this->tile_width*_tile_x+(this->tile_width>>1)
		,this->offset_y+this->tile_height*_tile_y+(this->tile_height>>1)
	);
}

Tile Tilemap::getTileFromPosition(int _position_x, int _position_y){
	return getTile(
		(_position_x-this->offset_x)/this->tile_width
		,(_position_y-this->offset_y)/this->tile_height
	);
}

Tile Tilemap::getTileFromEntity(Entity *_entity){
	return getTileFromPosition(_entity->x, _entity->y);
}

void Tilemap::destroy(){
	tiles.clear();
	tilemap_width=0;
	tilemap_height=0;
	tile_width=0;
	tile_height=0;

	tm_tiles_per_span=0;
	tilemap_size=0;
	image=NULL;;
}

Tilemap::~Tilemap(){
	destroy();
}
