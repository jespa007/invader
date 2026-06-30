#include "BASE/@BASE.H"

Buffer * File_Read(const char *_filename){

	size_t  readed_elements=0;
	Buffer *buffer=NULL;
	size_t  file_length=0;


	 FILE  *fp;

	if((fp  =  fopen(_filename,"rb"))  !=  NULL)
	{
		if((file_length = File_Length(_filename)) != INVALID_LENGTH) {

			buffer=Buffer_New(file_length+1); // we reserve +1 for end string just in case is a text (it always works!)
			readed_elements = fread(buffer->ptr, 1, file_length, fp);

			if(readed_elements != file_length) {
				LOG_ERROR("File_Read : number elements doesn't match with length file (%s)",_filename);
				Buffer_Delete(buffer);
				buffer = NULL;
			}
		}
		else  {
			LOG_ERROR("File_Read : I can't read file \"%s\"",_filename);
		}

		fclose(fp);
	}
	else {
		LOG_ERROR("File_Read : I can't open file \"%s\" for reading",_filename);
	}

	return buffer;
}

bool	File_Write(const char *_filename, Buffer * buf){

	size_t wrote_elements=0;
	FILE  *fp;
	bool ok = false;

	if(buf->ptr==NULL || buf->len==0){
		return false;
	}

	if((fp  =  fopen(_filename,"wb"))  !=  NULL){

		wrote_elements = fwrite(buf->ptr, 1, buf->len, fp);

		if(wrote_elements == buf->len) {
			ok=true;
		}else{
			LOG_WARNING("number elements wrote doesn't match with length file (%s)",_filename);
		}

		fclose(fp);
	}
	else  {
		LOG_ERROR("I can't open file \"%s\" for writting",_filename);
	}

	return ok;
}

size_t  File_Length(const char * _filename)
{

	size_t length = INVALID_LENGTH;

	FILE  *fp=NULL;

	if((fp  =  fopen(_filename,"rb"))  !=  NULL){

		size_t  ini,  end;

		fseek(fp,  0,SEEK_SET);
		ini  =  ftell(fp);
		fseek(fp,  0,SEEK_END);
		end  =  ftell(fp);

		length= (end  -  ini);
		fclose(fp);
	}

	return    length;
}

bool File_Exists(const char *_filename) {


	FILE *fp = fopen(_filename,"r");

	if(fp == NULL) {
		return false;
	}

	fclose(fp);

	return true;


}




