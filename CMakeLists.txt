cmake_minimum_required(VERSION 2.8)

project(balgo CXX)

set(root_dir ${PROJECT_SOURCE_DIR})
set(src_dir ${root_dir}/src)
set(build_dir ${root_dir}/build)
set(bin_dir ${root_dir}/bin)
set(lib_dir ${root_dir}/lib)
set(third_dir ${root_dir}/../third_party)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CXX_FLAGS
 -g
 # -DVALGRIND
 -Wall
 -Wextra
 # -m32
 -Werror
 #-Wconversion
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 #-march=native
 # -MMD
  -std=c++0x
  -fopenmp
 )
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")

set(EXECUTABLE_OUTPUT_PATH ${bin_dir})
set(LIBRARY_OUTPUT_PATH ${lib_dir})

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

include_directories(
    ${src_dir}
    ${third_dir}/include
)
link_directories(
    ${lib_dir}
    ${third_dir}/lib
)

#self-defined functions
	
function(add_test src)
	message(STATUS "src: " ${src})
	string(REGEX REPLACE "\\..*" "" testname ${src})
    set(srcs ${src} ${src_dir}/test_main.cpp)
	add_executable(${testname} ${srcs})
	target_link_libraries(${testname} gtest)
endfunction()	

add_subdirectory(src)

