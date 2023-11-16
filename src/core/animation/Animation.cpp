#include "@animation.h"



void Animation::onResetChannels(void (*_on_reset_channels)(ChannelsInfo *_channels_info, void *_user_data), void *_user_data){
	channels_info->on_set_channels.ptr_function=_on_reset_channels;
	channels_info->on_set_channels.user_data=_user_data;
}

void Animation::onSetChannels(void (*_on_set_channels)(ChannelsInfo *_channels_info, void *user_data), void *_user_data){
	channels_info->on_set_channels.ptr_function=_on_set_channels;
	channels_info->on_set_channels.user_data=_user_data;
}


//--------------------------------------------------------------------------------------------------------------------------------------
// STATIC FUNCTIONS

uint32_t Animation::getDefaultStartTimeTriggerAction(void *user_data){
	UNUSUED_PARAM(user_data);
	return SDL_GetTicks();
}


//--------------------------------------------------------------------------------------------------------------------------------------
// PUBLIC FUNCTIONS


Animation::Animation(uint8_t n_channels){

	channels_info=new ChannelsInfo(n_channels);
	tween=new Tween(n_channels);
}

/**
 * Trigger action (independent to time line)
 */
void Animation::startAction(Action *_action,uint32_t _start_time, int _repeat){
	if(channels_info->n_channels != _action->channels_info->n_channels){
		LOG_ERROR("Internal error animation components (%i) != action components (%i)"
				,channels_info->n_channels
				,channels_info->n_channels);
		return;
	}

	info_actions.push_back(CInfoAction(
		_action
		,_start_time
		,_repeat
	));

}

/**
 * Remove action to time line
 */
void Animation::clearAction(Action *_action){
	for(unsigned i = 0; i < info_actions.size(); i++){
		if(info_actions[i].action == _action){
			//InfoAniAction_Delete((InfoAction *)info_actions->items[i]);
			info_actions.erase(info_actions.begin()+i);
			return;
		}
	}
	//LOG_WARNING("action not exist");
}

void Animation::startTween(
		  uint32_t _start_time
		, uint8_t _idx_channel
		, EaseType _ease
		, float _from
		, float _to
		, uint32_t _duration
		, int _repeat
){
	tween->start(_start_time,_idx_channel, _ease, _from, _to, _duration,_repeat);

}

void Animation::clear(){
	// TODO:
	info_actions.clear();

}

void Animation::copyChannelValues( float *_dest_copy){
	channels_info->copyTo(_dest_copy);
}

bool Animation::update( uint32_t _time){
	bool updated=(info_actions.size()>0) || (tween->channels_info->msk_active_channels != 0);
	unsigned i=0;
	/*if(channels_info->on_reset_channels.ptr_function!=NULL){
		channels_info->on_reset_channels.ptr_function(channels_info,channels_info->on_reset_channels.user_data);
	}*/

	CInfoAction *ptr_info_actions=info_actions.data();

	// for all info_actions... make ops.
	// update triggered info_actions
	while(i< info_actions.size()){

		CInfoAction *info_action=ptr_info_actions+i;
		bool update_action = true;

		// render frame...
		if(info_action->action->update(
				_time
				,&info_action->start_time
				,&info_action->repeat
		)==false){ //remove action...
			update_action=false;
		}

		// update last channels...
		ChannelsInfo::copy(channels_info,info_action->action->channels_info);
		channels_info->msk_active_channels |= info_action->action->channels_info->msk_active_channels;


		if(update_action){
			i++;
		}else{ // remove
			info_actions.erase(info_actions.begin()+i);
		}
	}

	if(tween->channels_info->msk_active_channels != 0){
		tween->update(_time);
		ChannelsInfo::copy(channels_info,tween->channels_info);
	}

	return updated;
}


Animation::~Animation(){

	clear();

	delete channels_info;
	delete tween;

}


