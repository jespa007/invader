#!/bin/bash

# Param settings
BUILD=""
TARGET_OS=""
HOST=""
ARCH=""
EXTENSION_EXE=""
CMAKE_GENERATOR="Unix Makefiles"
ROOT_DIR=$PWD
THIRD_PARTY_SOURCES_DIR=$ROOT_DIR"/src/3rdparty"
TOOLCHAIN="gcc"
TARGET="release"
BUILD_DIR="-C build"
PLATFORM="linux"
EXTENSION_STATIC_LIB=".a"
INSTALLED_DIR_LIBRARY_FILE="lib"
COMMON_CONFIGURE_OPTIONS=" --disable-shared --enable-static"
CMAKE_CONFIG=()

# The third parties
SDL2_VERSION="SDL2-2.24.1"
ZETSCRIPT_VERSION="zetscript-2.0.0"

# Toolchain selection
if [[ $# > 0 ]] 
then
	# custom platform
	case $1 in
	  android)
	  	TOOLCHAIN=android
	  	echo NDK_ROOT=$NDK_ROOT
	  	if [ "$NDK_ROOT" = "" ]
	  	then
	  		echo "NDK_ROOT environment variable not set"
	  		exit
	  	fi
	  	
	  	if [ "$(expr substr $(uname -s) 1 7)" = "MSYS_NT" ]
	    then
	    	CMAKE_CONFIG=("${CMAKE_CONFIG[@]}" -G 'MinGW Makefiles')
	    fi
	   	CMAKE_CONFIG=( "${CMAKE_CONFIG[@]}" -DCMAKE_TOOLCHAIN_FILE=$NDK_ROOT/build/cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release )	   	
	  	
	  ;;
	  em)
	    TOOLCHAIN=em
	    
	    if [ "$EMSCRIPTEN_ROOT_PATH" = "" ]
	  	then
	  		echo "EMSCRIPTEN_ROOT_PATH environment variable not set"
	  		exit
	  	fi
	    
	   	if [ "$(expr substr $(uname -s) 1 7)" = "MSYS_NT" ]
	    then
	    	CMAKE_CONFIG=("${CMAKE_CONFIG[@]}" -G 'MinGW Makefiles')
	    fi
	   	CMAKE_CONFIG=( "${CMAKE_CONFIG[@]}" -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN_ROOT_PATH/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=Release )	   	
	  ;;
	  rpi)
	    TOOLCHAIN=rpi
	    CMAKE_CONFIG=( "${CMAKE_CONFIG[@]}" -DRASPBERRY:BOOL=true -DCMAKE_TOOLCHAIN_FILE=$ROOT_DIR/toolchain-rpi.cmake -DCMAKE_BUILD_TYPE=Release )
	  ;;
	  rs97)
	    TOOLCHAIN=rs97
	  ;;
	  *)
	  	echo
	    echo "\""$1"\"" platform not handled
	    echo
	    echo Available platforms are:
	    echo
	    echo - "'"gcc"'" : gnu toolchain
	    echo - "'"em"'"  : emscriptem toolchain
	    echo - "'"rs97"'": rs97 toolchain
	    echo - "'"rpi"'" : Raspberry PI toolchain
	    exit -1
	  ;;
	esac
else

	if [ "$(expr substr $(uname -s) 1 7)" = "MSYS_NT" ]
	then
		BUILD_DIR=""
		EXTENSION_EXE=".exe"
		INSTALLED_DIR_LIBRARY_FILE="bin"
		HOST=x86_64-w64-mingw32
		ARCH=x86_64
		BUILD=$HOST
		TARGET_OS=mingw32
		COMMON_CONFIGURE_OPTIONS=$COMMON_CONFIGURE_OPTIONS" --build=$BUILD  --host=$HOST"
		CMAKE_CONFIG=(-DCMAKE_COLOR_MAKEFILE=0xFF -G 'MinGW Makefiles')
	else
		export CFLAGS=$CFLAGS" -fPIC"
	fi

fi

echo TOOLCHAIN=$TOOLCHAIN
THIRD_PARTY_BUILD_DIR=$ROOT_DIR"/build/"$TOOLCHAIN"/3rdparty"
THIRD_PARTY_INSTALL_DIR=$ROOT_DIR"/3rdparty/"$TOOLCHAIN
BINARY_DIR=$ROOT_DIR"/bin/"$TOOLCHAIN"/release"
export CFLAGS="-O2 -I"$THIRD_PARTY_INSTALL_DIR"/include"
export LDFLAGS="-L"$THIRD_PARTY_INSTALL_DIR"/lib"
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$THIRD_PARTY_INSTALL_DIR"/lib/pkgconfig"


CMAKE_CONFIG=("${CMAKE_CONFIG[@]}" -DCMAKE_INSTALL_PREFIX:PATH=$THIRD_PARTY_INSTALL_DIR )
COMMON_CONFIGURE_OPTIONS=$COMMON_CONFIGURE_OPTIONS" --prefix="$THIRD_PARTY_INSTALL_DIR

echo THIRD_PARTY_INSTALL_DIR=$THIRD_PARTY_INSTALL_DIR
echo THIRD_PARTY_BUILD_DIR=$THIRD_PARTY_BUILD_DIR
echo PKG_CONFIG_PATH=$PKG_CONFIG_PATH
echo LDFLAGS=$LDFLAGS
echo CFLAGS=$CFLAGS
echo TARGET_OS=$TARGET_OS
echo CMAKE_CONFIG=$CMAKE_CONFIG
echo THIRD_PARTY_INCLUDE=$THIRD_PARTY_INSTALL_DIR/include
echo CMAKE_CONFIG=${CMAKE_CONFIG[@]}

if ! [ -d "$THIRD_PARTY_BUILD_DIR" ] 
then
	mkdir -p $THIRD_PARTY_BUILD_DIR
fi

	
if ! [ -d $THIRD_PARTY_INSTALL_DIR"/lib" ]
then
	mkdir -p $THIRD_PARTY_INSTALL_DIR"/lib"
fi 

cd $THIRD_PARTY_BUILD_DIR



#------------------------------------------------------------------------------------------------------------------------
#
# SDL2
#

echo building SDL2...

if ! [ -d $THIRD_PARTY_BUILD_DIR"/$SDL2_VERSION" ] 
then
	tar xf $THIRD_PARTY_SOURCES_DIR"/"$SDL2_VERSION".tar.gz"
fi

cd $SDL2_VERSION

if ! [ -f $THIRD_PARTY_INSTALL_DIR"/lib/libSDL2"$EXTENSION_STATIC_LIB ] 
then

	rm -rf build

	cmake -H. -Bbuild "${CMAKE_CONFIG[@]}" -DBUILD_SHARED_LIBS:BOOL=false

	if ! [ $? -eq 0 ] 
	then
		exit 1
	fi

	make clean -C build
	make -j2   -C build install

	if ! [ $? -eq 0 ] 
	then
		exit 1
	fi
fi

cd ..


#------------------------------------------------------------------------------------------------------------------------
#
# invader
#
echo building invader...
cd $ROOT_DIR

if ! [ -f $BINARY_DIR"/invader"$EXTENSION_EXE ] 
then

	rm -rf build/$TOOLCHAIN/invader
	cmake -H. -Bbuild/$TOOLCHAIN/invader "${CMAKE_CONFIG[@]}"
	
	if ! [ $? -eq 0 ] 
	then
		exit 1
	fi
	
	make clean -C build/$TOOLCHAIN/invader
	make -C build/$TOOLCHAIN/invader
		
	if ! [ $? -eq 0 ] 
	then
		exit 1
	fi
fi

#------------------------------------------------------------------------------------------------------------------------


echo "All OK"
