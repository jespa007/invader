#include "@animation.h"

bool KeyframeTrackGroup::decomposeXYZW(

		   const std::vector<float> & _points
		, KeyframeTrackGroup * _vx
		, KeyframeTrackGroup * _vy
		, KeyframeTrackGroup * _vz
		, KeyframeTrackGroup * _vw
		){

	const float *v_input=_points.data();
	size_t v_input_len=_points.size();
	// check keyframe_tracks. Possible combinations are:
	// 1. xy
	// 2. xy
	// 3. xyz
	// 4. xyzw
	KeyframeTrackGroup *vx=NULL,*vy=NULL,*vz=NULL,*vw=NULL;

	KeyframeTrackGroup * di_src[]={
			_vx,_vy,_vz,_vw
	};

	KeyframeTrackGroup ** di_dst[]={
			&vx,&vy,&vz,&vw
	};

	KeyframeTrackGroup ***di_dst_ptr = di_dst;

	for(unsigned i=0; i < ARRAY_SIZE(di_src);i++){
		if(di_src[i] != NULL){ // assign
			**di_dst_ptr++=di_src[i];
		}
	}


	if(    vx!=NULL
		&& vy==NULL
		&& vz==NULL
		&& vw==NULL
	) {
		int packed_channels=2;

		if((v_input_len % packed_channels)!=0){
			LOG_ERROR("Error invalid dimension 1!");
			return false;
		}

		size_t dim=(v_input_len/packed_channels)*2;

		vx->points.resize(dim);

		float *aux_ptr=vx->points.data();

		for(unsigned i = 0; i < v_input_len; i+=packed_channels){
			//---
			// t
			*aux_ptr++=*v_input++;

			//---
			// x
			*aux_ptr++=*v_input++;
		}
	}else if(vx!=NULL // dimension 2
			&& vy!=NULL
			&& vz==NULL
			&& vw==NULL){
		int packed_channels=3;

		if((v_input_len % packed_channels)!=0){
			LOG_ERROR("Error invalid dimension 2!");
			return false;
		}

		size_t dim=(v_input_len/packed_channels)*2; // *2 because is the t and v

		vx->points.resize(dim);
		vy->points.resize(dim);

		float * vx_aux=vx->points.data();
		float * vy_aux=vy->points.data();

		for(unsigned i = 0; i < v_input_len; i+=packed_channels){
			//---
			// t
			*vx_aux++=*vy_aux++=*v_input++;

			//---
			// x
			*vx_aux++=*v_input++;

			//---
			// y
			*vy_aux++=*v_input++;
		}
	}
	else if(vx!=NULL
			&& vy!=NULL
			&& vz!=NULL
			&& vw==NULL){

		int packed_channels=4;

		if((v_input_len % packed_channels)!=0){
			LOG_ERROR("Error invalid dimension 3!");
			return false;
		}

		size_t dim=(v_input_len/packed_channels)*2;

		vx->points.resize(dim);
		vy->points.resize(dim);
		vz->points.resize(dim);


		float * vx_aux=vx->points.data();
		float * vy_aux=vy->points.data();
		float * vz_aux=vz->points.data();

		for(unsigned i = 0; i < v_input_len; i+=packed_channels){
			//---
			// t
			*vx_aux++=*vy_aux++=*v_input++;
			//---
			// x
			*vx_aux++=*v_input++;
			//---
			// y
			*vy_aux++=*v_input++;
			//----
			// z
			*vz_aux++=*v_input++;
		}
	}
	else{

		int packed_channels=5;

		if((v_input_len % packed_channels)!=0){
			LOG_ERROR("Error invalid dimension 5!");
			return false;
		}

		size_t dim=(v_input_len/packed_channels)*2;

		vx->points.resize(dim);
		vy->points.resize(dim);
		vz->points.resize(dim);
		vw->points.resize(dim);


		float * vx_aux=vx->points.data();
		float * vy_aux=vy->points.data();
		float * vz_aux=vz->points.data();
		float * vw_aux=vw->points.data();

		for(unsigned i = 0; i < v_input_len; i+=packed_channels){
			//---
			// t
			*vx_aux++=*vy_aux++=*v_input++;
			//---
			// x
			*vx_aux++=*v_input++;
			//---
			// y
			*vy_aux++=*v_input++;
			//---
			// z
			*vz_aux++=*v_input++;
			//---
			// w
			*vw_aux++=*v_input++;
		}
	}

	return true;
}

//----
KeyframeTrackGroup::KeyframeTrackGroup(){

}

KeyframeTrackGroup::~KeyframeTrackGroup(){
}
