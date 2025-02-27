cmake_minimum_required(VERSION 3.10)
project(TowerOfTheSorcerer)

set(CMAKE_CXX_STANDARD 14)

find_package(FLTK REQUIRED)

include_directories(${FLTK_INCLUDE_DIRS})
link_directories(${FLTK_LIBRARY_DIRS})

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

add_executable(TowerOfTheSorcerer ${SOURCES} ${HEADERS})

target_link_libraries(TowerOfTheSorcerer ${FLTK_LIBRARIES} SDL2 SDL2_mixer)