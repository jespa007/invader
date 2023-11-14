#pragma once

class Tween{

public:

	typedef enum{
		TWEEN_PROPERTY_PING_PONG=0x1<<0
	}TweenPropery;

	ChannelsInfo	*channels_info;
	TweenChannel	*tween_channels;

	Tween(Uint8 _n_channels);

	void start(
			uint32_t _start_time
			, uint8_t _idx_channel
			, EaseType  _ease
			, float _from
			, float _to
			, uint32_t _duration
			, int _repeat
			);

	void update(uint32_t _time);

	~Tween();


};


