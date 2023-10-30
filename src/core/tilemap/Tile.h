#pragma once

struct Tile{
	bool is_valid;
	int tile_offset;
	int tile_value;
	int tile_x;
	int tile_y;
	int tile_left_value;
	int tile_right_value;
	int tile_up_value;
	int tile_down_value;

	int centered_absolute_x, centered_absolute_y;

	Tile(){
		is_valid=false;
		tile_offset=-1;
		tile_value=-1;
		tile_x=-1;
		tile_y=-1;
		tile_left_value=-1;
		tile_right_value=-1;
		tile_up_value=-1;
		tile_down_value=-1;
		centered_absolute_x=-1;
		centered_absolute_y=-1;
	}

	Tile(
			int _tile_offset
			,int _tile_value
			,int _tile_x
			,int _tile_y
			,int _tile_left_value
			,int _tile_right_value
			,int _tile_up_value
			,int _tile_down_value
			,int _centered_absolute_x
			,int _centered_absolute_y
	){
		is_valid=true;
		tile_offset=_tile_offset;
		tile_value=_tile_value;
		tile_x=_tile_x;
		tile_y=_tile_y;
		tile_left_value=_tile_left_value;
		tile_right_value=_tile_right_value;
		tile_up_value=_tile_up_value;
		tile_down_value=_tile_down_value;
		centered_absolute_x=_centered_absolute_x;
		centered_absolute_y=_centered_absolute_y;
	}

	Tile (const Tile & _tile){
		set(_tile);
	}

	Tile & operator =(const Tile & _tile){
		set(_tile);
		return *this;
	}

private:
	void set(
			const Tile & _tile
	){
		is_valid=_tile.is_valid;
		tile_offset=_tile.tile_offset;
		tile_value=_tile.tile_value;
		tile_x=_tile.tile_x;
		tile_y=_tile.tile_y;
		tile_left_value=_tile.tile_left_value;
		tile_right_value=_tile.tile_right_value;
		tile_up_value=_tile.tile_up_value;
		tile_down_value=_tile.tile_down_value;
		centered_absolute_x=_tile.centered_absolute_x;
		centered_absolute_y=_tile.centered_absolute_y;
	}
};
