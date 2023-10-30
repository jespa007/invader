/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
#pragma once

class Graphics;
class Collider{
public:
	typedef enum{
		COLLIDER_TYPE_NONE=0,
		COLLIDER_TYPE_RECTANGLE,
		COLLIDER_TYPE_CIRCLE
	}ColliderType;


	int width,height;
	ColliderType collider_type;

	static bool testIntersectionRectangleRectangle(
		  int _c1_x
		, int _c1_y
		, int _c1_w
		, int _c1_h
		, int _c2_x
		, int _c2_y
		, int _c2_w
		, int _c2_h
	);

	static bool testIntersectionRectangleCircle(
		  int _c1_x
		, int _c1_y
		, int _c1_w
		, int _c1_h
		, int _c2_x
		, int _c2_y
		, int _c2_r
	);

	static bool testIntersectionCircleCircle(
		  int _c1_x
		, int _c1_y
		, int _c1_r
		, int _c2_x
		, int _c2_y
		, int _c2_r
	);

	static Collider newCollider2dTypeRectangle(int _width, int _height);
	static Collider newCollider2dTypeCircle(int _radius);
	static bool testIntersection(
		int c1_x
		,int c1_y
		,const Collider * _c1
		,int c2_x
		,int c2_y
		,const Collider * _c2
	);

	Collider();
	Collider(ColliderType _type, int _dimx, int _dimy);
	Collider & operator =(const Collider & _collider);

	virtual ~Collider();
private:

	void copy(const Collider & _collider);

};
