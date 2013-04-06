## $BI,MW$J(BCMake$B$N%P!<%8%g%s(B
cmake_minimum_required(VERSION 2.8.8)
# $BJQ?t(B PROJECT_NAME_STR $B$N@_Dj(B
set(PROJECT_NAME_STR template)
#$B%W%m%8%'%/%HL>(B
project(${PROJECT_NAME_STR} C CXX)
# $B%3%s%Q%$%i$,(B g++ $B$N0l<o$G$"$k>l9g(B true $B$K$J$j(B
if(CMAKE_COMPILER_IS_GNUCXX)
#$B%3%s%Q%$%i$KEO$9%*%W%7%g%s(B
	add_definitions(-Wall -ansi -Wno-deprecated -pthread)
endif()

#-------------------
# set common include folder for module
#-------------------
# $BJQ?t(B COMMON_INCLUDES $B$N@_Dj(B
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
# $BJQ?t(B EXT_PROJECTS_DIR $B$N@_Dj(B
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

#-------------------
# Module source
#-------------------
#$BDI2C(B -->$B$3$3$+$i(B
set(PROJECT_LIB_NAME ${PROJECT_NAME_STR}_impl)

include_directories(${COMMON_INCLUDES})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
#add_library($B%?!<%2%C%H(B IMPORTED)
#$B%i%$%V%i%j$N@8@.!#!V(BADD_LIBRARY(sample_lib SHARED sample.c)$B!W$@$H!V(Blibsample_lib.dylib$B!W$,@8@.$5$l$k(B
add_library(${PROJECT_LIB_NAME} ${SRC_FILES})
#add_library(${SRC_FILES})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME_STR} ${SRC_FILES})


#$B%5%V%G%#%l%/%H%j(B($B3F!$%5%V%G%#%l%/%H%j$K$b(BCMakeLists.txt$B$rCV$/(B)
add_subdirectory(${EXT_PROJECTS_DIR}/gtest)

#-------------------
# Test
#-------------------

# Enable testing for current directory and below.
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
#include$B%G%#%l%/%H%j$N%Q%9$r;XDj!J(B-I$B%*%W%7%g%s$K;H$o$l$k!K(B 
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
#include_directories(${COMMON_INCLUDES} ${GTEST_INCLUDE_DIRS} )


file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
#file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(test/${PROJECT_TEST_NAME} ${TEST_SRC_FILES} ${PROJECT_SOURCE_DIR}/src/add.cpp)
add_dependencies(test/${PROJECT_TEST_NAME} googletest)

if(CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries(test/${PROJECT_TEST_NAME} pthread)
	target_link_libraries(test/${PROJECT_TEST_NAME}
		${GTEST_LIBS_DIR}/libgtest.a
		${GTEST_LIBS_DIR}/libgtest_main.a
	)
else()

#target_link_libraries($B%?!<%2%C%H!!%i%$%V%i%jL>(B)
#$B%j%s%/$9$k%i%$%V%i%j$r;XDj(B
	target_link_libraries(test/${PROJECT_TEST_NAME}
	       debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
	target_link_libraries(test/${PROJECT_TEST_NAME}
	       debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
endif()

# add_test($B%F%9%HL>(B Exename $B0z?t(B1 $B0z?t(B2 ...)
add_test(test1 test/${PROJECT_TEST_NAME})