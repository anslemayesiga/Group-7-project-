cmake_minimum_required(VERSION 3.16)
project(ridgelib VERSION 0.2.0 LANGUAGES CXX)

<<<<<<< HEAD
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compile library binary layer using your individual source code implementation file
add_library(ridge_ml_lib 
=======
add_library(ridgelib
    src/MinMaxScaler.cpp
>>>>>>> main
    src/data_loader.cpp
    src/gradient_descent.cpp
    src/linear_regression.cpp
    src/matrix.cpp
    src/metrics.cpp
    src/normal_equation.cpp
    src/ridge_regression.cpp
    src/ridge_regression_cost.cpp
    src/tuning.cpp
)
add_library(ridgelib::ridgelib ALIAS ridgelib)
target_include_directories(ridgelib PUBLIC include)
target_compile_features(ridgelib PUBLIC cxx_std_17)

<<<<<<< HEAD
target_include_directories(ridge_ml_lib PUBLIC include)

# Setup executable testing binary target outputs
add_executable(test_data_loader 
    tests/test_data_loader.cpp
)

target_link_libraries(test_data_loader PRIVATE ridge_ml_lib)
 
=======
add_executable(ridge_demo examples/ridge_demo.cpp)
target_link_libraries(ridge_demo PRIVATE ridgelib::ridgelib)

add_executable(oop_demo examples/oop_demo.cpp)
target_link_libraries(oop_demo PRIVATE ridgelib::ridgelib)

include(CTest)
if(BUILD_TESTING)
    add_executable(test_data_loader tests/test_data_loader.cpp)
    target_link_libraries(test_data_loader PRIVATE ridgelib::ridgelib)
    add_test(NAME data_loader_split COMMAND test_data_loader)
endif()
>>>>>>> main
