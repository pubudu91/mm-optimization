cmake_minimum_required(VERSION 3.6)
project(lab4_5_final)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lblas")

set(SOURCE_FILES main.cpp version1/version1.cpp utils/MiscOps.cpp utils/MiscOps.h utils/MatrixOps.cpp utils/MatrixOps.h utils/OptimizedMatrixOps.cpp utils/OptimizedMatrixOps.h common/Matrix1D.cpp common/Matrix1D.h version1/version1.h version2/version2.cpp version2/version2.h version3/version3.cpp version3/version3.h)
add_executable(lab4_5_final ${SOURCE_FILES})

target_link_libraries(lab4_5_final blas)