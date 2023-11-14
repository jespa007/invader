#pragma once

// A way to describe packed units for each type (example translation,rotation,etc ) in order to decompose in 1d
#define KEYFRAME_TRACK_GROUP_COMPONENT_X (0x1 << 0)
#define KEYFRAME_TRACK_GROUP_COMPONENT_Y (0x1 << 1)
#define KEYFRAME_TRACK_GROUP_COMPONENT_Z (0x1 << 2)
#define KEYFRAME_TRACK_GROUP_COMPONENT_W (0x1 << 3)


class KeyframeTrackGroup{
public:
	std::vector<float>  points;

	static bool decomposeXYZW(
			const std::vector<float> & _points
			, KeyframeTrackGroup * vx
			, KeyframeTrackGroup * vy
			, KeyframeTrackGroup * vz
			, KeyframeTrackGroup * vw
		);


	KeyframeTrackGroup(void);
	~KeyframeTrackGroup();
};

