#include "@animation.h"

#define MAX_CHANNELS 16
//---------------------------------------------------------------------------------------------------------------------
// STATIC
/*
void ChannelsInfo::copy(ChannelsInfo * _dst, ChannelsInfo * _src){
	uint32_t msk = _src->msk_active_channels;

	for(unsigned i=0; i < _dst->n_channels; i++){
		if(msk & (0x1 << i)){
			_dst->channels[i]=(_src)->channels[i];
		}
	}

	_dst->msk_active_channels |= msk;
}*/

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC

ChannelsInfo::ChannelsInfo(uint8_t _n_channels){

	channels=NULL;
	msk_active_channels=0;
	n_channels=_n_channels;

	if(n_channels==0){
		LOG_ERROR("Invalid num components");
		return;
	}

	channels=new float[n_channels];
	msk_active_channels=0;
}

void ChannelsInfo::copy(ChannelsInfo  * _dst, ChannelsInfo *  _src){

	if(_dst->n_channels != _src->n_channels){
		LOG_ERROR("ChannelsInfo::copy : _dst and _src has not the same number of channels");
		return;
	}

	uint32_t msk = _src->msk_active_channels;

	for(unsigned i=0; i < _dst->n_channels; i++){
		if(msk & (0x1 << i)){
			_dst->channels[i]=(_src)->channels[i];
		}
	}

	_dst->msk_active_channels |= msk;
}

void ChannelsInfo::print(){
	for(unsigned i=0; i < this->n_channels; i++){
		if(i > 0){
			printf(",");
		}
		printf("%02f",this->channels[i]);
	}

	printf("\n");
}

void ChannelsInfo::copyTo(float *_dst){
	uint32_t msk = this->msk_active_channels;

	for(unsigned i=0; i < this->n_channels; i++){
		if(msk & (0x1 << i)){
			_dst[i]=this->channels[i];
		}
	}
}
/*
void ChannelsInfo::copy(ChannelsInfo * _dst, ChannelsInfo * _src){
	uint32_t msk = _src->msk_active_channels;

	for(unsigned i=0; i < _dst->n_channels; i++){
		if(msk & (0x1 << i)){
			_dst->channels[i]=(_src)->channels[i];
		}
	}

	_dst->msk_active_channels |= msk;
}*/


ChannelsInfo::~ChannelsInfo(){
	n_channels=0;
	msk_active_channels=0;
	delete [] channels;

}

