#ifndef __STRING_H__
#define __STRING_H__

typedef struct String String;

struct String{
	char		*	str;
	size_t 			len;
	void 		*	data;
};

String	*	String_New(const char * _str);
void 		String_Delete(String * _this);
#endif