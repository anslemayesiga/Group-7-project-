cmake_minimum_required(VERSION 3.14)
project(FeatureScalerLibrary VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Main Shared Library Target
add_library(feature_scaler
    src/MinMaxScaler.cpp
    src/StandardScaler.cpp
)

# Specify public include directories
target_include_directories(feature_scaler PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# 2. Example Application Executable
add_executable(example_scaling examples/example_scaling.cpp)
target_link_libraries(example_scaling PRIVATE feature_scaler)

# 3. Unit Tests Executable
add_executable(test_scalers tests/test_scalers.cpp)
target_link_libraries(test_scalers PRIVATE feature_scaler)
