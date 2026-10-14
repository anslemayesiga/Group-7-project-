cmake_minimum_required(VERSION 3.10)
project(RidgeML_Library VERSION 1.0)

# Force the project environment to build with standard modern C++17 properties
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Compile your reusable core ML library module targets 
add_library(ridge_ml_lib 
    src/data_loader.cpp
)

# 2. Declare the public headers path so external applications can find module interface definitions
target_include_directories(ridge_ml_lib PUBLIC include)

# 3. Create an executable process target to verify your unit tests automatically
add_executable(test_data_loader 
    tests/test_data_loader.cpp
)

# 4. Link your executable binary directly into the compiled library layer assets 
target_link_libraries(test_data_loader PRIVATE ridge_ml_lib)
 
