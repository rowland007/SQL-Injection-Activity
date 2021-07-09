cmake_minimum_required(VERSION 3.19)
project(SQL_Injection_Activity)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES source/SQLInjection.cpp source/sqlite3.c source/sqlite3.h)

add_executable(SQL_Injection_Activity source/SQLInjection.cpp)