# Week 4 Individual Progress Report

**Name:** Ayesiga Anslem  
**Assigned module:** Matrix and vector operations  
**Reporting period:** 20–23 October 2026

## Completed / verified project status

- The shared library exposes `ridge_ml::Matrix` and `ridge_ml::Vector` through `include/Group-7-project-ridge-lib/matrix.hpp` and `src/matrix.cpp`.
- Matrix operations are included in the reusable `ridgelib::ridgelib` C++17 target. The matrix implementation compiled as part of the successful full library build.
- The root README documents how another CMake project can link the library and include its public headers.

## Verification

- Full library and both examples compiled using GNU C++ 16.2 with MinGW Makefiles.
- Registered CTest result: 1 passed, 0 failed. This test covers the data loader; there is not yet a dedicated matrix unit-test target.

## Follow-up

- Add focused Matrix tests for dimensions, bounds, arithmetic, transpose, matrix-vector multiplication, and dot product before release.
- Review and merge any remaining individual matrix work based on its actual source changes and tests.

## Transferred responsibility

Week 4 work previously assigned to Tumweheire Desire (gradient descent) was transferred to Ayesiga Anslem at the user's direction. The repository contains include/Group-7-project-ridge-lib/gradient_descent.hpp and src/gradient_descent.cpp; no focused gradient-descent test is registered. This records the handover and current shared-code status, not unverified completion by either member.
