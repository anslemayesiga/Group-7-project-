# Week 3 Individual Progress Report

**Name:** Khalid Taban Luate  
**Assigned module:** Normal equation and linear solvers  
**Reporting period:** 13-19 October 2026 (status as of 17 October)

> Drafted from the agreed Week 1 responsibilities and the Git history available in the project. A missing commit is not proof that no work was done. The member should add evidence for offline or unmerged work and verify all details before submission.

## Completed / repository evidence

- Commits 64a8043 and 77e547b on 14 October add include/ridge_ml/normal_equation.hpp and src/normal_equation.cpp. The implementation contains Gaussian elimination with partial pivoting and an unregularized normal equation; no solver test was added.

## In Progress

- The solver needs integration with the Matrix public API and tests for dimensions, row swaps, singular inputs, and a known solution.

## Challenges/Blockers

- The initial source included a non-existent header path and used a legacy Matrix namespace/path; this was repaired in the current shared checkout. No tests/normal-equation file exists yet.

## Next Week - files to merge

- Add focused tests for Gaussian elimination (including pivoting and singular inputs) and normal-equation fitting. Review the current Matrix API integration. No tests were run during this follow-up.

## AI Use

- **OpenAI Codex (17 October):** drafted this report from repository evidence and repaired integration in the shared checkout across Matrix, CSV loading, feature scaling, normal-equation solving, ridge cost, CMake, and a demo. This is group-level AI-assisted work, not an individual contribution by Khalid Taban Luate. The team must review and understand these changes before accepting them.
- Add any other AI tools this member used for their own module work; do not mark none without checking.

## Week 3 shared code status (Codex-assisted)

The current checkout contains `include/Group-7-project-ridge-lib/normal_equation.hpp` and `src/normal_equation.cpp`; includes and validation were aligned with the Matrix API during Codex-assisted integration. These group-level edits are not proof of individual authorship. Review and add any personal work/evidence before submitting.

## OOP Concepts and Class Layout (Week 3)

**Code reviewed:** `include/Group-7-project-ridge-lib/normal_equation.hpp`, `src/normal_equation.cpp`.

- **Encapsulation:** Not applicable to the solver API as currently written; `gaussian_solve` and `fit_normal_equation` are namespace-level functions, not class methods.
- **Polymorphism and inheritance:** None in these files; no class, virtual function, base/derived relationship, or `protected` member is present.
- **Layout to draw:** There is no class layout for this function-only module. Draw the two free function signatures and state “no class/inheritance in current implementation,” or update this report if the member adds an actual class.

Include the corresponding hand-drawn function/API layout photo with the report. See [shared class-layout guide](../class-layouts.md#khalid-taban-luate-normal-equation).
