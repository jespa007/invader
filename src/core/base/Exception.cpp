#include "@base.h"


void Exception::throwExceptionFileLine(const char *_file,int _line, const char *_str_in,...){
	char aux[STR_MAX];
	snprintf(aux,sizeof(aux),"[%s:%i] ",_file,_line);

	char str_out[STR_MAX];
	STR_CAPTURE_VARGS(str_out,_str_in);

	strcat(aux,str_out);

	throw std::runtime_error(str_out);
}

void Exception::throwException( const char *_str_in,...){
	char str_out[STR_MAX];
	STR_CAPTURE_VARGS(str_out,_str_in);

	throw std::runtime_error(str_out);
}

