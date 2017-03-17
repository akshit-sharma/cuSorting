
project(cuSorting)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


file(GLOB CPP_SRC
        "*.cpp"
        )
        
        
file(GLOB CPP_HEADER
        "*.h"
        )
        
file(GLOB CUDA_SRC
        "*.cu"
        )

cuda_compile(CUDA_OBJ ${CUDA_SRC})        
        

cuda_add_executable(cuSorting ${CPP_HEADER} ${CPP_SRC} ${CUDA_OBJ})

