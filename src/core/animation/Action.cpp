#include "@animation.h"

Action::Action(uint8_t n_channels){
	channels_info=NULL;
	channel_keyframe_tracks=NULL;
	duration=0;
	min_time_ms=0;
	max_time_ms=0;

	channels_info=new ChannelsInfo(n_channels);

	channel_keyframe_tracks=new KeyframeTrack[n_channels];

}


void 	Action::setKeyframesTrack(
		 uint8_t idx_channel
		, EaseType ease
		,const std::vector<float> & _points
){

	if(idx_channel >= this->channels_info->n_channels){
		LOG_ERROR("Internal error index reached max channels");
		return;
	}

	this->channel_keyframe_tracks[idx_channel].setEase(ease);
	this->channel_keyframe_tracks[idx_channel].setKeyframes(_points);

	this->min_time_ms=MIN(this->min_time_ms,this->channel_keyframe_tracks[idx_channel].minx_interval);
	this->max_time_ms=MAX(this->max_time_ms,this->channel_keyframe_tracks[idx_channel].maxx_interval);

	this->duration = this->max_time_ms - this->min_time_ms;

	this->channels_info->msk_active_channels|=(0x1<<idx_channel);
}


void 				Action::setKeyframesTrackGroup(
		uint8_t idx_channel_first
		,uint32_t msk_keyframe_track_group
		, EaseType _ease
		,const std::vector<float > & _points
){
	KeyframeTrackGroup *x=NULL, *y=NULL, *z=NULL, *w=NULL;
	KeyframeTrackGroup group_track_x,group_track_y,group_track_z,group_track_w;

	switch(msk_keyframe_track_group){
	case KEYFRAME_TRACK_GROUP_COMPONENT_X:
		x=&group_track_x;
		break;
	case KEYFRAME_TRACK_GROUP_COMPONENT_Y:
		y=&group_track_y;
		break;
	case KEYFRAME_TRACK_GROUP_COMPONENT_Z:
		z=&group_track_z;
		break;
	case KEYFRAME_TRACK_GROUP_COMPONENT_W:
		w=&group_track_w;
		break;
	case KEYFRAME_TRACK_GROUP_COMPONENT_X | KEYFRAME_TRACK_GROUP_COMPONENT_Y:
		x=&group_track_x;
		y=&group_track_y;
		break;
	case KEYFRAME_TRACK_GROUP_COMPONENT_X | KEYFRAME_TRACK_GROUP_COMPONENT_Y | KEYFRAME_TRACK_GROUP_COMPONENT_Z:
		x=&group_track_x;
		y=&group_track_y;
		z=&group_track_z;
		break;
	case KEYFRAME_TRACK_GROUP_COMPONENT_X | KEYFRAME_TRACK_GROUP_COMPONENT_Y | KEYFRAME_TRACK_GROUP_COMPONENT_Z | KEYFRAME_TRACK_GROUP_COMPONENT_W:
		x=&group_track_x;
		y=&group_track_y;
		z=&group_track_z;
		w=&group_track_w;
		break;
	default:
		LOG_ERROR("Action::setKeyframes: invalid mask");
		break;
	}

	if(KeyframeTrackGroup::decomposeXYZW(_points,x,y,z,w)){

		if(x != NULL){
			setKeyframesTrack(idx_channel_first+0,_ease,x->points);
		}

		if(y!=NULL){
			setKeyframesTrack(idx_channel_first+1,_ease,y->points);
		}

		if(z!=NULL){
			setKeyframesTrack(idx_channel_first+2,_ease,z->points);
		}

		if(w!=NULL){
			setKeyframesTrack(idx_channel_first+3,_ease,w->points);
		}
	}
}

bool Action::update(uint32_t current_time_ms, uint32_t *start_time_ms, int * repeat){

	float point=0;
	bool update=true;

	if(this->channels_info == NULL){
		return false;
	}

	// reset components to unit...
	if(this->channels_info->on_reset_channels.ptr_function!=NULL){
		this->channels_info->on_reset_channels.ptr_function(this->channels_info,this->channels_info->on_reset_channels.user_data);
	}

	uint32_t time_ms=current_time_ms-*start_time_ms;//[MAX_MATERIAL_COMPONENTS];

	if(
		(time_ms < this->duration ) || ((time_ms >= this->duration)
		&& (((*repeat) > 0) || ((*repeat) < 0)))
	){

		if(time_ms >= this->duration ) {// clamp start time
			*start_time_ms=current_time_ms;// set start time

			if(*repeat > 0){
				(*repeat)--;
			}

			// clamp
			time_ms %= this->duration;
		}
	}else{ //update last
		update=false;
	}

	// update all channels...
	for(int i = 0; i < this->channels_info->n_channels; i++){
		if(this->channel_keyframe_tracks[i].interpolate(time_ms,&point)){
			this->channels_info->channels[i]  = point;
		}
	}

	return update;
}

void Action::unload(){
	if(this->channel_keyframe_tracks !=NULL){
		delete [] this->channel_keyframe_tracks;
		this->channel_keyframe_tracks=NULL;
	}
}

Action::~Action(){
	unload();
	delete channels_info;
}


