#include "@animation.h"

double Ease::linear( double t ){
	return t;
}

double Ease::inSine( double t ) {
	return sin( 1.5707963 * t );
}

double Ease::outSine( double t ) {
	return 1 + sin( 1.5707963 * (--t) );
}

double Ease::inOutSine( double t ) {
	return 0.5 * (1 + sin( 3.1415926 * (t - 0.5) ) );
}

double Ease::inQuad( double t ) {
    return t * t;
}

double Ease::outQuad( double t ) {
    return t * (2 - t);
}

double Ease::inOutQuad( double t ) {
    return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
}

double Ease::inCubic( double t ) {
    return t * t * t;
}

double Ease::outCubic( double t ) {
    return 1 + (t-1) * t * t;
}

double Ease::inOutCubic( double t ) {
    return t < 0.5 ? 4 * t * t * t : 1 + (t-1) * (2 * (t-1)) * (2 * t);
}

double Ease::inQuart( double t ) {
    t *= t;
    return t * t;
}

double Ease::outQuart( double t ) {
    t = (t-1) * t;
    return 1 - t * t;
}

double Ease::inOutQuart( double t ) {
    if( t < 0.5 ) {
        t *= t;
        return 8 * t * t;
    } else {
        t = (t-1) * t;
        return 1 - 8 * t * t;
    }
}

double Ease::inQuint( double t ) {
    double t2 = t * t;
    return t * t2 * t2;
}

double Ease::outQuint( double t ) {
    double t2 = (t-1) * t;
    return 1 + t * t2 * t2;
}

double Ease::inOutQuint( double t ) {
    double t2;
    if( t < 0.5 ) {
        t2 = t * t;
        return 16 * t * t2 * t2;
    } else {
        t2 = (t-1) * t;
        return 1 + 16 * t * t2 * t2;
    }
}

double Ease::inExpo( double t ) {
    return (pow( 2, 8 * t ) - 1) / 255;
}

double Ease::outExpo( double t ) {
    return 1 - pow( 2, -8 * t );
}

double Ease::inOutExpo( double t ) {
    if( t < 0.5 ) {
        return (pow( 2, 16 * t ) - 1) / 510;
    } else {
        return 1 - 0.5 * pow( 2, -16 * (t - 0.5) );
    }
}

double Ease::inCirc( double t ) {
    return 1 - sqrt( 1 - t );
}

double Ease::outCirc( double t ) {
    return sqrt( t );
}

double Ease::inOutCirc( double t ) {
    if( t < 0.5 ) {
        return (1 - sqrt( 1 - 2 * t )) * 0.5;
    } else {
        return (1 + sqrt( 2 * t - 1 )) * 0.5;
    }
}

double Ease::inBack( double t ) {
    return t * t * (2.70158 * t - 1.70158);
}

double Ease::outBack( double t ) {
    return 1 + (t-1) * t * (2.70158 * t + 1.70158);
}

double Ease::inOutBack( double t ) {
    if( t < 0.5 ) {
        return t * t * (7 * t - 2.5) * 2;
    } else {
        return 1 + (t-1) * t * 2 * (7 * t + 2.5);
    }
}

double Ease::inElastic( double t ) {
    double t2 = t * t;
    return t2 * t2 * sin( t * _PI * 4.5 );
}

double Ease::outElastic( double t ) {
    double t2 = (t - 1) * (t - 1);
    return 1 - t2 * t2 * cos( t * _PI * 4.5 );
}

double Ease::inOutElastic( double t ) {
    double t2;
    if( t < 0.45 ) {
        t2 = t * t;
        return 8 * t2 * t2 * sin( t * _PI * 9 );
    } else if( t < 0.55 ) {
        return 0.5 + 0.75 * sin( t * _PI * 4 );
    } else {
        t2 = (t - 1) * (t - 1);
        return 1 - 8 * t2 * t2 * sin( t * _PI * 9 );
    }
}

double Ease::inBounce( double t ) {
    return pow( 2, 6 * (t - 1) ) * abs( sin( t * _PI * 3.5 ) );
}

double Ease::outBounce( double t ) {
    return 1 - pow( 2, -6 * t ) * abs( cos( t * _PI * 3.5 ) );
}

double Ease::inOutBounce( double t ) {
    if( t < 0.5 ) {
        return 8 * pow( 2, 8 * (t - 1) ) * abs( sin( t * _PI * 7 ) );
    } else {
        return 1 - 8 * pow( 2, -8 * t ) * abs( sin( t * _PI * 7 ) );
    }
}
