# Week 4 Individual Progress Report

**Name:** Ayesiga Anslem  
**Assigned module:** Matrix and vector operations  
**Reporting period:** 20–23 October 2026

## Completed 

- The shared library exposes `ridge_ml::Matrix` and `ridge_ml::Vector` through `include/Group-7-project-ridge-lib/matrix.hpp` and `src/matrix.cpp`.
- Matrix operations are included in the reusable `ridgelib::ridgelib` C++17 target. The matrix implementation compiled as part of the successful full library build.


## Verification

- Full library and both examples compiled using with MinGW Makefiles.
- Registered CTest result: 1 passed, 0 failed. This test covers the data loader; there is not yet a dedicated matrix unit-test target.

## Follow-up

- Add focused Matrix tests for dimensions, bounds, arithmetic, transpose, matrix-vector multiplication, and dot product before release.


## Transferred responsibility

 work previously assigned to Tumweheire Desire (gradient descent) was transferred to  me. and completed all tasks 
