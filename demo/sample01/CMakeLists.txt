## Required CMake version.
cmake_minimum_required(VERSION 2.8.8)
# Set PROJECT_NAME_STR
set(PROJECT_NAME_STR tdd_chap01)
# Set Project Name
project(${PROJECT_NAME_STR} C CXX)
# If your compiler is G++,
if(CMAKE_COMPILER_IS_GNUCXX)
  # These options are added to compiler.
  add_definitions(-Wall -ansi -Wno-deprecated -pthread)
endif()

#-------------------
# set common include folder for module
#-------------------
# Set COMMON_INCLUDES
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
# Set EXT_PROJECTS_DIR
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

#-------------------
# Module source
#-------------------
set(PROJECT_LIB_NAME ${PROJECT_NAME_STR}_impl)

include_directories(${COMMON_INCLUDES})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
# add_library(target: IMPORTED)
# Make library. ex) ADD_LIBRARY(sample_lib SHARED sample.c) -> libsample_lib.dylib will be created.
add_library(${PROJECT_LIB_NAME} ${SRC_FILES})
# add_library(${SRC_FILES})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME_STR} ${SRC_FILES})

# Sub directory (put CMakeLists.txt on each subdirectories)
add_subdirectory(${EXT_PROJECTS_DIR}/gtest)

#-------------------#
# Test              #
#-------------------#

# Enable testing for current directory and below.
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
# Path to include directory (it is used by "-I" option)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
#include_directories(${COMMON_INCLUDES} ${GTEST_INCLUDE_DIRS} )


file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
#file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(test/${PROJECT_TEST_NAME} ${TEST_SRC_FILES} ${PROJECT_SOURCE_DIR}/src/dollar.cpp)
add_dependencies(test/${PROJECT_TEST_NAME} googletest)

if(CMAKE_COMPILER_IS_GNUCXX)
  target_link_libraries(test/${PROJECT_TEST_NAME} pthread)
  target_link_libraries(test/${PROJECT_TEST_NAME}
    ${GTEST_LIBS_DIR}/libgtest.a
    ${GTEST_LIBS_DIR}/libgtest_main.a
    )
else()

  #target_link_libraries(target library name)
  # Set library to link
  target_link_libraries(test/${PROJECT_TEST_NAME}
    debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
    optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
    )
  target_link_libraries(test/${PROJECT_TEST_NAME}
    debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
    optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
    )
endif()

# add_test(TEST_NAME arg1 arg2 ...)
add_test(test1 test/${PROJECT_TEST_NAME})
