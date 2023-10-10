/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "invader.h"

bool Collider::testIntersectionRectangleRectangle(
		  int _c1_x
		, int _c1_y
		, int _c1_w
		, int _c1_h
		, int _c2_x
		, int _c2_y
		, int _c2_w
		, int _c2_h
){

	int w1_med=_c1_w*0.5;
	int w2_med=_c2_w*0.5;
	int h1_med=_c1_h*0.5;
	int h2_med=_c2_h*0.5;

	if (_c1_x + w1_med < _c2_x - w2_med) {
		return false;
	}
	if (_c1_y + h1_med < _c2_y - h2_med) {
		return false;
	}
	if (_c1_x - w1_med > _c2_x + w2_med) {
		return false;
	}
	if (_c1_y - h1_med > _c2_y + h2_med) {
		return false;
	}
	return true;
}

bool Collider::testIntersectionRectangleCircle(
	  int _c1_x
	, int _c1_y
	, int _c1_w
	, int _c1_h
	, int _c2_x
	, int _c2_y
	, int _c2_r){
	int w1_med=_c1_w*0.5;
	int h1_med=_c1_h*0.5;

	int circle_distance_x = fabs(_c2_x - _c1_x);
	int circle_distance_y = fabs(_c2_y - _c1_y);

   	if (circle_distance_x > (w1_med + _c2_r)) { return false; }
   	if (circle_distance_y > (h1_med + _c2_r)) { return false; }

   	if (circle_distance_x <= (w1_med)) { return true; }
   	if (circle_distance_y <= (h1_med)) { return true; };

   	int xdiff=circle_distance_x-w1_med;
   	int ydiff=circle_distance_y-h1_med;

   	int corner_distance=(xdiff)*(xdiff)+
						  (ydiff)*(ydiff);

	return corner_distance<=_c2_r*_c2_r;
}

bool Collider::testIntersectionCircleCircle(
	  int _c1_x
	, int _c1_y
	, int _c1_r
	, int _c2_x
	, int _c2_y
	, int _c2_r){

	int xdiff=fabs(_c1_x-_c2_x);
	int ydiff=fabs(_c1_y-_c2_y);

	int distance=(xdiff)*(xdiff)+
					  (ydiff)*(ydiff);

	return distance < _c1_r*_c1_r || distance < _c2_r*_c2_r;

}

Collider::Collider(){
	this->collider_type=COLLIDER_TYPE_NONE;
	this->width=0;
	this->height=0;
}

Collider::Collider(ColliderType _type, int _dimx, int _dimy){
	this->collider_type=_type;
	this->width=_dimx;
	this->height=_dimy;
}

void Collider::copy(const Collider & _collider){
	this->collider_type=_collider.collider_type;
	this->width=_collider.width;
	this->height=_collider.height;
}

Collider & Collider::operator =(const Collider & _collider){
	copy(_collider);
	return *this;
}


bool Collider::testIntersection(
		 int _c1_x
		, int _c1_y
		, const Collider * _c1
		, int _c2_x
		, int _c2_y
		, const Collider * _c2){

	if(_c1 == NULL){
		//fprintf(stderr,"collider 1 (_c1) is NULL\n");
		return false;
	}

	if(_c2 == NULL){
		//fprintf(stderr,"collider 2 (_c2) is NULL\n");
		return false;
	}


	if(_c1->collider_type == ColliderType::COLLIDER_TYPE_NONE || _c2->collider_type == ColliderType::COLLIDER_TYPE_NONE){
		return false;
	}

	bool test=false;
	// check collision and set line red if collides
	switch(_c1->collider_type){
	case COLLIDER_TYPE_NONE:
		break;
	case COLLIDER_TYPE_RECTANGLE:
		switch(_c2->collider_type){
		case COLLIDER_TYPE_RECTANGLE:
			test=Collider::testIntersectionRectangleRectangle(
					_c1_x
					,_c1_y
					,_c1->width
					,_c1->height
					,_c2_x
					,_c2_y
					,_c2->width
					,_c2->height
			);
			break;
		case COLLIDER_TYPE_CIRCLE:

			test=Collider::testIntersectionRectangleCircle(
					_c1_x
					,_c1_y
					,_c1->width
					,_c1->height
					,_c2_x
					,_c2_y
					,_c2->width
			);
			break;
		default:
			break;
		}
		break;
	case COLLIDER_TYPE_CIRCLE:
		switch(_c2->collider_type){
		case COLLIDER_TYPE_RECTANGLE:
			test=Collider::testIntersectionRectangleCircle(
					_c2_x
					,_c2_y
					,_c2->width
					,_c2->height
					,_c1_x
					,_c1_y
					,_c1->width

			);
			break;
		case COLLIDER_TYPE_CIRCLE:

			test=Collider::testIntersectionCircleCircle(
					_c1_x
					,_c1_y
					,_c1->width
					,_c2_x
					,_c2_y
					,_c2->width
			);
			break;
		default:
			break;
		}
		break;
	default:
		break;


	}

	return test;
}


Collider::~Collider(){

}

