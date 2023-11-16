#pragma once

class Action{
public:
	ChannelsInfo		*channels_info;
	KeyframeTrack 		*channel_keyframe_tracks;
	uint32_t 	   		duration;
	uint32_t 			min_time_ms;
	uint32_t 			max_time_ms;

	// member
	Action(uint8_t n_channels);

	bool 			update(uint32_t current_ms, uint32_t *start_time_ms, int *repeat);

	void 			setKeyframesTrack(
			uint8_t idx_channel
			, EaseType _ease
			,const std::vector<float> & _keyframe_points
	);

	void 			setKeyframesTrackGroup(
			uint8_t idx_channel_first
			,uint32_t msk_keyframe_track_group
			, EaseType _ease
			,const std::vector<float> & _keyframe_points
	);

	void			unload();
	~Action();
};





