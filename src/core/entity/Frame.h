/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
class Image;
class Frame{
public:
	static const size_t npos=-1;

	Image *image;
	int time;
	SDL_Rect crop;
	Collider collider;
	int color;

	Frame(){
		image=NULL;
		time=-1; // by default first frame
		color=-1; // white by default
		crop={0,0,0,0};
	}

	Frame(
		Image *_image
		,int _time
		,SDL_Rect _crop
		,Collider _collider
		,int _color
	){
		image=_image;
		time=_time;
		color=_color;
		crop=_crop;
		collider=_collider;
	}



	Frame(const Frame & _frame_info){
		copy(_frame_info);
	}


	Frame & operator =(const Frame & _frame_info){
		copy(_frame_info);
		return *this;
	}
private:

	void copy(const Frame & _frame_info){


		this->image=_frame_info.image;
		this->color=_frame_info.color;
		this->time=_frame_info.time;
		this->crop=_frame_info.crop;
		this->collider=_frame_info.collider;

	}
};
