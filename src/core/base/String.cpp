/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
#include "@base.h"


std::string  String::format(const  std::string & _str_in, ...){

	char  _sformat_buffer[STR_MAX] = { 0 };
	STR_CAPTURE_VARGS_STD_STRING(_sformat_buffer,_str_in);
	return std::string(_sformat_buffer);
}

std::string	String::formatFileLine(const char* _file, int _line, const  std::string & _str_in, ...) {
	std::string str_out;
	char  _sformat_buffer[STR_MAX] = { 0 };
	STR_CAPTURE_VARGS_STD_STRING(_sformat_buffer,_str_in);

	if((_file == NULL || *_file == 0)){
		str_out=format("[line %i] ", _line);
	}else{
		str_out=format("[%s:%i] ", Path::getFileName(_file).c_str(), _line);
	}

	return str_out+_sformat_buffer;

}



std::string					String::wstringToString(const std::wstring & _str_in){
	std::string res="";
	for(auto wc:_str_in){
		// just chop off the high byte from a wchar_t to get your char.
		// More information at http://www.unicode.org/
		char c=wc & 0xff;
		res+=c;
	}

	return res;
}

std::string String::toLowerCase(const std::string & str){

	std::string ret = str;
	for(size_t l = 0; l < ret.length();l++){
		ret[l] = tolower(ret[l]);
	}
	return ret;
}

std::string String::toUpperCase(const std::string & str){

	std::string ret = str;
	for(size_t l = 0; l < ret.length();l++)
		ret[l] = toupper(ret[l]);
	return ret;
}

//------------------------------------------------------------------------------------------------------------------------
std::vector<std::string> String::split(const std::string &_s_in, char _delim) {
	std::vector<std::string> elems;
	//std::string s = s_in;
	char *last_pos=(char *)_s_in.c_str();
	char *pos=(char *)_s_in.c_str();
	std::string token;
	while((pos=strchr(pos,_delim))!=NULL) {
		token = _s_in.substr(last_pos-_s_in.c_str(), pos-last_pos);
		elems.push_back(std::string(token));
		pos++;
		last_pos=pos;
	}

	// push last token
	token = _s_in.substr((last_pos-_s_in.c_str()), _s_in.length()-(last_pos-_s_in.c_str()));
	elems.push_back(std::string(token));

	return elems;
}

std::vector<std::string> String::split(const std::string &_s_in, const std::string & _delim) {
	std::vector<std::string> elems;
	std::string s = _s_in;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(_delim)) != std::string::npos) {
		token = s.substr(0, pos);
		elems.push_back(std::string(token));
		s.erase(0, pos + _delim.length());
	}

	elems.push_back(std::string(s));
	return elems;
}

std::string String::join(
	const std::vector<std::string> &_strs
	, char _join_char
) {
	std::string out="";

	for(size_t i=0; i < _strs.size(); i++){
		if(i>0){
			out+=_join_char;
		}
		out.append(_strs[i]);
	}

	return out;
}

bool String::isEmpty(const std::string & str){
	return str.empty();
}

bool String::endsWith(const std::string & str, const std::string & ending){
	size_t len_str=str.length();
	size_t len_end_str=ending.length();
	if(len_end_str<=len_str){
		const char *p1=str.c_str()+len_str-len_end_str;
		const char *p2=ending.c_str();
		return strcmp(p1,p2)==0;
	}

	return false;
}

bool String::startsWith(const std::string & str, const std::string & starting){
	if (str.length() >= starting.length()) {
		return strncmp(str.c_str(),starting.c_str(),starting.length())==0;
	}
	return false;
}

std::string String::replace(const std::string & input_str, const std::string & str_old, const std::string & str_new){
	std::string str = input_str;
	int	idx_current_pos=0;
	char *current_pos=NULL;

	while((current_pos = strstr((char*)str.c_str()+idx_current_pos,str_old.c_str())) != NULL) {
		idx_current_pos=current_pos-str.c_str();
		str.replace(idx_current_pos, str_old.length(), str_new);
		idx_current_pos += str_new.length(); // Handles case where 'str_new' is a substring of 'str_old'
	}

	return str;
}

std::string String::replace(const std::string & _str_in, char _old_char, char _new_char){
	std::string str = "";

	for(size_t i=0; i < _str_in.size(); i++){
		char c=_str_in[i];
		if(c==_old_char){
			c=_new_char;
		}
		str+=c;
	}

	return str;
}


std::string  String::remove(const std::string & _str_in, const char *_const_str_chars_to_remove){

	std::string str_new="";
	size_t num_ch_to_remove=strlen(_const_str_chars_to_remove);

	for(size_t  i = 0; i < _str_in.length(); ++i) {
		char current_char=_str_in[i];
		bool ch_to_remove=false;
		// check if the set of ch_to_remove is
		for(size_t c=0; c < num_ch_to_remove && (ch_to_remove==false); c++){
			if (current_char == _const_str_chars_to_remove[c]){
				ch_to_remove=true;
			}
		}

		// if not ch to remove addit
		if(ch_to_remove==false){
			str_new+=current_char;
		}

	}
	return str_new;
}

int String::count(const std::string & s,char c){
	int n_items=0;

	for(size_t i=0; i < s.length(); i++)
		if(s[i] == c)
			n_items++;

	return n_items;
}

bool String::contains(const std::string & _str_input, const std::string & _str_containts,StringComparer sc){

	std::string s1=_str_input;
	std::string s2=_str_containts;

	if(sc==StringComparer::STRING_COMPARER_ORDINAL_IGNORE_CASE){
		s1=toLowerCase(s1);
		s2=toLowerCase(s2);
	}

	if (s1.find(s2) != std::string::npos) {
		return true;
	}
	return false;
}

bool String::contains(const std::vector<std::string> & _strings, const std::string & _str_containts,StringComparer sc){

	for(size_t i = 0; i < _strings.size(); i++){
		if(contains(_strings[i],_str_containts,sc)){
			return true;
		}
	}
	return false;
}

size_t String::indexOf(const std::string & text, const std::string & pattern)
{
	// where appears the pattern in the text?
	size_t loc = text.find(pattern, 0);
	if (loc != std::string::npos)
	{
		return loc;
	}
	return std::string::npos;
}

std::string String::unescape(const std::string & s)	{
	std::string res;
	char *it = (char *)s.c_str();
	char *end= (char *)s.c_str()+s.length();
	while (it != end) {
		char c = *it++;
		if (c == '\\' && it != end)	{
			switch (*it++) {
				case '\\': c = '\\'; break;
				case 'n': c = '\n'; break;
				case 't': c = '\t'; break;
				case '"': c = '\"'; break;
				case 0x27: c = '\''; break;
				// all other escapes
				default:
				// invalid escape sequence - skip it. alternatively you can copy it as is, throw an exception...
			continue;
		  }
		}
		res += c;
	}

  return res;
}


