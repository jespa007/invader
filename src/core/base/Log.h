#pragma once


 //#include <assert.h>


class  Log{

  Log();
  
  static bool ansi_escape;
public:


  typedef enum {
    LOG_LEVEL_ERROR=0,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
	LOG_LEVEL_DEBUG
  }LOG_LEVEL;
  
  //static Log *singleton_log;
  //static std::string * filename_str;
  //FILE  *fp;
  

	void  ini();
	
	//static Log * getInstance();
	static void setUseAnsiEscape(bool _use);

	//void  print_with_file_line(const  char  *file,  int  line,  const  char  *string_text,...);
	//void  print(const  char  *string_text,...);
	static void  print(const  char  *file,  int  line, LOG_LEVEL level, const  char  *string_text,...);

	~Log();
	
	static void deInit();
};


#define LOG_ERROR(s, ...) 			Log::print(__FILE__,__LINE__,Log::LOG_LEVEL::LOG_LEVEL_ERROR, s, ##__VA_ARGS__)
#define LOG_ERRORF(s) 				LOG_ERROR(s,0)

#define LOG_WARNING(s, ...)   		Log::print(__FILE__,__LINE__,Log::LOG_LEVEL::LOG_LEVEL_WARNING, s, ##__VA_ARGS__)
#define LOG_WARNINGF(s)		    	LOG_WARNING(s,0)

#define LOG_INFO(s, ...)   			Log::print(__FILE__,__LINE__,Log::LOG_LEVEL::LOG_LEVEL_INFO	, s, ##__VA_ARGS__)
#define LOG_INFOF(s)		   		LOG_INFO(s,0)

#define LOG_DEBUG(s, ...)   		Log::print(__FILE__,__LINE__,Log::LOG_LEVEL::LOG_LEVEL_DEBUG	, s, ##__VA_ARGS__)
#define LOG_DEBUGF(s)		   		LOG_DEBUG(s,0)





