# Week 3 Individual Progress Report

**Name:** Mandela Nickson  
**Assigned module:** Ridge cost function and L2 regularization  
**Reporting period:** 13-19 October 2026 (status as of 17 October)

> Drafted from the agreed Week 1 responsibilities and the Git history available in the project. A missing commit is not proof that no work was done. The member should add evidence for offline or unmerged work and verify all details before submission.

## Completed / repository evidence

- Commit 11df2c1 on 13 October adds src/ridge_regression_cost.cpp. It contained a standalone main() and had no public cost header or focused test.

## In Progress

- The cost formula was drafted; the public API, error handling, intercept convention, and tests were not integrated at the Week 3 checkpoint.

## Challenges/Blockers

- A source file with main() cannot be linked into a reusable library. The intercept-exclusion rule needs to match the ridge model's parameter layout.

## Next Week - files to merge

- Add tests for ridge cost and for `RidgeRegression` fit/predict, non-negative lambda validation, intercept handling, and polymorphic use through `Regressor`. Review the Codex-assisted model files. No tests were run during this follow-up.

## AI Use

- **OpenAI Codex (17 October):** drafted this report from repository evidence and repaired integration in the shared checkout across Matrix, CSV loading, feature scaling, normal-equation solving, ridge cost, CMake, and a demo. This is group-level AI-assisted work, not an individual contribution by Mandela Nickson. The team must review and understand these changes before accepting them.
- Add any other AI tools this member used for their own module work; do not mark none without checking.

## Week 3 shared code status (Codex-assisted)

The current checkout contains `ridge_cost.hpp`, `ridge_regression_cost.cpp`, `ridge_regression.hpp`, and `ridge_regression.cpp` under the project include/source folders. The Ridge estimator is a group-level draft prepared with Codex assistance; repository history does not establish it as Mandela's individual contribution. Review and adapt it and add personal work/evidence before submitting.

## OOP Concepts and Class Layout (Week 3)

**Code files prepared for the assigned module:** `include/Group-7-project-ridge-lib/ridge_cost.hpp`, `src/ridge_regression_cost.cpp`, `include/Group-7-project-ridge-lib/ridge_regression.hpp`, and `src/ridge_regression.cpp`.

- **Encapsulation:** `RidgeRegression` keeps `lambda_`, fitted coefficients, and fitted state private. Public methods expose fitting, prediction, and read-only accessors.
- **Inheritance and runtime polymorphism:** `RidgeRegression` publicly derives from abstract `Regressor` and overrides virtual `fit` and `predict`. The separate `ridge_cost` helper remains a free function.
- **Layout to draw:** `RidgeRegression` derives from `Regressor`; private `lambda_`, `coefficients_`, `fitted_`; public constructor, `fit`, `predict`, `coefficients`, `lambda`.

The new model files were prepared with OpenAI Codex assistance for the group. Review and understand them before claiming individual authorship. Draw the actual class layout by hand and add a clear photo. See [shared class-layout guide](../class-layouts.md#mandela-nickson-ridge-regression).
