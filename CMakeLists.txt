cmake_minimum_required(VERSION 3.20)
project(SpaceCombat VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

# Export compile commands (for IDEs)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include(CTest)
enable_testing()

# include
include_directories(include)

# libs
set(libs libglfw3.a)
link_directories(lib/)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	link_directories(lib/windows)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	link_directories(lib/linux)
	set(libs ${libs} libGL.so libX11.so libpthread.so libXrandr.so libXi.so libdl.so)
endif()

# git submodule
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
	# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# yaml-cpp
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/3rdparty/yaml-cpp/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()
add_subdirectory(3rdparty/yaml-cpp)
include_directories(3rdparty/yaml-cpp/include)
set(libs ${libs} yaml-cpp)

# spdlog
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/3rdparty/spdlog/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()
add_subdirectory(3rdparty/spdlog lib/spdlog)
if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()
include_directories(3rdparty/spdlog/include)
set(libs ${libs} spdlog::spdlog)

# sources
file(GLOB sources CONFIGURE_DEPENDS ./source/*.c*  ./source/game/*.c*)

# executable
add_executable(SpaceCombat main.cpp)
target_sources(SpaceCombat PUBLIC ${sources})
target_link_libraries(SpaceCombat ${libs})

# output
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
