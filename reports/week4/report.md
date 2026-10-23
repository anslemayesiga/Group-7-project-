# Week 4 Group Completion Report

**Project:** RidgeLib — Ridge Regression from Scratch  
**Reporting period:** 20–23 October 2026

## Completed

- Reconciled the data loader with the public `ridge_ml::DataLoader` interface. It reads numeric CSV data, validates row shapes and values, separates the last column as the target, and creates deterministic train/test splits.
- Repaired the CMake project definition and exposed the reusable `ridgelib::ridgelib` C++17 target with public include paths, examples, and CTest integration.
- Updated the data-loader test to exercise CSV loading, feature/target separation, splitting, and invalid split rejection through the public API.
- Documented library integration and usage in the root README.

## Verification

- Configured and built with GNU C++ 16.2 using the MinGW Makefiles generator.
- Both `ridge_demo` and `oop_demo` compiled.
- CTest result: 1 test passed, 0 failed (`test_data_loader`).

## Remaining limitation

- The old `linear_ml::NormalSolver` implementation uses a retired Matrix API and is excluded from the CMake library target. Use `ridge_ml::fit_normal_equation` and the current `ridge_ml::Matrix` API. Dedicated tests for matrix arithmetic, ridge fitting, optimizer behavior, and evaluation metrics are still recommended before release.

## Reuse

Consumers can add this repository using `add_subdirectory(...)` and link `ridgelib::ridgelib`. See the root README for the complete build and usage instructions.
