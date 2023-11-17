cmake_minimum_required(VERSION 3.20)
project(SpaceCombat VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER "/usr/bin/clang-16")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-16")

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include(CTest)
enable_testing()

link_directories(lib)
include_directories(include)

file(GLOB sources CONFIGURE_DEPENDS ./source/*.c*  ./source/game/*.c*)

add_executable(SpaceCombat main.cpp)
target_sources(SpaceCombat PUBLIC ${sources})

target_link_libraries(SpaceCombat libglfw3.a)
target_link_libraries(SpaceCombat libyaml-cpp.a)
target_link_libraries(SpaceCombat libGL.so libX11.so libpthread.so libXrandr.so libXi.so libdl.so)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
