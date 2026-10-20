cmake_minimum_required(VERSION 3.10)
project(RidgeML_Library VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compile library binary layer using your individual source code implementation file
add_library(ridge_ml_lib 
    src/data_loader.cpp
)

target_include_directories(ridge_ml_lib PUBLIC include)

# Setup executable testing binary target outputs
add_executable(test_data_loader 
    tests/test_data_loader.cpp
)

target_link_libraries(test_data_loader PRIVATE ridge_ml_lib)
 
