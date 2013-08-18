cmake_minimum_required(VERSION 2.8)

project(balgo CXX)

set(CMAKE_PREFIX_PATH "../third_party")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

set(root_dir ${PROJECT_SOURCE_DIR})
set(src_dir ${root_dir}/src)
set(build_dir ${root_dir}/build)
set(bin_dir ${root_dir}/bin)
set(lib_dir ${root_dir}/lib)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CXX_FLAGS
 -g
 #-DVALGRIND
 -Wall
 -Wextra
 #-m32
 -Werror
 #-Wconversion
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 #-march=native
 #-MMD
 #-std=c++0x
 )
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")

set(EXECUTABLE_OUTPUT_PATH ${bin_dir})
set(LIBRARY_OUTPUT_PATH ${lib_dir})

find_package(gtest REQUIRED)

include_directories(
    ${src_dir}
)
link_directories(
    ${lib_dir}
)

#self-defined functions

# Add a library
function(add_lib name srcstr)
	message(STATUS "[add_lib] name=${name}, srcstr=${srcstr}, depstr=${depstr}")
  string(REGEX MATCHALL "[^ ;]+" srcs "${srcstr}")
  string(REGEX MATCHALL "[^ ;]+" deps "${depstr}")
	message(STATUS "srcs=${srcs}")
	message(STATUS "deps=${deps}")
	add_library(${name} ${srcs})
	target_link_libraries(${name} ${deps})
endfunction()	

# Add a binary
function(add_bin name)
  message(STATUS "[add_bin] ARGC=${ARGC}, ARGV=${ARGV}")
  add_executable(${name} ${name})
  if (${ARGC} GREATER 1)
    string(REGEX MATCHALL "[^ ;]+" deps "${ARGV1}")
    list(LENGTH ${deps} len)
    if (${len} GREATER 0)
      message(STATUS "${len} deps: ${deps}")
      target_link_libraries(${name} ${deps})
    endif()
  endif()
endfunction()	

# Add a unittest
# A optional argument can specify the dependcies
# Example1: add_test(foo_test)
# Example2: add_test(foo_test "glog")
# Example3: add_test(foo_test "gtest glog")
function(add_test name)
  message(STATUS "[add_test] name=${name}, ARGC=${ARGC}, ARGV=${ARGV}")
  set(libs gtest gtest_main)
  if (${ARGC} GREATER 1)
    string(REGEX MATCHALL "[^ ]+" deps "${ARGV1}")
    list(LENGTH deps len)
    if (${len} GREATER 0)
      message(STATUS "${len} deps: ${deps}")
      list(APPEND libs ${deps})
    endif()
  endif()
  message(STATUS "[add_test] name=${name}, libs=${libs}")

	add_executable(${name} ${name})
	target_link_libraries(${name} ${libs})
endfunction()	

add_subdirectory(src)

