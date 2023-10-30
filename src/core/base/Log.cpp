#include "@base.h"

#define VAR_LOG(l) ((l) == LOG_LEVEL::LOG_LEVEL_ERROR?"ERR": (l)==LOG_LEVEL::LOG_LEVEL_WARNING?"WRN": (l) == LOG_LEVEL::LOG_LEVEL_INFO ? "INF" : "NAN" )
//      #include                  "cbingq.h"
//#include <string>


//std::string *Log::filename_str=NULL;
//using std::string;
//FILE  *fp;
//Log *Log::singleton_log = NULL;
bool Log::ansi_escape =false;
//static char s_Filename[MAX_PATH];

void Log::setUseAnsiEscape(bool _use){
	ansi_escape=_use;
}
/*
Log * Log::getInstance()
{
    if(singleton_log == NULL){
     // singleton_log = new Log();
     // filename_str = new string;
    }


    //return singleton_log;
}
 */

void Log::deInit(){
	/*if(filename_str !=NULL){
		delete filename_str;
		filename_str=NULL;
	}*/
}

//--------------------------------------------------------------------------------
Log::Log()
{
}
//--------------------------------------------------------------------------------


void  Log::ini()
{

}
//---------------------------------------------------------------------------------------------------------
#ifndef  __GNUC__
#pragma  managed(push,  off)
#endif


void  Log::print(const  char  *file,  int  line, LOG_LEVEL level, const  char  *string_text,...) {
	//FILE *log_std=stdout;
	FILE *std_type=stdout;
	/*if(filename_str ==NULL){
		filename_str = new string;
	}*/
	//std::string filename_str = "";

	switch(level)
	{
	case LOG_LEVEL::LOG_LEVEL_WARNING:
	case LOG_LEVEL::LOG_LEVEL_ERROR:
		std_type=stdout; // everything stdout to have all conscutives prints (stderr/stdout)
		break;
	default:
		break;
	}



	char  text[STR_MAX]={0};
	STR_CAPTURE_VARGS(text, string_text);
	//  Results  Are  Stored  In  Text


	if(!ansi_escape){
#ifdef _WIN32
		int colors[7];
		colors[0] = FOREGROUND_RED   | FOREGROUND_INTENSITY;//FOREGROUND_BLUE  | FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		colors[1] = FOREGROUND_GREEN | FOREGROUND_RED   | FOREGROUND_INTENSITY;
		colors[2] = FOREGROUND_BLUE  | FOREGROUND_GREEN | FOREGROUND_RED   | FOREGROUND_INTENSITY;
		colors[3] = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		colors[4] = FOREGROUND_BLUE  | FOREGROUND_INTENSITY;
		colors[5] = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		colors[6] = FOREGROUND_RED   | FOREGROUND_INTENSITY;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[level]);
#endif
	}else{

		switch(level)
		{
		case LOG_LEVEL::LOG_LEVEL_ERROR:
			ColorTerm::setColor(std_type,ColorTerm::BRIGHT, ColorTerm::CYAN, ColorTerm::RED);
			break;
		case LOG_LEVEL::LOG_LEVEL_WARNING:
			ColorTerm::setColor(std_type,ColorTerm::BRIGHT,ColorTerm::CYAN, ColorTerm::YELLOW);
			break;
		default:

			break;
		}
	}





	if(file == NULL)
		fprintf(std_type,"%s",text);
	else{
		fprintf(std_type,"[ %30s:%04i - %3s]=%s",file!=NULL?Path::getFileName(file).c_str():"unknow",line,VAR_LOG(level),text);
		//fprintf(stderr,"[ %30s:%04i - %3s]=%s",filename.c_str(),line,VAR_LOG(level),text);
	}

	if(!ansi_escape){
#ifdef _WIN32
		// restore ...
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE  | FOREGROUND_GREEN | FOREGROUND_RED );
#endif
	}else{
		ColorTerm::setColor(std_type,ColorTerm::BRIGHT, ColorTerm::GREEN, ColorTerm::BLACK);
	}


	fprintf(std_type,"\n");


	// to ensure all data has been write...
	fflush(std_type);
	// ColorTerm::resetColor();

}

#ifndef  __GNUC__
#pragma  managed(pop)
#endif  

Log::~Log()
{

}


