/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

#include "Tile.h"
#include "TilemapGridFormat.h"

class Image;
class Entity;
class Tilemap{
public:

	int offset_x,offset_y;

	Tilemap();


	void setup(
		Image *_image
		, const std::vector<short> & _tiles
		, int _tilemap_width
		, int _tilemap_height
		, int _tile_width
		, int _tile_height
		, const TilemapGridFormat & _tm_grid_properties=TilemapGridFormat()
	);

	int getTilemapWidth();
	int getTilemapWidthPixels();

	int getTilemapHeight();
	int getTileWidth();
	int getTileHeight();
	int getTilesPerSpan();
	Image *getImage();
	const TilemapGridFormat & getTilemapGridFormat();
	TilemapGridFormat *getGridFormatReference();

	std::vector<short> *getTiles();

	Tile getTile(unsigned _offset);
	Tile getTile(int _tile_x, int _tile_y);
	Tile getTileFromEntity(Entity *_entity);
	Tile getTileFromPosition(int _position_x, int _position_y);

	~Tilemap();

private:

	std::vector<short> tiles;

	// the offset in the screen

	int tilemap_width;
	int tilemap_height;
	int tile_width;
	int tile_height;
	int tilemap_width_pixels;
	TilemapGridFormat tm_grid_format;
	int tm_tiles_per_span;
	int tilemap_size;
	Image  *image;

	void destroy();

};
