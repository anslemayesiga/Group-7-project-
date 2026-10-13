# Build the validation execution binary
add_executable(run_preprocessing_tests tests/test_dataset.cpp src/preprocessing.cpp src/dataset.cpp)
target_include_directories(run_preprocessing_tests PRIVATE include)
