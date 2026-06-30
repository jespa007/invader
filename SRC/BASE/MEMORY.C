#include "BASE/@BASE.H"


void * my_malloc(size_t size){
	void * p=NULL;

	p=malloc(size);

	if(p==NULL){
		Log_Error("Cannot allocate %zu",size);
		return NULL;
	}

	memset(p,0,size);

	return p;
}

void   my_free(void * _ptr){
	free(_ptr);
}


