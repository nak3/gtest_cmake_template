## 必要なCMakeのバージョン
cmake_minimum_required(VERSION 2.8.8)
# 変数 PROJECT_NAME_STR の設定
set(PROJECT_NAME_STR template)
#プロジェクト名
project(${PROJECT_NAME_STR} C CXX)
# コンパイラが g++ の一種である場合 true になり
if(CMAKE_COMPILER_IS_GNUCXX)
#コンパイラに渡すオプション
	add_definitions(-Wall -ansi -Wno-deprecated -pthread)
endif()

#-------------------
# set common include folder for module
#-------------------
# 変数 COMMON_INCLUDES の設定
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
# 変数 EXT_PROJECTS_DIR の設定
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

#-------------------
# Module source
#-------------------
#追加 -->ここから
set(PROJECT_LIB_NAME ${PROJECT_NAME_STR}_impl)

include_directories(${COMMON_INCLUDES})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
#add_library(ターゲット IMPORTED)
#ライブラリの生成。「ADD_LIBRARY(sample_lib SHARED sample.c)」だと「libsample_lib.dylib」が生成される
add_library(${PROJECT_LIB_NAME} ${SRC_FILES})
#add_library(${SRC_FILES})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME_STR} ${SRC_FILES})


#サブディレクトリ(各，サブディレクトリにもCMakeLists.txtを置く)
add_subdirectory(${EXT_PROJECTS_DIR}/gtest)

#-------------------
# Test
#-------------------

# Enable testing for current directory and below.
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
#includeディレクトリのパスを指定（-Iオプションに使われる） 
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

#target_link_libraries(ターゲット　ライブラリ名)
#リンクするライブラリを指定
	target_link_libraries(test/${PROJECT_TEST_NAME}
	       debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
	target_link_libraries(test/${PROJECT_TEST_NAME}
	       debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
endif()

# add_test(テスト名 Exename 引数1 引数2 ...)
add_test(test1 test/${PROJECT_TEST_NAME})
