PROJECT(cmake_productionSearch)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "-g -Ofast")

INCLUDE_DIRECTORIES(src/interface)

FILE(GLOB cpp_files "src/implement/*.cpp")

MESSAGE("${cpp_files}")

ADD_EXECUTABLE(Solver ${cpp_files})