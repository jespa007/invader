#ifndef __FILE_H__
#define __FILE_H__

Buffer	    *	File_Read(const char *filename);
bool			File_Write(const char *filename, Buffer * buf);
size_t			File_Length(const char *filename);
bool			File_Exists(const char *filename);


#endif
