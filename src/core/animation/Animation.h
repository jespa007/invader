#pragma once

#define ANIMATION_LOOP_REPEAT_INFINITE	-1

class Animation{

public:
	typedef struct{
		uint32_t (* ptr_function)(void * user_data);
		void * user_data;
	} CallbackAnimationTime;

	Animation(uint8_t n_channels);

	void setCallbackAnimationTime(CallbackAnimationTime cf);
	void addChannel(ChannelsInfo *ac);

	void onResetChannels(void (*)(ChannelsInfo *_channels_info,void * _user_data), void *_user_data);
	void onSetChannels(void (*)(ChannelsInfo *_channels_info, void *_user_data), void *_user_data);

	/**
	 * Erase component
	 */
	void eraseChannel( ChannelsInfo *ac);

	/**
	 * Add action to time line
	 */
	void startAction( Action *_action,uint32_t _start_time, int _repeat);

	/**
	 * Add action to time line
	 */
	void clearAction(Action *_action);

	/**
	 * Trigger action (independent to time line)
	 */
	void startTween(
			 uint32_t _start_time
			, uint8_t  _idx_channel
			, EaseType  _ease
			, float _from
			, float _to
			, uint32_t _duration
			, int _repeat);


	void clear();
	void copyChannelValues(float *_dest_copy);
	bool update(uint32_t _time);

	~Animation();

private:

	class CInfoAction{
	public:
		Action *action;
		uint32_t start_time;
		int repeat;

		CInfoAction(Action *_action,uint32_t _start_time, int  _repeat){
			this->start_time=_start_time; // only for triggered info_actions...
			this->repeat=_repeat;
			this->action = _action;
		}
	};

	std::vector<CInfoAction> info_actions;
	Tween  *tween;
	ChannelsInfo 	*channels_info;

	static uint32_t getDefaultStartTimeTriggerAction(void *user_data);

};
