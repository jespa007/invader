#pragma once


//--------------------- PROPERTIES ------
#define	KEYFRAME_TRACK_PROPERTY_TIME_POW_2 	(0x1 << 0)


class KeyframeTrack{
public:
	std::vector<KeyframePoint> 	keyframe_points;

	float							minx_interval,// = 0.0f,
									maxx_interval,// = 1.0f,
									dxdt_pow2,
									rangex_interval;//   = 1.0f;

	uint32_t						rangex_interval_pow2;
	bool 							configured_interpolator;
	EaseType						ease;

	uint32_t 						properties;

	//--------------------------------------------------------------------------------------------------------
	// PUBLIC
	KeyframeTrack();

	void			setEase( EaseType  _ease);
	void 			clear();
	void 			setKeyframes(const std::vector<float> & _keyframe_points);
	void 			addKeyframesFloat(const std::vector<float> & _keyframe_points);
	void 			addKeyframesBezier(const std::vector<KeyframePoint> & _keyframe_points);
	bool 			interpolate( float _t, float * _result);

	~KeyframeTrack();
private:


	//--------------------------------------------------------------------------------------------------------
	// STATIC
	static void calculeFx(KeyframePoint * result
		, const float  ini_point[I1D_POINT_SIZE]
		, const float  ini_control_point_1[I1D_POINT_SIZE]
		, const float  ini_control_point_2[I1D_POINT_SIZE]
		, float iv_ini
		, const float end_point[I1D_POINT_SIZE]
		, const float end_control_point_1[I1D_POINT_SIZE]
		, const float end_control_point_2[I1D_POINT_SIZE]
		, float iv_end);



};
