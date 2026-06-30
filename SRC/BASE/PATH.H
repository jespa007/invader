#ifndef __ZG_PATH_H__
#define __ZG_PATH_H__


/**
 * Given absolute path give it return its filename. The resulting string should be deallocated when is not used anymore
 */
String *  Path_GetFilename(const char * _absolute_filename);


#endif