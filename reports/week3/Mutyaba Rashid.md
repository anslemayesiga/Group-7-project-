# Week 3 Individual Progress Report

**Name:** Mutyaba Rashid  
**Assigned module:** Regressor interface and prediction  
**Reporting period:** 13-19 October 2026 (status as of 17 October)



## Completed / repository evidence

- A 13 October commit adds or revises a Regressor explanation note; no regressor HPP/CPP/test is recorded in the available source tree.

## In Progress

- The prediction routine is described in the Week 2 note, but no working interface/implementation has been merged.

## Challenges/Blockers

- The public fit/predict signatures and parameter/intercept ownership must be agreed with the baseline and ridge model owners.

## Next Week - files to merge

- Add interface-level tests/examples showing `LinearRegression` and `RidgeRegression` used through `Regressor*` or `unique_ptr<Regressor>`; review the abstract API and dependent models. No tests were run during this follow-up.


**Code file prepared for the assigned module:** `include/Group-7-project-ridge-lib/regressor.hpp`.

- **Encapsulation:** `Regressor` defines a controlled public model interface and has no data members.
- **Inheritance:** It is an abstract base class. `LinearRegression` and `RidgeRegression` publicly derive from it.
- **Runtime polymorphism:** Pure virtual `fit` and `predict` are overridden by concrete models. `GridSearchTuner` invokes those methods through `std::unique_ptr<Regressor>`.
- **Layout to draw:** `Regressor` with public virtual destructor and pure virtual `fit`/`predict`, and arrows from `LinearRegression` and `RidgeRegression` to the base. No private/protected state in the interface.

