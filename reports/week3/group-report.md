# Week 3 Group Progress Report

Project: ridgelib - C++ library for Ridge Regression
Reporting period: 13-19 October 2026 (status as of 17 October)
Repository branch: main was fast-forwarded to the cached origin/main before this review.

## Completed - repository evidence

- Added MinMaxScaler interface and implementation, plus initial normal-equation solver and ridge-cost source in the shared repository.
- Added normal-equation header/source on 14 October; added ridge-cost source on 13 October.
- Integrated the data-preprocessing branch into main.
- During this follow-up, OpenAI Codex aligned existing modules around the ridge_ml API: added Matrix method definitions, made CSV loading return usable data and validate split inputs, standardized the scaler namespace, corrected normal-equation includes and input handling, exposed ridge cost through a header and removed the library-source main(), updated CMake to build current sources, and added a small demonstration program.
- These Codex-authored changes are group integration assistance. They are not individual member contributions and must be reviewed and understood before the group accepts them.

## In Progress

- Validation: installed CMake 4.4.4, configured the project with MinGW, and built all CMake targets successfully. Both demos ran; CTest passed the existing DataLoader test (1/1). Focused tests for the other modules are still needed.

- Review and refine the prepared regressor, linear-regression baseline, ridge estimator, gradient descent, evaluation, and tuning modules.
- Add focused tests for Matrix, scaler, normal equation, ridge cost/model, preprocessing, optimizer, metrics, and tuning.
- Complete the build/run instructions and project description in the README using the group's own writing.

## OOP Concepts and Class Layouts

- **Encapsulation:** Implemented in `Matrix` through private dimensions/data and a private index helper; implemented in `MinMaxScaler` through private fitted bounds/state and public operations. `DataLoader` has public nested data structs and no private instance state, so encapsulation there is limited.
- **Polymorphism:** `Matrix` arithmetic operators and `DataLoader::trainTestSplit` overloads use compile-time overloading. `Regressor` provides runtime virtual dispatch for the linear and ridge models; `GridSearchTuner` invokes models through `Regressor` pointers.
- **Inheritance:** `LinearRegression` and `RidgeRegression` publicly derive from `Regressor`. Other current classes do not use inheritance; no `protected` data members are used.
- The normal-equation solver and ridge-cost calculation are free functions. Week 3 files have now been prepared for linear regression, the regressor interface, ridge regression, gradient descent, metrics, and tuning.
- Each member has an OOP section in their individual Week 3 report. See [class-layout reference](class-layouts.md) for the classes and APIs to copy onto paper. Paper drawing photos have not yet been added and must be supplied by the members.

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
- Shared OOP demonstration — `examples/oop_demo.cpp` exercises model inheritance, virtual dispatch, metrics, and tuning.

OpenAI Codex prepared the new module files and report updates as group-level assistance. Members must review and understand their assigned files before attributing or submitting them. The project build and existing DataLoader test passed; other module-specific tests are not yet present.

## Challenges/Blockers

- The new module HPP/CPP files are Codex-assisted drafts. Members must review and understand their assigned module; focused tests are not yet present for most modules.
- The project structure list in the Week 1 report conflicted with its explicit owner list for solver, cost, and metrics. The merge plan follows the explicit owner list and asks the team to confirm it.
- The repository has no verified scikit-learn comparison or complete test suite yet.
- README.md remains a one-line placeholder; the assignment requires the group to hand-type it.
- LICENSE has no usable license text.

## Next Week - merge work

Use reports/module-merge-plan.md to review/adapt the prepared HPP/CPP files, add the listed focused tests, and integrate in dependency order. Each member should commit their own reviewed work, request review, and update their progress report with exact files and verified results.

## AI Use

- Tool: OpenAI Codex.
- Purpose: Review and repair integration in existing Matrix, data-loader, scaler, solver, cost, CMake, and demo files; prepare draft linear-regression, Regressor, RidgeRegression, gradient-descent, metrics, and tuning modules; draft evidence-based progress, OOP, and merge-plan documents.
- Reason: Fix path/API/build-structure defects and make repository status traceable without claiming missing modules were implemented.
- The earlier group report also records Claude use for assignment analysis and the initial project structure. Individual reports include member-declared Gemini and Meta AI use where available; each member should verify and add their personal declaration.

