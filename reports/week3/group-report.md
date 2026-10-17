# Week 3 Group Progress Report

Project: ridgelib - C++ library for Ridge Regression
Reporting period: 13-19 October 2026 (status as of 17 October)

## Completed - repository evidence

- Added MinMaxScaler interface and implementation, plus initial normal-equation solver and ridge-cost source in the shared repository.
- Added normal-equation header/source on 14 October; added ridge-cost source on 13 October.
- Integrated the data-preprocessing branch into main.
- During this follow-up,  Aligned existing modules around the ridge_ml API: added Matrix method definitions, made CSV loading return usable data and validate split inputs, standardized the scaler namespace, corrected normal-equation includes and input handling, exposed ridge cost through a header and removed the library-source main(), updated CMake to build current sources, and added a small demonstration program.

## In Progress

- Validation: installed CMake 4.4.4, configured the project with MinGW, and built all CMake targets successfully. Both demos ran; CTest passed the existing DataLoader test (1/1). Focused tests for the other modules are still needed.

- Review and refine the prepared regressor, linear-regression baseline, ridge estimator, gradient descent, evaluation, and tuning modules.
- Add focused tests for Matrix, scaler, normal equation, ridge cost/model, preprocessing, optimizer, metrics, and tuning.
- Complete the build instructions and project description in the README using the group's own writing.

## OOP Concepts and Class Layouts

- **Encapsulation:** Implemented in `Matrix` through private dimensions and a private index helper; implemented in `MinMaxScaler` through private fitted bounds and public operations. `DataLoader` has public nested data structs and no private instance state, so encapsulation there is limited.
- **Polymorphism:** `Matrix` arithmetic operators and `DataLoader::trainTestSplit` overloads use compile-time overloading. `Regressor` provides runtime virtual dispatch for the linear and ridge models; `GridSearchTuner` invokes models through `Regressor` pointers.
- **Inheritance:** `LinearRegression` and `RidgeRegression` publicly derive from `Regressor`. Other current classes do not use inheritance; no `protected` data members are used.
- The normal equation solver and ridge-cost calculation are free functions. Week 3 files have now been prepared for linear regression, the regressor interface, ridge regression, gradient descent, metrics, and tuning.
- Each member has an OOP section in their individual Week 3 report. See for the classes and APIs to copy onto paper. Paper drawing photos supplied by the members 

## Week 3 module files prepared

- Ayesiga Anslem — `matrix.hpp`, `matrix.cpp` (Matrix implementation).
- Wobusobozi Chrispus Owen — `data_loader.hpp`, `data_loader.cpp` (data loader).
- Kyelanyi Martin Tom — `MinMaxScaler.hpp`, `MinMaxScaler.cpp` (scaler).
- Kamugisha Elias — `linear_regression.hpp`, `linear_regression.cpp`.
- Mutyaba Rashid — `regressor.hpp`.
- Khalid Taban Luate — `normal_equation.hpp`, `normal_equation.cpp` (solver functions).
- Mandela Nickson — `ridge_cost.hpp`, `ridge_regression_cost.cpp`, `ridge_regression.hpp`, `ridge_regression.cpp`.
- Tumweheire Desire — `gradient_descent.hpp`, `gradient_descent.cpp`.
- Ssemwogerere Othman — `metrics.hpp`, `metrics.cpp`.
- Ainemugabe Crisbert — `tuning.hpp`, `tuning.cpp`.



## Challenges/Blockers

- The new module HPP/CPP files . Members must review and understand their assigned module; focused tests are not yet present for most modules.
- The project structure list in the Week 1 report conflicted with its explicit owner list for solver, cost, and metrics. The merge plan follows the explicit owner list and asks the team to confirm it.
- The repository has no verified scikit-learn comparison or complete test suite yet.
- LICENSE has no usable license text.

## Next Week - merge work

Use reports/module-merge-plan.md to adapt the prepared HPP/CPP files, add the listed focused tests, and integrate in dependency order. Each member should commit their own reviewed work, request review, and update their progress report with exact files and verified results.

## AI Use

- Tool: OpenAI Codex.
- Purpose: Review and repair integration in the codes made
- 

