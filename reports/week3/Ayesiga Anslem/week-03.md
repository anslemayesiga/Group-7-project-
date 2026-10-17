# Week 3 Individual Progress Report

**Name:** Ayesiga Anslem  
**Assigned module:** Matrix and vector operations  
**Reporting period:** 13-19 October 2026 (status as of 17 October)

> Drafted from the agreed Week 1 responsibilities and the Git history available in the project. A missing commit is not proof that no work was done. The member should add evidence for offline or unmerged work and verify all details before submission.

## Completed / repository evidence

- The repository records integration of the data-preprocessing branch into main on 14 October (merge of PR #12). This is a group integration activity, not evidence that the assigned Matrix implementation was complete. A 13 October commit changed a file named matrix.hhp (a header-extension typo), but no Matrix implementation/test update was recorded under the normal .hpp/.cpp/test paths in this window.

## In Progress

- The Matrix API still needed a canonical include path, method definitions, and retained tests at the start of this follow-up.

## Challenges/Blockers

- Data loading, regression, and solver modules depend on a stable Matrix implementation.

## Next Week - files to merge

- Add focused Matrix tests for construction, bounds checking, arithmetic, transpose, vector multiplication, and dot product; then review the Codex-assisted Matrix files before merge. No tests were run during this follow-up.

## AI Use

- **OpenAI Codex (17 October):** drafted this report from repository evidence and repaired integration in the shared checkout across Matrix, CSV loading, feature scaling, normal-equation solving, ridge cost, CMake, and a demo. This is group-level AI-assisted work, not an individual contribution by Ayesiga Anslem. The team must review and understand these changes before accepting them.
- Add any other AI tools this member used for their own module work; do not mark none without checking.

## Week 3 shared code status (Codex-assisted)

The current checkout now has the canonical `include/Group-7-project-ridge-lib/matrix.hpp`, `src/matrix.cpp`, and `examples/ridge_demo.cpp` for the Matrix module. These are group-level integration files prepared or corrected with Codex assistance. The available history does not establish these changes as Ayesiga's individual work; review them and add any personally completed work/evidence before submitting.

## OOP Concepts and Class Layout (Week 3)

**Code reviewed:** `include/Group-7-project-ridge-lib/matrix.hpp`, `src/matrix.cpp`.

- **Encapsulation:** Implemented. `Matrix` keeps `rows_`, `cols_`, `values_`, and the bounds-checking `index()` helper private. Constructors and matrix operations are public.
- **Polymorphism:** The matrix operators (`+`, `-`, `*`) are overloaded for matrix and scalar operands. This is compile-time operator overloading, not virtual runtime polymorphism.
- **Inheritance:** None in the current Matrix code; there is no base or derived class, and no `protected` member.
- **Layout to draw:** `Matrix` with private fields `rows_: size_t`, `cols_: size_t`, `values_: vector<double>`, `index(row,col): size_t`; public constructors, `identity`, `rows`, `cols`, `operator()`, `transpose`, arithmetic operators, `multiply`, `column`, and `row`. Free functions: scalar-left multiply and `dot`.

Draw this actual class layout by hand and add a clear photo to this report before submission. See [shared class-layout guide](../class-layouts.md#ayesiga-anslem-matrix).


