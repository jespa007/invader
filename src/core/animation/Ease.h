#pragma once
typedef enum{
	EASE_TYPE_CUSTOM=0,
	EASE_TYPE_LINEAR,
	EASE_TYPE_IN_SINE,
	EASE_TYPE_OUT_SINE,
	EASE_TYPE_IN_OUT_SINE,
	EASE_TYPE_IN_QUAD,
	EASE_TYPE_OUT_QUAD,
	EASE_TYPE_IN_OUT_QUAD,
	EASE_TYPE_IN_CUBIC,
	EASE_TYPE_OUT_CUBIC,
	EASE_TYPE_IN_OUT_CUBIC,
	EASE_TYPE_IN_QUART,
	EASE_TYPE_OUT_QUART,
	EASE_TYPE_IN_OUT_QUART,
	EASE_TYPE_IN_QUINT,
	EASE_TYPE_OUT_QUINT,
	EASE_TYPE_IN_OUT_QUINT,
	EASE_TYPE_IN_EXPO,
	EASE_TYPE_OUT_EXPO,
	EASE_TYPE_IN_OUT_EXPO,
	EASE_TYPE_IN_CIRC,
	EASE_TYPE_OUT_CIRC,
	EASE_TYPE_IN_OUT_CIRC,
	EASE_TYPE_IN_BACK,
	EASE_TYPE_OUT_BACK,
	EASE_TYPE_IN_OUT_BACK,
	EASE_TYPE_IN_ELASTIC,
	EASE_TYPE_OUT_ELASTIC,
	EASE_TYPE_IN_OUT_ELASTIC,
	EASE_TYPE_IN_BOUNCE,
	EASE_TYPE_OUT_BOUNCE,
	EASE_TYPE_IN_OUT_BOUNCE,

}EaseType;

class Ease{
public:
	static double linear( double t );
	static double inSine( double t );
	static double outSine( double t );
	static double inOutSine( double t );
	static double inQuad( double t );
	static double outQuad( double t );
	static double inOutQuad( double t );
	static double inCubic( double t );
	static double outCubic( double t );
	static double inOutCubic( double t );
	static double inQuart( double t );
	static double outQuart( double t );
	static double inOutQuart( double t );
	static double inQuint( double t );
	static double outQuint( double t );
	static double inOutQuint( double t );
	static double inExpo( double t );
	static double outExpo( double t );
	static double inOutExpo( double t );
	static double inCirc( double t );
	static double outCirc( double t );
	static double inOutCirc( double t );
	static double inBack( double t );
	static double outBack( double t );
	static double inOutBack( double t );
	static double inElastic( double t );
	static double outElastic( double t );
	static double inOutElastic( double t );
	static double inBounce( double t );
	static double outBounce( double t );
	static double inOutBounce( double t );
};


