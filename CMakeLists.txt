cmake_minimum_required(VERSION 3.16)
project(ridgelib VERSION 1.0.0 LANGUAGES CXX)

option(RIDGELIB_BUILD_EXAMPLES "Build RidgeLib examples" ON)
option(RIDGELIB_ENABLE_WARNINGS "Enable useful compiler warnings" ON)
include(CTest)

add_library(ridgelib
    src/MinMaxScaler.cpp
    src/StandardScaler.cpp
    src/data_loader.cpp
    src/gradient_descent.cpp
    src/linear_regression.cpp
    src/matrix.cpp
    src/metrics.cpp
    src/normal_equation.cpp
    src/normal_solver.cpp
    src/ridge_cost_function.cpp
    src/tuning.cpp
)
add_library(ridgelib::ridgelib ALIAS ridgelib)
target_include_directories(ridgelib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_compile_features(ridgelib PUBLIC cxx_std_17)
if(RIDGELIB_ENABLE_WARNINGS)
    if(MSVC)
        target_compile_options(ridgelib PRIVATE /W4 /permissive-)
    else()
        target_compile_options(ridgelib PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

if(RIDGELIB_BUILD_EXAMPLES)
    add_executable(ridge_demo examples/ridge_demo.cpp)
    target_link_libraries(ridge_demo PRIVATE ridgelib::ridgelib)
    add_executable(oop_demo examples/oop_demo.cpp)
    target_link_libraries(oop_demo PRIVATE ridgelib::ridgelib)
endif()

include(GNUInstallDirs)
install(TARGETS ridgelib EXPORT ridgelibTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT ridgelibTargets NAMESPACE ridgelib:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ridgelib)

if(BUILD_TESTING)
    foreach(test_target IN ITEMS test_data_loader test_metrics test_matrix test_scaler test_standard_scaler test_linear_regression test_normal_equation tests_normal_solver test_ridge_cost_function test_gradient_descent test_tuning test_workflow)
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_target}.cpp")
            add_executable(${test_target} "tests/${test_target}.cpp")
            target_link_libraries(${test_target} PRIVATE ridgelib::ridgelib)
            add_test(NAME ${test_target} COMMAND ${test_target})
        endif()
    endforeach()
endif()
