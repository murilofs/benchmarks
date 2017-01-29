cmake_minimum_required(VERSION 3.6)
project(benchmarks)

set(CMAKE_CXX_STANDARD 11)

set(COWICHAN_SOURCE_FILES
        main_cowichan.cc
        cowichan.h
        cowichan.cc
        Timer.cc
        Timer.h database.h)

add_executable(cowichan ${COWICHAN_SOURCE_FILES})
target_link_libraries(cowichan db)