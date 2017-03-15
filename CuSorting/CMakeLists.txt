
project(CuSorting)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


SET(SOURCES
        Main.cpp
        Source.cpp
        BiggerSource.cpp
        SchemeDataStructure.cpp
        GlobalHeader.cpp
        BiggerSource.h
        Main.h
        Source.h
        SchemeDataStructure.h
        GlobalHeader.h
        ResultsDataStructure.cpp ResultsDataStructure.h)

add_executable(CuSorting ${SOURCES})

