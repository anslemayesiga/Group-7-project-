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

## AI Use

- **OpenAI Codex (17 October):** drafted this report from repository evidence and repaired integration in the shared checkout across Matrix, CSV loading, feature scaling, normal-equation solving, ridge cost, CMake, and a demo. This is group-level AI-assisted work, not an individual contribution by Mutyaba Rashid. The team must review and understand these changes before accepting them.
- Add any other AI tools this member used for their own module work; do not mark none without checking.

## Week 3 shared code status (Codex-assisted)

The current checkout now contains `include/Group-7-project-ridge-lib/regressor.hpp`, an abstract interface draft prepared with Codex assistance for the group. The available history does not establish it as Mutyaba's individual work. Review and adapt the interface and add any personal work/evidence before submitting.

## OOP Concepts and Class Layout (Week 3)

**Code file prepared for the assigned module:** `include/Group-7-project-ridge-lib/regressor.hpp`.

- **Encapsulation:** `Regressor` defines a controlled public model interface and has no data members.
- **Inheritance:** It is an abstract base class. `LinearRegression` and `RidgeRegression` publicly derive from it.
- **Runtime polymorphism:** Pure virtual `fit` and `predict` are overridden by concrete models. `GridSearchTuner` invokes those methods through `std::unique_ptr<Regressor>`.
- **Layout to draw:** `Regressor` with public virtual destructor and pure virtual `fit`/`predict`, and arrows from `LinearRegression` and `RidgeRegression` to the base. No private/protected state in the interface.

These files were prepared with OpenAI Codex assistance for the group. Review and understand them before claiming individual authorship. Draw the actual class layout by hand and add a clear photo. See [shared class-layout guide](../class-layouts.md#mutyaba-rashid-regressor-interface).
