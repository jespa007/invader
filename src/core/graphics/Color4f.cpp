#include "@graphics.h"

Color4f Color4f::BLACK=Color4f(0,0,0,1);
Color4f Color4f::WHITE=Color4f(1,1,1,1);
Color4f Color4f::RED=Color4f(1,0,0,1);
Color4f Color4f::YELLOW=Color4f(1.0f,1.0f,0.0f,1);
Color4f Color4f::GREEN=Color4f(0.0f,1.0f,0.0f,1);
Color4f Color4f::GRAY=Color4f(0.5f,0.5f,0.5f,1);



Color4f Color4f::fromColor3i(int r, int g, int b){
	Color4f color;
	color.set(
		(float)(((unsigned)r)&0xff)*ONE_OVER_256
		,(float)(((unsigned)g)&0xff)*ONE_OVER_256
		,(float)(((unsigned)b)&0xff)*ONE_OVER_256
		,1
	);

	return color;
}

Color4f::Color4f(float _r, float _g, float _b, float _a){
	set(
		_r
		,_g
		,_b
		,_a
	);
}
