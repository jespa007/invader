
#pragma once


#define 	STR_EXPAND(tok) 	#tok
#define 	STR(tok) 		ZS_STR_EXPAND(tok)
#define 	STRCMP(a, R, b) 	(strcmp(a,b) R 0)
#define		STR_MAX			4096

#define 	STR_CAPTURE_BASE(_str_out, _first_param, _str_in)\
{va_list  ap;\
int max_len=(int)((sizeof(_str_out)/sizeof(char))-1);\
va_start(ap, _first_param);\
int n=vsnprintf(_str_out,max_len,_str_in,  ap);\
if(n>=(int)max_len || n==-1){\
	_str_out[max_len-1]=0;\
	_str_out[max_len-2]='.';\
	_str_out[max_len-3]='.';\
	_str_out[max_len-4]='.';\
}\
va_end(ap);}

#define STR_CAPTURE_VARGS_STD_STRING(_str_out, _std_string_in)\
STR_CAPTURE_BASE(_str_out,_std_string_in,_std_string_in.c_str())\


#define 	STR_CAPTURE_VARGS(_str_out, _str_in)\
STR_CAPTURE_BASE(_str_out,_str_in,_str_in)\

#define 	STR_CAPTURE_WVARGS(text_out, text_in)\
{va_list  ap;\
size_t max_len=sizeof(text_out)/sizeof(wchar_t);\
va_start(ap,  text_in);\
int n=vswprintf(_str_out,max_len,text_in,  ap);\
if(n>=(int)max_len || n==-1 ){\
	_str_out[max_len-1]=0;\
	_str_out[max_len-2]='.';\
	_str_out[max_len-3]='.';\
	_str_out[max_len-4]='.';\
}\
va_end(ap);}


#define 	STR_IS_EMPTY(str) ((str)==NULL || (*(str))==0)


class String{
public:

	typedef enum{
		STRING_COMPARER_EXACTLY=0,
		STRING_COMPARER_ORDINAL_IGNORE_CASE
	}StringComparer;


	static std::string					wstringToString(const std::wstring & _val);

	static std::string 					toLowerCase(const std::string & str);
	static std::string 					toUpperCase(const std::string & str);
	static std::string  				format(const  std::string & _str_text, ...);
	static std::string					formatFileLine(const char * _file, int _line, const  std::string & _str_in, ...);

	static bool 						isEmpty(const std::string & _str_in);
	static bool 						endsWith(const std::string & _str_in, const std::string & ending);
	static bool 						startsWith(const std::string & _str_in, const std::string & starting);
	static std::string 					replace(const std::string & _str_in, const std::string & old_word, const std::string & new_word);
	static std::string 					replace(const std::string & _str_in, char _old_char, char _new_char);

	static std::vector<std::string> 	split(const std::string & _str_in, char delim);
	static std::vector<std::string> 	split(const std::string & _str_in, const std::string & delim);

	static std::string					join(const std::vector<std::string> & _str_in, char _join_char);

	static std::string 					remove(const std::string & _str_in, const char *_const_str_chars_to_remove);

	static int							count(const std::string & s,char c);

	static bool 						contains(const std::string & _str_input, const std::string & _str_containts,StringComparer sc=StringComparer::STRING_COMPARER_ORDINAL_IGNORE_CASE);
	static bool 						contains(const std::vector<std::string> & _strings, const std::string & _str_containts,StringComparer sc=StringComparer::STRING_COMPARER_ORDINAL_IGNORE_CASE);

	static size_t 						indexOf(const std::string& text, const std::string& pattern);

	static std::string 					unescape(const std::string & s);

private:

};

