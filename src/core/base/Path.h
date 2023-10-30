#pragma once

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

class Path{
	public:

	/**
	 * It returns the temp path
	 */
	static std::string  getTempPath(void);

	/**
	 * Given absolute path give it return its filename. The resulting string should be deallocated when is not used anymore
	 */
	static std::string  getFileName(const std::string & _path);

	/**
	 * Given absolute path give it return its filename without extension. The resulting string should be deallocated when is not used anymore
	 */
	static std::string	getFilenameWithoutExtension(const std::string & _path);

	/**
	 * Given absolute path give it return its filename extension
	 */
	static std::string	getExtension(const std::string & _path);

};
