#include "@animation.h"

#define CAST_BEZIER_POINT(p) ((KeyframePoint *)(p))


//---------------------------------------------------------------------------------------------------
// PUBLIC
KeyframeTrack::KeyframeTrack()
{
	ease = EaseType::EASE_TYPE_LINEAR;
	minx_interval = FLT_MAX,
	maxx_interval = FLT_MIN,
	rangex_interval   = FLT_MIN;
	rangex_interval_pow2 = 0;
	dxdt_pow2 =  1;
	properties=0;
	configured_interpolator=false;

}


//---------------------------------------------------------------------------------------------------
// STATIC

void KeyframeTrack::calculeFx(
	  KeyframePoint * result
	, const float  ini_point[I1D_POINT_SIZE]
	, const  float   ini_control_point_1[I1D_POINT_SIZE]
	, const  float  ini_control_point_2[I1D_POINT_SIZE]
	, float iv_ini
	, const float  end_point[I1D_POINT_SIZE]
	, const  float  end_control_point_1[I1D_POINT_SIZE]
    , const  float  end_control_point_2[I1D_POINT_SIZE]
    , float iv_end)
{

	UNUSUED_PARAM(ini_control_point_1);
	UNUSUED_PARAM(ini_control_point_2);
	UNUSUED_PARAM(end_control_point_1);
	UNUSUED_PARAM(end_control_point_2);

	//
	// PRE: Assumes that result, ini_point && end_point is equal to n_dimension

	float diff = (iv_end-iv_ini);
	float inc_one_over_diff_interval = 1.0f/(diff);

	result->inc_fx[I1D_IDX_VALUE] = (end_point[I1D_IDX_VALUE]-ini_point[I1D_IDX_VALUE])/diff;
	result->inc_one_over_diff_interval = inc_one_over_diff_interval;
}
//---------------------------------------------------------------------------------------------------
// PRIVATE
void KeyframeTrack::setEase( EaseType  _ease){
	this->ease=_ease;
}
//---
void KeyframeTrack::clear(){
	this->keyframe_points.clear();
}
//---
void KeyframeTrack::addKeyframesFloat(const std::vector<float> & _points)
{
	// PRE:
	// point[x1,x2,...xn-1]: Dependen var (x,y,z, etc).
	// point[xn]: Independent var (time).
	if(_points.size()==0){ // no keyframe_points...
		return;
	}

	if(_points.size() % I1D_POINT_SIZE != 0)
	{
		LOG_ERROR("Error! Data length is not equal to dimension+1");
		return;
	}

	int number_keyframes = _points.size()/I1D_POINT_SIZE;
	KeyframePoint new_data, previus_data;

	// Get the independent point...
	float x_ini, x_actual, x_old;
	float x_end;


	int i;
	int length_offset = I1D_POINT_SIZE;
	x_actual = _points[I1D_IDX_TIME];


	x_old = x_actual-1.0f;
	//x_actual = point[N_DIMENSION];
	int actual_offset = 0;


	for(i = 0; i < number_keyframes; i++)
	{
		x_actual = _points[actual_offset + I1D_IDX_TIME];

		if(x_actual < x_old)
		{
			LOG_ERROR("Malformed list point at index %i (independent variable is not ascendent) (last independent x: %f,current independent x: %f)",i,x_old, x_actual);

			return;
		}

		KeyframePoint new_data;

		// copy first point...
		new_data.point[I1D_IDX_TIME] 		  = _points[actual_offset + I1D_IDX_TIME];
		new_data.point[I1D_IDX_VALUE] 		  = _points[actual_offset + I1D_IDX_VALUE];

		// Interpolates with prevous point...
		if(i > 0)
		{
			previus_data = this->keyframe_points[i-1];
			KeyframeTrack::calculeFx(
					&previus_data,
					previus_data.point,
					previus_data.control_point_1,
					previus_data.control_point_2,
					previus_data.point[I1D_IDX_TIME],
					new_data.point,
					new_data.control_point_1,
					new_data.control_point_2,
					new_data.point[I1D_IDX_TIME]
			);

			this->keyframe_points[i-1] = previus_data;
		}

		this->keyframe_points.insert(this->keyframe_points.begin()+i, new_data);
		x_old = x_actual;
		actual_offset += length_offset;
	}

	x_end = _points[(number_keyframes-1)*length_offset+ I1D_IDX_TIME];
	x_ini = _points[(0)*length_offset +              I1D_IDX_TIME];

	this->minx_interval = MIN(this->minx_interval, x_ini);
	this->maxx_interval = MAX(this->maxx_interval, x_end);

	this->rangex_interval = this->maxx_interval-this->minx_interval;
}
//---
void KeyframeTrack::setKeyframes(const std::vector<float> & _points)
{
	clear();
	addKeyframesFloat(_points);

	// optimization independent var as pow2
	this->rangex_interval_pow2=Bit::nextPow2(this->rangex_interval);
	this->dxdt_pow2=(float)this->rangex_interval_pow2/this->rangex_interval;
	this->properties|=KEYFRAME_TRACK_PROPERTY_TIME_POW_2;

	// TODO: set all independent keyframe_points 1/maxx_interval_mask;
}
//---
void KeyframeTrack::addKeyframesBezier(const std::vector<KeyframePoint> & _keyframe_points)
{
	// PRE:
	// point[x1,x2,...xn-1]: Dependen var (x,y,z, etc).
	// point[xn]: Independent var (time).
	int x_actual=-1;
	int x_old=-1;


	KeyframePoint new_data,first_point, last_point;

	for(unsigned i = 0; i < _keyframe_points.size(); i++)
	{
		KeyframePoint bp_actual=_keyframe_points[i];

		x_actual = bp_actual.point[I1D_IDX_TIME];//actual_offset + 2*I1D_IDX_TIME];

		if(x_actual < x_old)
		{
			LOG_ERROR("Malformed list point at index %i (independent variable is not ascendent) (p: %i,a: %i)",i,x_old, x_actual);

			return;
		}

		KeyframePoint new_data;

		for(unsigned j=0; j< I1D_POINT_SIZE; j++){
			new_data.control_point_1[j] 	= bp_actual.control_point_1[j];
			new_data.point[j]				= bp_actual.point[j];
			new_data.control_point_2[j] 	= bp_actual.control_point_2[j];
		}

		// Interpolates with prevous point...
		if(i > 0)
		{
			KeyframePoint previus_data = this->keyframe_points[i-1];
			KeyframeTrack::calculeFx(
					&previus_data,
					previus_data.point,
					previus_data.control_point_1,
					previus_data.control_point_2,
					previus_data.point[I1D_IDX_TIME],
					new_data.point,
					new_data.control_point_1,
					new_data.control_point_2,
					new_data.point[I1D_IDX_TIME]
			);
		}

		this->keyframe_points.insert(this->keyframe_points.begin()+i, new_data);

		x_old = x_actual;
	}

	first_point=_keyframe_points[0];
	last_point=_keyframe_points[_keyframe_points.size()-1];

	this->minx_interval = MIN(this->minx_interval, last_point.point[I1D_IDX_TIME]);
	this->maxx_interval = MAX(this->maxx_interval, first_point.point[I1D_IDX_TIME]);

	this->rangex_interval = this->maxx_interval-this->minx_interval;
}
//---
bool KeyframeTrack::interpolate(float _t, float * _value)
{
	bool ok=false;

	// And then get the point...
	if(this->keyframe_points.size() < 1) // ---> No values ...
	{
		return false;
	}

	if(this->keyframe_points.size() == 1) // ---> No interpolation, holds same value all time...
	{
		*_value = this->keyframe_points[0].point[I1D_IDX_VALUE];
		return true;
	}

	if(_t <= this->minx_interval)  // return first value...
	{

		*_value = this->keyframe_points[0].point[1];
		return true;
	}

	if(_t >= this->maxx_interval) // return last value...
	{
		*_value = this->keyframe_points[this->keyframe_points.size()-1].point[1];
		return true;
	}

	// search span and interpolate usign ease function
	for(unsigned i = 0; i <this->keyframe_points.size()-1; i++)
	{
		ok=true;
		KeyframePoint point_i1 = this->keyframe_points[i];
		KeyframePoint point_i2 = this->keyframe_points[i+1];
		float interpolate_value=0;

		if(_t >= point_i1.point[I1D_IDX_TIME] && //.independent_variable &&
				_t < point_i2.point[I1D_IDX_TIME]  //.independent_variable
		) // Calcule interpolated point...
		{
			float normalized_t=(_t-point_i1.point[I1D_IDX_TIME])*point_i1.inc_one_over_diff_interval;
			switch(this->ease)
			{
			/*case EASE_BEZIER:
				LOG_ERROR("Bezier interpolator not implemented");
				break;*/
			default:
			case EASE_TYPE_LINEAR:
				interpolate_value=Ease::linear(normalized_t);
				break;

			case EASE_TYPE_IN_OUT_SINE:
				interpolate_value=Ease::inOutSine(normalized_t);
				break;
			}

			*_value=point_i1.point[I1D_IDX_VALUE] + interpolate_value*(point_i2.point[I1D_IDX_VALUE]-point_i1.point[I1D_IDX_VALUE]);
		}
	}

	return ok;
}
//---
KeyframeTrack::~KeyframeTrack()
{
	clear();
}

