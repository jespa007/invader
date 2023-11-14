#pragma once

#include <stdio.h>
#include  <SDL2/SDL.h>
#include  <unordered_map>
#include  <vector>
#include  <map>
#include  <functional>
#include  <string>

#if defined(_WIN32 ) // win32
	#ifndef NTDDI_VERSION
		#define NTDDI_VERSION 0x06000000
	#endif
	#include	<windows.h>
	#include	<conio.h>
	#include	<tchar.h>
	#include 	<Rpc.h>
	#include    <stdexcept>
	#include    <initguid.h>
#endif

#if defined(__GNUC__) // linux or mingw
#define __STDC_FORMAT_MACROS

	#include	<sys/stat.h>
	#include	<sys/types.h>
	#include	<unistd.h>
	#include	<memory.h>
	#include	<fcntl.h>
	#include	<dirent.h>
	#include	<sys/time.h>

	#if defined(__linux__)

		#include	<dlfcn.h>
		#include	<sys/ioctl.h>
		#include	<termios.h>
		#include 	<pwd.h>
	#endif
#endif

#define snprintf _snprintf

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifdef __MEMMANAGER__
#include "memmgr.h"
#endif

#include 		<stdexcept>
#include 		<cstddef>

#include "Common.h"
#include "Bit.h"
#include "String.h"
#include "Log.h"
#include "System.h"
#include "Path.h"
#include "ColorTerm.h"
