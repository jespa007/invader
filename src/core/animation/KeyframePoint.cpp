#include "@animation.h"

KeyframePoint::KeyframePoint(){
	memset(this->point,0,sizeof(this->point));
	memset(this->control_point_1,0,sizeof(this->control_point_1));
	memset(this->control_point_2,0,sizeof(this->control_point_2));
	memset(this->inc_fx,0,sizeof(this->inc_fx));

	inc_one_over_diff_interval=0;
}

KeyframePoint::~KeyframePoint(){
}
