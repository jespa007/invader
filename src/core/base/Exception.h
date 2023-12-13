#pragma once

#define THROW_EXCEPTION Exception::throwException

class Exception{
public:
	static void throwExceptionFileLine(const char *_file,int line, const char *_str_in,...);
	static void throwException(const char *_str_in,...);
};
