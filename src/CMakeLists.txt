cmake_minimum_required(VERSION 3.15)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  MESSAGE(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the 'invader' source code and call cmake from there. For instance,\nmkdir build\ncd build\ncmake ..")
endif()


cmake_policy(SET CMP0091 NEW)	# To enable MSVC_RUNTIME_LIBRARY. It has effect only when policy CMP0091 is set to NEW prior to the first project()
project(invader)



IF( NOT CMAKE_BUILD_TYPE )
   SET( CMAKE_BUILD_TYPE Release )
ENDIF()

set(POST_NAME "")
set(IS_DEBUG FALSE)
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	set(IS_DEBUG TRUE)
	SET( CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -D__DEBUG__ ")
	set( POST_NAME "_d")
endif()

MESSAGE ("-- Target: " ${CMAKE_BUILD_TYPE})


#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#
# COMPILER PARAMS
#


message("-- Install drectory: " ${CMAKE_INSTALL_PREFIX})

if(MSVC)
	set(PLATFORM "msvc")
	MESSAGE("-- Plataform: MSVC" )
	
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)

	#disable C4103 warning because is perfectly valid. Only MSVC complains about it
	add_definitions(/wd4103)
	add_definitions(/wd4800)
	add_definitions(/wd4244)
	
	# warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc
	add_definitions(/EHsc)
	
	
	if(BUILD_SHARED_LIBS)
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
		IF (IS_DEBUG)
			set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:libcmtd.lib")
		ELSE()
			set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:libcmt.lib")
		ENDIF()
		
	else()
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
		IF (IS_DEBUG)
			set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:msvcrtd.lib")
		ELSE()
			set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:msvcrt.lib")
		ENDIF()

	endif()

else()
	SET( CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -D__STDC_CONSTANT_MACROS -static-libstdc++ -static-libgcc -std=gnu++0x -pthread -Wall -Wextra -pedantic")
    set(PLATFORM "gcc")
	if (MINGW)
		MESSAGE("-- Plataform: MINGW" )
	elseif(RASPBERRY)
    	MESSAGE ("-- Plataform: RASPBERRY" )
    	set(PLATFORM "rpi")
	elseif(UNIX)
    	MESSAGE ("-- Plataform: UNIX" )
    	file(READ "/etc/issue" ETC_ISSUE )
		string(REGEX MATCH "Debian|Ubuntu|Alpine" DIST ${ETC_ISSUE})
		MESSAGE ("-- Dist: " ${DIST} )    	
    elseif(EMSCRIPTEN)
    	MESSAGE ("-- Plataform: EMSCRIPTEN" )
		message("emscripten path: $ENV{EMSCRIPTENDIR} ")
		set(CMAKE_C_COMPILER "$ENV{EMSCRIPTENDIR}/emcc")
		set(CMAKE_CXX_COMPILER "$ENV{EMSCRIPTENDIR}/em++")
		SET( CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -I$ENV{EMSCRIPTENDIR}/system/lib/libcxxabi/include/ -s USE_SDL=2 -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2 -s VERBOSE=1 ")
		set( POST_NAME ${POST_NAME}.html)    	
    else()
    	MESSAGE ("-- Plataform: Unknown" )
	endif()	
	
	
	IF ( IS_DEBUG)
		set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -O0 -g ")
		
		IF (EXISTS ${PROJECT_SOURCE_DIR}/../../memmgr)
		
			message("-- Memmanager: Yes")
			SET( CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -D__MEMMANAGER__")
			include_directories (
				${PROJECT_SOURCE_DIR}/../../memmgr
			)
			
	   		set(INVADER_LIB_SRCS ${INVADER_LIB_SRCS} ${PROJECT_SOURCE_DIR}/../../memmgr/memmgr.cpp)
		
		ELSE()
	
			if(UNIX)
				if( NOT "${DIST}" STREQUAL "Alpine")
					set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fsanitize=address ")
					message("-- Memmanager: -fsanitize=address")
				else()
					message("-- Memmanager: -fsanitize NOT supported")
				endif()
			 else()
			 	message("-- Memmanager: OFF (../../memmgr not exist)")
			 endif()
		ENDIF()
	ELSE()
		set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -O2 ")
	ENDIF()
	
	#Redefine output dir ...
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin/${PLATFORM}/${CMAKE_BUILD_TYPE})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin/${PLATFORM}/${CMAKE_BUILD_TYPE})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin/${PLATFORM}/${CMAKE_BUILD_TYPE})
	LINK_DIRECTORIES(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})	
		
endif()

MESSAGE ("-- Platform: " ${PLATFORM})
include_directories (
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/../3rdparty/${PLATFORM}/include
)


#
# COMPILER PARAMS
#
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#
# LINK PARAMS
#

LINK_DIRECTORIES (
	${PROJECT_SOURCE_DIR}/../3rdparty/${PLATFORM}/lib
)	


if(MSVC)
	  # Add dependency platform libraries
  	set( LIB_DEPS  ${LIB_DEPS} 
		  	opengl32 # OpenGL for windows
		  	Rpcrt4   # Win32 uuid create 
		  	ws2_32	 # Win32 winsock2
			imm32    # Win32 Keyboard
			winmm    # Win32 Audio
			version  # Win32 GetVersion Info
			setupapi # Win32 DiGet class
			SDL2	 # SDL2
			SDL2main # SDL2_main
	)
else()
	list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/../3rdparty/${PLATFORM}/lib/cmake/SDL2/)
	find_package(PkgConfig REQUIRED)
	find_package(SDL2 REQUIRED)
	set(LIB_DEPS ${LIB_DEPS}
	   ${SDL2_LIBRARIES}
	   ${SDL2_EXTRA_LINK_FLAGS_STATIC}
	)	

endif()

#
# RELEASE PARAMS
#
#----------------------------------------------------------------------------------------------------------------------------------------------------
#
# SOURCE CODE PARAMS
#


# INVADER SRC
set(  INVADER_LIB_SRCS ${INVADER_LIB_SRCS} 
	core/base/@base.cpp
	core/animation/@animation.cpp	
	core/graphics/@graphics.cpp
	core/sound/@sound.cpp
	core/input/@input.cpp
	core/entity/@entity.cpp
	core/physics/@physics.cpp
	core/tilemap/@tilemap.cpp
	Invader.cpp
	main.cpp
	
)


if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    enable_language("RC")
    set (WIN32_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/invader.rc)
endif()

# invader
add_executable(
	invader${POST_NAME}	
	${INVADER_LIB_SRCS} 
	${WIN32_RESOURCES}
)


# Library
if (EMSCRIPTEN)
	set_target_properties(invader${POST_NAME} PROPERTIES LINK_FLAGS " -s USE_SDL=2 ")
	target_link_libraries(invader${POST_NAME} SDL2main SDL2)
else()
	target_link_libraries(invader${POST_NAME} ${LIB_DEPS})
endif()




