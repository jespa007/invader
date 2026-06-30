#include "BASE/@BASE.H"


typedef struct{
	size_t capacity;
}StringData;

String	*	String_NewEmpty(void){
	String *str = NEW(String);
	StringData *data = NEW(StringData);
	str->data = data;

	str->str = NULL;
	str->len = 0;
	data->capacity = 0;

	return str;
}


String	*	String_New(const char *_str_in){

	String *str_out = String_NewEmpty();

	if(_str_in != NULL){

		StringData *str_out_data = str_out->data;
		str_out->len = str_out_data->capacity = strlen(_str_in);
		str_out->str = NEW_LENGTH(char , str_out->len+1);
		strcpy(str_out->str,_str_in);
	}

	return str_out;
}

void 			String_Delete(String * _this){
    StringData *data = NULL;

	if(_this->str != NULL){
		FREE(_this->str);
	}

	data = _this->data;
	FREE(data);
	FREE(_this);
}