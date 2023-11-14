#pragma once

class TweenChannel{
public:
	float to,from;
	uint32_t start_time;
	EaseType ease;
	int repeat;
	uint32_t duration;
	float one_over_duration;
};

