cmake_minimum_required(VERSION 3.17)
project(p1)

set(CMAKE_CXX_STANDARD 14)

add_executable(p1x p1x.cpp BookList.cpp BookList.h MemberList.cpp MemberList.h RatingList.cpp RatingList.h)