@echo off
SET ROOT_DIR=%~dp0
SET THIRD_PARTY_SOURCES_DIR=%ROOT_DIR%src\3rdparty
SET THIRD_PARTY_BUILD_DIR=%ROOT_DIR%build\msvc\3rdparty
SET THIRD_PARTY_INSTALL_DIR=%ROOT_DIR%3rdparty\msvc
SET THIRD_PARTY_INCLUDE=%THIRD_PARTY_INSTALL_DIR%\include
SET THIRD_PARTY_LIB=%THIRD_PARTY_INSTALL_DIR%\lib
SET TARGET=release
 
:: The third parties
SET SDL2_VERSION=SDL2-2.24.1

:: Detect which Visual Studio has installed
IF NOT "%VS160COMNTOOLS%"=="" (
	SET CMAKE_GENERATOR="Visual Studio 16 2019"
)ELSE IF NOT "%VS150COMNTOOLS%"=="" (
	SET CMAKE_GENERATOR="Visual Studio 15 2017"
)ELSE IF NOT "%VS140COMNTOOLS%"=="" (
	SET CMAKE_GENERATOR="Visual Studio 14 2015"
) ELSE (
	echo.
	echo Cannot detect Visual Studio environment vars through "Visual Studio Developer Command Prompt". The environment should set one of the followings environment variables,
	echo.
	echo  VS140COMNTOOLS: Environment variable for Visual Studio 2015
	echo  VS150COMNTOOLS: Environment variable for Visual Studio 2017
	echo  VS160COMNTOOLS: Environment variable for Visual Studio 2019
	echo. 
	echo Other Visual Studio versions are not supported
	echo. 
	PAUSE
	EXIT
)


echo -- 3rdparty dest path: %THIRD_PARTY_INSTALL_DIR%
echo -- CMake generator: %CMAKE_GENERATOR%

IF NOT EXIST %THIRD_PARTY_INCLUDE% (
	MD %THIRD_PARTY_INCLUDE%
)

IF NOT EXIST %THIRD_PARTY_LIB% (
	MD %THIRD_PARTY_LIB%
)


cd %ROOT_DIR%

::------------------------------------------------------------------------------------------------------------------------
::
:: SDL2
::
echo building SDL2...

IF NOT EXIST %THIRD_PARTY_BUILD_DIR%\%SDL2_VERSION%\NUL (
	tools\7zip\7za.exe x src\3rdparty\%SDL2_VERSION%.tar.gz -so| tools\7zip\7za.exe x -aoa -si -ttar -o%THIRD_PARTY_BUILD_DIR%
)

IF NOT EXIST %THIRD_PARTY_LIB%\SDL2.lib (
	cd %THIRD_PARTY_BUILD_DIR%\%SDL2_VERSION%

	rd %THIRD_PARTY_INCLUDE%\SDL2 /S /Q
	
	cmake  -H. -Bbuild -G %CMAKE_GENERATOR% -DBUILD_SHARED_LIBS:BOOL=OFF -A Win32
	msbuild build\SDL2.sln /t:Rebuild /p:Configuration=Release /p:Platform=Win32

	
	MD %THIRD_PARTY_INCLUDE%\SDL2
	copy include\* %THIRD_PARTY_INCLUDE%\SDL2	
	copy build\Release\SDL2main.lib %THIRD_PARTY_LIB%\SDL2main.lib
	copy build\Release\SDL2-static.lib %THIRD_PARTY_LIB%\SDL2.lib
)

cd %ROOT_DIR%

::------------------------------------------------------------------------------------------------------------------------
::
:: invader
::

echo building invader

IF NOT EXIST build\msvc\invader\Release\invader.exe (

	rd build\msvc\invader /S /Q
	cmake  -H. -Bbuild\msvc\invader -G %CMAKE_GENERATOR%  -A Win32
	msbuild build\msvc\invader\invader.sln /t:Rebuild /p:Configuration=Release /p:Platform=Win32

)

echo All OK
