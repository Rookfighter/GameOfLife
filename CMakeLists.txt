cmake_minimum_required(VERSION 2.8.3)
project(GameOfLife)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(GOL_LIB "gol")
set(GOL_EXEC "GameOfLife")
set(GOL_TEST_EXEC "TestGameOfLife")

get_filename_component(SFML_ROOT "./lib/SFML-2.2" ABSOLUTE)
get_filename_component(CATCH_ROOT "./lib/Catch" ABSOLUTE)
get_filename_component(GOL_MODULES_PATH "./cmake-modules" ABSOLUTE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${GOL_MODULES_PATH})

find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)
find_package(Catch)

include_directories("src" ${SFML_INCLUDE_DIR})

add_subdirectory(src)
#add_subdirectory(test)