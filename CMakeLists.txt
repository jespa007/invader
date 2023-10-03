# CMakeLists.txt
#
# Copyright 2021 by
# Jordi Espada
#
# Say
#
#   cmake CMakeLists.txt
#
#
# instead.  Please refer to the cmake manual for further options, in
# particular, how to modify compilation and linking parameters.
#

cmake_minimum_required(VERSION 3.15)

cmake_policy(SET CMP0091 NEW)	# To enable MSVC_RUNTIME_LIBRARY. It has effect only when policy CMP0091 is set to NEW prior to the first project() 
project(invader)

# Recurse into the "src" subdirectories.
add_subdirectory (src)

