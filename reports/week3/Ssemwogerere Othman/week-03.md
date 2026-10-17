# Week 3 Individual Progress Report

**Name:** Ssemwogerere Othman  
**Assigned module:** Model evaluation metrics  
**Reporting period:** 13-19 October 2026 (status as of 17 October)

> Drafted from the agreed Week 1 responsibilities and the Git history available in the project. A missing commit is not proof that no work was done. The member should add evidence for offline or unmerged work and verify all details before submission.

## Completed / repository evidence

- No Week 3 evaluation HPP/CPP/test commit or individual Week 3 report is present in the available history.

## In Progress

- No evaluation implementation can be verified. Add evidence for any work done outside Git.

## Challenges/Blockers

- Metrics must agree on target/prediction vector types and integrate with the two model outputs.

## Next Week - files to merge

- Add tests for each metric, equal-length validation, and constant-target R-squared behavior; confirm metric definitions with model owners. No tests were run during this follow-up.

## AI Use

- **OpenAI Codex (17 October):** drafted this report from repository evidence and repaired integration in the shared checkout across Matrix, CSV loading, feature scaling, normal-equation solving, ridge cost, CMake, and a demo. This is group-level AI-assisted work, not an individual contribution by Ssemwogerere Othman. The team must review and understand these changes before accepting them.
- Add any other AI tools this member used for their own module work; do not mark none without checking.

## Week 3 shared code status (Codex-assisted)

The current checkout now contains `include/Group-7-project-ridge-lib/metrics.hpp` and `src/metrics.cpp`, prepared as a group-level draft with Codex assistance. The available history does not establish these as Ssemwogerere's individual work. Review and adapt the metric definitions and add personal work/evidence before submitting.

## OOP Concepts and Class Layout (Week 3)

**Code files prepared for the assigned module:** `include/Group-7-project-ridge-lib/metrics.hpp`, `src/metrics.cpp`.

- **Encapsulation:** `RegressionMetrics` groups metric operations. It has no instance data; its methods are public static functions.
- **Inheritance and polymorphism:** None. Metrics have no base/derived relationship or virtual methods.
- **Layout to draw:** `RegressionMetrics` with public static `mean_absolute_error`, `mean_squared_error`, `root_mean_squared_error`, and `r_squared`; no private/protected members.

These files were prepared with OpenAI Codex assistance for the group. Review and understand them before claiming individual authorship. Draw the actual class layout by hand and add a clear photo. See [shared class-layout guide](../class-layouts.md#ssemwogerere-othman-metrics).
