# Week 3 Individual Progress Report

**Name:** Wobusobozi Chrispus Owen  
**Assigned module:** Dataset loading and data preprocessing  
**Reporting period:** 13-19 October 2026 (status as of 17 October)

> Drafted from the agreed Week 1 responsibilities and the Git history available in the project. A missing commit is not proof that no work was done. The member should add evidence for offline or unmerged work and verify all details before submission.

## Completed / repository evidence

- The Week 2 loader HPP/CPP/test were already committed on 12 October. The Week 3 history shows report updates on 13 and 15 October, but no Week 3 data-loader or preprocessing source/test change.

## In Progress

- The Week 2 report claimed preprocessing and verified randomized splitting, but no preprocessing module exists in the repository and the committed split is contiguous. Add links to any work not represented in Git.

## Challenges/Blockers

- The data loader needed a public result and validation; preprocessing HPP/CPP/tests remain absent.

## Next Week - files to merge

- Review the current CSV loader and its passing test, then implement the agreed preprocessing component and add focused tests. No preprocessing module exists yet, and no preprocessing tests have been run.

## AI Use

- **OpenAI Codex (17 October):** drafted this report from repository evidence and repaired integration in the shared checkout across Matrix, CSV loading, feature scaling, normal-equation solving, ridge cost, CMake, and a demo. This is group-level AI-assisted work, not an individual contribution by Wobusobozi Chrispus Owen. The team must review and understand these changes before accepting them.
- Add any other AI tools this member used for their own module work; do not mark none without checking.

## Week 3 shared code status (Codex-assisted)

The current checkout has `include/Group-7-project-ridge-lib/data_loader.hpp`, `src/data_loader.cpp`, and `tests/test_data_loader.cpp`. The loader API and validation were adjusted with Codex assistance as group-level integration; this is not proof of individual authorship. The existing DataLoader check was compiled and passed. Review the changes and add any personal/offline work and evidence before submitting.

## OOP Concepts and Class Layout (Week 3)

**Code reviewed:** `include/Group-7-project-ridge-lib/data_loader.hpp`, `src/data_loader.cpp`.

- **Encapsulation:** `DataLoader` groups CSV loading and splitting operations. Its `Dataset` and `SplitResult` nested structs expose their data publicly; the loader itself has no private state members, so data hiding is limited.
- **Polymorphism:** None. The two `trainTestSplit` overloads are compile-time overloads for different input types, not virtual runtime polymorphism.
- **Inheritance:** None; there is no base/derived relationship or `protected` member.
- **Layout to draw:** `DataLoader` has public nested `Dataset` (`features`, `targets`, `feature_names`) and `SplitResult` (`X_train_raw`, `X_test_raw`, `y_train`, `y_test`), plus public `loadCSV` and two `trainTestSplit` overloads. No private/protected members.

Draw this actual class layout by hand and add a clear photo to this report before submission. See [shared class-layout guide](../class-layouts.md#wobusobozi-chrispus-owen-data-loader).
