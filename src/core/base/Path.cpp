#include "@base.h"




std::string Path::getTempPath(void){
	static char folder[MAX_PATH]={0};
#ifdef _WIN32
	GetTempPath(MAX_PATH,folder);
#else
	const char *env_folder = getenv("TMPDIR");
	if (env_folder == 0){
		env_folder = "/tmp";
	}
	strcpy(folder,env_folder);
#endif
	return folder;

}

std::string  Path::getFileName(const std::string & _path) {

	  size_t found;
	  std::string ss=_path;
	  found=_path.find_last_of("/\\");
	  if(found != std::string::npos){
		  ss= _path.substr(found+1);
	  }
	  return ss;
}

std::string  Path::getFilenameWithoutExtension(const std::string & _path) {

	std::string file = getFileName(_path);
	std::string fname(file);
	size_t pos = fname.find_last_of(".");
	if(pos == std::string::npos){  //No extension.
		return fname;
	}

	if(pos == 0){    //. is at the front. Not an extension.
		return fname;
	}

	return fname.substr(0, pos);
}

std::string  Path::getExtension(const std::string & _path) {

	std::string file = getFileName(_path);
	std::string fname(file);
	size_t pos = fname.find_last_of(".");
	if(pos == std::string::npos){  //No extension.
		return fname;
	}

	return fname.substr(pos);
}

