#include "BASE/@BASE.H"

Buffer *Buffer_New(size_t len){
	Buffer *buffer=NEW(Buffer);
	buffer->ptr=(uint8_t *)MALLOC(sizeof(uint8_t)*len);
	buffer->len=len;
	memset(buffer->ptr,0,len);
	return buffer;
}

void Buffer_Delete(Buffer *buffer){
	if(buffer!=NULL){
		if(buffer->ptr!=NULL){
			FREE(buffer->ptr);
		}
		FREE(buffer);
	}
}
