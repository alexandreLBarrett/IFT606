cmake_minimum_required(VERSION 3.2.0)

project(TP1)

set (CMAKE_CXX_STANDARD 20)

aux_source_directory(. ROOT_SOURCE)

add_executable(TP1 ${ROOT_SOURCE})