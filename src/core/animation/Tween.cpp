#include "@animation.h"

Tween::Tween(Uint8 _n_channels){
	channels_info=new ChannelsInfo(_n_channels);
	tween_channels=new TweenChannel[_n_channels];

}

void Tween::start(
		 uint32_t _start_time
		, uint8_t _idx_channel
		, EaseType _ease
		, float _from
		, float _to
		, uint32_t _duration
		, int _repeat){
	TweenChannel *tc=NULL;

	if(_idx_channel > this->channels_info->n_channels){
		LOG_ERROR("reached max channels (%i > %i)",_idx_channel,this->channels_info->n_channels);
		return;
	}

	tc=tween_channels+_idx_channel;
	tc->duration=_duration;
	tc->ease=_ease;
	tc->from=_from;
	tc->to=_to;
	tc->start_time=_start_time;
	tc->repeat = _repeat;
	tc->one_over_duration=1.0f/_duration;

	// mark channel active
	this->channels_info->msk_active_channels|=0x1<<_idx_channel;
}

void Tween::update(uint32_t _time){
	if(this->channels_info->msk_active_channels){
		for(unsigned i = 0; i < this->channels_info->n_channels; i++){
			if(this->channels_info->msk_active_channels & (0x1<<i)){ // update
				TweenChannel *tween_channel=this->tween_channels+i;
				uint32_t diff_time=_time-tween_channel->start_time;
				if(diff_time >= tween_channel->duration &&  tween_channel->repeat < 0){
					diff_time=(_time-tween_channel->start_time)%tween_channel->duration;
				}
				float t = diff_time*tween_channel->one_over_duration;
				float value=tween_channel->from;

				if((diff_time) < tween_channel->duration){ // interpolate
					value=tween_channel->from+Ease::linear(t)*(tween_channel->to - tween_channel->from);
				}else{ // set last and delete active msk
					value=tween_channel->to;
					this->channels_info->msk_active_channels&=~(0x1<<i);
				}

				this->channels_info->channels[i]=value;

			}
		}
	}
}

Tween::~Tween(){
	delete channels_info;
	delete [] tween_channels;
}
