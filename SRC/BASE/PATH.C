#include "BASE/@BASE.H"


String *  Path_GetFilename(const char * _absolute_filename) {

	//char *dst=0;
	char *src=(char *)_absolute_filename;
	//size_t len = strlen(_absolute_filename);
	//size_t len=strlen(_absolute_filename);
	char * found=strrchr(_absolute_filename,'\\'); // locate the last ocurrence of '\\'

	if(found==NULL){
		found=strrchr(_absolute_filename,'/'); // locate the last ocurrence of '/'
	}

	if(found != NULL){ // no folder
		src=found+1;
		//len = strlen(src);
	}

	return String_New(src);
}