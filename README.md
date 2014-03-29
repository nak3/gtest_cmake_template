gtest_cmake_template
====================

How to make use this template?
----------------------------------------
See example project in under `demo/sample01`, which is example of Test Driven Development chap01 By Kent Beck.


How to build?
----------------------------------------

Following next steps, which is demonstration of `demo/sample01` project.

1. Change directory to build direcotry.

`$cd gtest_cmake_template.test/demo/sample01/build`

2. Run

`$ cmake ..`

You can see

    $ ls
    CMakeCache.txt  CMakeFiles  cmake_install.cmake  CTestTestfile.cmake  ext  Makefile  test

in your build directory.

3. Run make

`$ make`

4. Run test

Test result will be like this.

    $ ./test/tdd_chap01_test
    Running main() from gtest_main.cc
    [==========] Running 1 test from 1 test case.
    [----------] Global test environment set-up.
    [----------] 1 test from Dollar
    [ RUN      ] Dollar.test1
    [       OK ] Dollar.test1 (0 ms)
    [----------] 1 test from Dollar (0 ms total)

    [----------] Global test environment tear-down
    [==========] 1 test from 1 test case ran. (0 ms total)
    [  PASSED  ] 1 test.

