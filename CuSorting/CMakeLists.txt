
project(CuSorting)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


file(GLOB CPP_SRC
        "*.cpp"
        )
        
        
file(GLOB CPP_HEADER
        "*.h"
        )
        
        

add_executable(CuSorting ${CPP_HEADER} ${CPP_SRC})

