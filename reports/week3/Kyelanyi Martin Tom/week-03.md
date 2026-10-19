# Week 3 Individual Progress Report

**Name:** Kyelanyi Martin Tom  
**Assigned module:** Feature scaling and build setup  
**Reporting period:** 13-19 October 2026 (status as of 17 October)

> Drafted from the agreed Week 1 responsibilities and the Git history available in the project. A missing commit is not proof that no work was done. The member should add evidence for offline or unmerged work and verify all details before submission.

## Completed / repository evidence

- Commit 417d6dc on 13 October updates CMakeLists.txt and adds include/scalerlib/MinMaxScaler.hpp and src/MinMaxScaler.cpp. No scaler test is present.

## In Progress

- MinMaxScaler is implemented in the source history. The Week 2 note also mentions StandardScaler, but no StandardScaler HPP/CPP/test is in the tree.

## Challenges/Blockers

- The original CMake target built only the data loader and did not include all library sources. Scaling has no focused tests.

## Next Week - files to merge

- Add focused tests for fitting, transforms, constant columns, empty inputs, and use-before-fit; confirm whether StandardScaler is in scope. Review CMake integration. No scaler tests were run during this follow-up.

## AI Use

- **OpenAI Codex (17 October):** drafted this report from repository evidence and repaired integration in the shared checkout across Matrix, CSV loading, feature scaling, normal-equation solving, ridge cost, CMake, and a demo. This is group-level AI-assisted work, not an individual contribution by Kyelanyi Martin Tom. The team must review and understand these changes before accepting them.
- Add any other AI tools this member used for their own module work; do not mark none without checking.

## Week 3 shared code status (Codex-assisted)

The current checkout has `include/Group-7-project-ridge-lib/MinMaxScaler.hpp` and `src/MinMaxScaler.cpp`; namespace and include paths were aligned during Codex-assisted integration. These changes are group-level assistance, not evidence of individual authorship. Review the implementation and add any personal work/evidence before submitting.

## OOP Concepts and Class Layout (Week 3)

**Code reviewed:** `include/Group-7-project-ridge-lib/MinMaxScaler.hpp`, `src/MinMaxScaler.cpp`.

- **Encapsulation:** Implemented. `min_value_`, `max_value_`, and `fitted_` are private. Public `fit`, `transform`, and `fit_transform` methods control access to this state.
- **Polymorphism:** None; no virtual methods or overloaded methods are defined.
- **Inheritance:** None; there is no base/derived relationship or `protected` member.
- **Layout to draw:** `MinMaxScaler` with those three private data members and the three public scaling methods. No protected members.

.
