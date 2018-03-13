cmake_minimum_required(VERSION 3.5)
project(naivebayes)

set(CMAKE_CXX_STANDARD 14)

add_executable(naivebayes naivebayes.cpp naivebayes.h train_and_test.h)
#add_executable(unit-tests)
