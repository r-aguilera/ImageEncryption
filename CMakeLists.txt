# CMakeLists file to build an OpenCV project
# ==========================================

cmake_minimum_required(VERSION 2.8)
project( ImageEncryption )
find_package( OpenCV QUIET)

# If OpenCV package is not found, add the path from the environment variables
if(NOT OpenCV_DIR)
	set(OpenCV_DIR $ENV{OpenCV_DIR} FORCE)
endif()

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ImageEncryption ImageEncryption.cpp )
target_link_libraries( ImageEncryption ${OpenCV_LIBS} )