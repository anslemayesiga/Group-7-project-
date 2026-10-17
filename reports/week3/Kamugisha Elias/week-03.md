# Week 3 Individual Progress Report

**Name:** Kamugisha Elias  
**Assigned module:** Linear regression baseline  
**Reporting period:** 13-19 October 2026 (status as of 17 October)

> Drafted from the agreed Week 1 responsibilities and the Git history available in the project. A missing commit is not proof that no work was done. The member should add evidence for offline or unmerged work and verify all details before submission.

## Completed / repository evidence

- A 13 October commit adds a Linear Regression explanation/design note under reports/week_1,2,3,4/Kamugisha Elias/read,md. No linear_regression.hpp, linear_regression.cpp, or regression test is recorded.

## In Progress

- The design note describes the baseline, but the assigned fit/predict implementation is not in the repository.

## Challenges/Blockers

- The baseline needs the Matrix and regressor interfaces. The prior Week 2 logging tracker plan did not produce a model implementation.

## Next Week - files to merge

- Add focused tests for `LinearRegression` fit/predict, intercept handling, wrong dimensions, and use through `Regressor`; review/adapt the Codex-assisted HPP/CPP before merge. No tests were run during this follow-up.

## AI Use

- **OpenAI Codex (17 October):** drafted this report from repository evidence and repaired integration in the shared checkout across Matrix, CSV loading, feature scaling, normal-equation solving, ridge cost, CMake, and a demo. This is group-level AI-assisted work, not an individual contribution by Kamugisha Elias. The team must review and understand these changes before accepting them.
- Add any other AI tools this member used for their own module work; do not mark none without checking.

## Week 3 shared code status (Codex-assisted)

The current checkout now contains `include/Group-7-project-ridge-lib/linear_regression.hpp` and `src/linear_regression.cpp` for the assigned baseline. Codex prepared these as group-level draft implementation; repository history does not establish them as Kamugisha's individual work. Review and adapt the files, then add any personally completed work/evidence before submitting.

## OOP Concepts and Class Layout (Week 3)

**Code files prepared for the assigned module:** `include/Group-7-project-ridge-lib/linear_regression.hpp`, `src/linear_regression.cpp`.

- **Encapsulation:** `LinearRegression` stores coefficients and fitted state privately; public `fit`, `predict`, and `coefficients` expose controlled operations.
- **Inheritance and runtime polymorphism:** `LinearRegression` publicly derives from `Regressor` and overrides its virtual `fit` and `predict` methods. Calls through a `Regressor` pointer dispatch to this model at runtime.
- **Layout to draw:** `LinearRegression` private `coefficients_`, `fitted_`; public overrides and accessor. Base class `Regressor` has a public virtual destructor and pure virtual `fit`/`predict`; no protected fields.

These files were prepared with OpenAI Codex assistance for the group. The assigned member must review and understand them before claiming individual authorship. Draw the actual class layout by hand and add a clear photo. See [shared class-layout guide](../class-layouts.md#kamugisha-elias-linear-regression).
