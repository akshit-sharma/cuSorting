cmake_minimum_required(VERSION 2.8)

find_package(CUDA REQUIRED)

set(CUDA_64_BIT_DEVICE_CODE ON)
set(CUDA_SEPARABLE_COMPILATION ON)
set(CUDA_PROPAGATE_HOST_FLAGS OFF)
#set(CUDA_HOST_COMPILER clang++)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

list( APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_30,code=sm_30; -std=c++11")



add_subdirectory(CuSorting)
