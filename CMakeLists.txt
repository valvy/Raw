cmake_minimum_required (VERSION 3.21)
project(Raw)
set (CMAKE_CXX_STANDARD 14)


set (remove_cache_error "(You may need remove the CmakeCache.txt and the cache)")
IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    # Check if you're in the root directory of the project, and give an error.
    MESSAGE(FATAL_ERROR "Please create a dedicated build directory for Raw. ${remove_cache_error}")
ENDIF()

# Check if the compiler is emscripten
IF (NOT "${CMAKE_CXX_COMPILER}" MATCHES "em\\+\\+")
    MESSAGE (FATAL_ERROR "This project is only usable from emscripten. Please run emcmake cmake .. ${remove_cache_error}")
ENDIF()

# Set version constants.
set(Raw_MAJOR_VERSION 0)
set(Raw_MINOR_VERSION 0)
set(Raw_PATCH_VERSION 1)
set(Raw_version ${Raw_MAJOR_VERSION}.${Raw_MINOR_VERSION}.${Raw_PATCH_VERSION})


# Configure Settings file. 
# This file contains global information
set(header_version_in ${Raw_SOURCE_DIR}/assets/Raw-info.json.in)
set(header_version_out ${CMAKE_CURRENT_BINARY_DIR}/assets/Raw-info.json)
configure_file(${header_version_in} ${header_version_out})


configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/assets/index.html ${CMAKE_CURRENT_BINARY_DIR}/index.html  COPYONLY)



SET(LIB_SOURCES 
    src/main.cpp
)

set(RAW_INCLUDE_DIRS 
    ${Raw_SOURCE_DIR}/include/ 
    ${CMAKE_CURRENT_BINARY_DIR}/include/
) 

include_directories(${RAW_INCLUDE_DIRS} )




ADD_DEFINITIONS( "-g -Wall -c --bind " )
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} --emrun")
add_executable("${PROJECT_NAME}" ${LIB_SOURCES} ${RAW_INCLUDE_DIRS})