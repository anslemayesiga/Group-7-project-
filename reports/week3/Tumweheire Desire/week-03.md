# Week 3 Individual Progress Report

**Name:** Tumweheire Desire  
**Assigned module:** Gradient descent  
**Reporting period:** 13-19 October 2026 (status as of 17 October)

> Drafted from the agreed Week 1 responsibilities and the Git history available in the project. A missing commit is not proof that no work was done. The member should add evidence for offline or unmerged work and verify all details before submission.

## Completed / repository evidence

- No Week 3 gradient-descent HPP/CPP/test commit or individual Week 3 report is present in the available history.

## In Progress

- No optimizer implementation can be verified. This does not establish that the member did no offline work; link any existing branch or files before submission.

## Challenges/Blockers

- The optimizer depends on the agreed Matrix, cost, and model interfaces.

## Next Week - files to merge

- Add tests for the gradient update, cost-history shape, regularization, invalid dimensions, and constructor validation. Review the stopping behavior (currently fixed iteration count). No tests were run during this follow-up.

## AI Use

- **OpenAI Codex (17 October):** drafted this report from repository evidence and repaired integration in the shared checkout across Matrix, CSV loading, feature scaling, normal-equation solving, ridge cost, CMake, and a demo. This is group-level AI-assisted work, not an individual contribution by Tumweheire Desire. The team must review and understand these changes before accepting them.
- Add any other AI tools this member used for their own module work; do not mark none without checking.

## Week 3 shared code status (Codex-assisted)

The current checkout now contains `include/Group-7-project-ridge-lib/gradient_descent.hpp` and `src/gradient_descent.cpp`, prepared as a group-level draft with Codex assistance. The repository history does not establish them as Tumweheire's individual work. Review and adapt the implementation and add personal work/evidence before submitting.

## OOP Concepts and Class Layout (Week 3)

**Code files prepared for the assigned module:** `include/Group-7-project-ridge-lib/gradient_descent.hpp`, `src/gradient_descent.cpp`.

- **Encapsulation:** `GradientDescent` keeps learning rate, iteration count, and regularization strength private. Public constructor and `fit` form its interface. `GradientDescentResult` is a public result struct.
- **Inheritance and polymorphism:** None in this optimizer; it is a standalone algorithm and does not derive from `Regressor`.
- **Layout to draw:** Private `learning_rate_`, `iterations_`, `lambda_`; public constructor and `fit`; separate public `GradientDescentResult` fields `parameters` and `cost_history`.

These files were prepared with OpenAI Codex assistance for the group. Review and understand them before claiming individual authorship. Draw the actual class layout by hand and add a clear photo. See [shared class-layout guide](../class-layouts.md#tumweheire-desire-gradient-descent).
