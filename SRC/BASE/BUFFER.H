#ifndef __BUFFER_H__
#define __BUFFER_H__

typedef struct Buffer Buffer;

struct Buffer{
	uint8_t *   ptr;
	size_t      len;
};


Buffer * Buffer_New(size_t len);
void     Buffer_Delete(Buffer *buffer);

#endif
