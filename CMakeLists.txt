cmake_minimum_required(VERSION 3.8)

project(libmediasoupclient-demo LANGUAGES CXX)

# C++ standard requirements.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64")  

# Define the path to LibWebRTC include directory
set(LIBWEBRTC_INCLUDE_PATH "/Users/deepso/dev/stuff/webrtc-build/webrtc/src")

# Define the path to LibWebRTC binary directory
set(LIBWEBRTC_BINARY_PATH "/Users/deepso/dev/stuff/webrtc-build/webrtc/src/out/m120/obj")

# Find OpenSSL package
find_package(OpenSSL REQUIRED)

# CMAKE_USE_OPENSSL is typically set by CMake itself when OpenSSL is found
# But you can explicitly set it if needed
set(CMAKE_USE_OPENSSL ON)


message("\n=========== libmediasoupclient-demo Build Configuration ===========\n")
message(STATUS "LIBWEBRTC_INCLUDE_PATH : " ${LIBWEBRTC_INCLUDE_PATH})
message(STATUS "LIBWEBRTC_BINARY_PATH  : " ${LIBWEBRTC_BINARY_PATH})
message(STATUS "OPENSSL_INCLUDE_DIR    : " ${OPENSSL_INCLUDE_DIR})
message(STATUS "CMAKE_USE_OPENSSL      : " ${CMAKE_USE_OPENSSL})
message("")

# Add some compile flags to our source files.
set_source_files_properties(${SOURCE_FILES}
	PROPERTIES COMPILE_FLAGS -Wall -Wextra -Wpedantic)

# Create target.
add_executable(${PROJECT_NAME} ${SOURCES})

# Extra libs required in order to use Apple media devices.
if(APPLE)
	find_library(APPLICATION_SERVICES ApplicationServices)
	find_library(AUDIO_TOOLBOX AudioToolbox)
	find_library(AV_FOUNDATION AVFoundation)
	find_library(CORE_AUDIO CoreAudio)
	find_library(CORE_FOUNDATION Foundation)
	find_library(CORE_MEDIA CoreMedia)
	find_library(CORE_VIDEO CoreVideo)
	find_library(CORE_SERVICES CoreServices)

	target_link_libraries(${PROJECT_NAME} PUBLIC
		${APPLICATION_SERVICES}
		${AUDIO_TOOLBOX}
		${AV_FOUNDATION}
		${CORE_AUDIO}
		${CORE_FOUNDATION}
		${CORE_MEDIA}
		${CORE_VIDEO}
		${CORE_SERVICES}
	)
endif(APPLE)

include(FetchContent)

message(STATUS "\nFetching mediasoupclient...\n")
FetchContent_Declare(
  mediasoupclient
  GIT_REPOSITORY https://github.com/versatica/libmediasoupclient.git
  GIT_TAG v3
)
FetchContent_MakeAvailable(mediasoupclient)

target_sources(${PROJECT_NAME} PRIVATE
	src/main.cpp
)

# Private (implementation) header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Source Dependencies.
# add_subdirectory(deps/libwebrtc "${CMAKE_CURRENT_BINARY_DIR}/libwebrtc")

# Public (interface) headers from dependencies.
target_include_directories(${PROJECT_NAME} PUBLIC
	${mediasoupclient_SOURCE_DIR}/include
	"${PROJECT_SOURCE_DIR}/deps/libwebrtc"
)

# Public (interface) dependencies.
target_link_libraries(${PROJECT_NAME} PUBLIC
	${LIBWEBRTC_BINARY_PATH}/libwebrtc${CMAKE_STATIC_LIBRARY_SUFFIX}
	mediasoupclient
)
