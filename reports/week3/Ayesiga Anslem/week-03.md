# Week 3 Individual Report

**Name:** Ayesiga Anslem   25/U/0824
**Assigned module:** Matrix and vector operations  
**Reporting period:** 13-19 October 2026 (status as of 17 October)

> Drafted from the agreed Week 1 responsibilities and the Git history available in the project. A missing commit is not proof that no work was done. The member should add evidence for offline or unmerged work and verify all details before submission.

## Completed

- The repository records integration of the data-preprocessing branch into main on 14 October (merge of PR #12). This is a group integration activity, not evidence that the assigned Matrix implementation was complete. A 13 October commit changed a file named matrix.hhp (a header-extension typo), but no Matrix implementation/test update was recorded under the normal .hpp/.cpp/test paths in this window.

## In Progress

- The Matrix API still needed a canonical include path, method definitions, and retained tests at the start of this follow-up.

## Challenges

- Data loading, regression, and solver modules depend on a stable Matrix implementation.

## Next Week - files to merge

- Add focused Matrix tests for construction, bounds checking, arithmetic, transpose, vector multiplication, and dot product; then review the Codex-assisted Matrix files before merge. No tests were run during this follow-up.

## Week 3 shared code status 

The current checkout now has the canonical `include/Group-7-project-ridge-lib/matrix.hpp`, `src/matrix.cpp`, and `examples/ridge_demo.cpp` for the Matrix module. These are group-level integration files prepared or corrected with Codex assistance. The available history does not establish these changes as Ayesiga's individual work; review them and add any personally completed work/evidence before submitting.

## OOP Concepts and Class Layout 

**Code reviewed:** `include/Group-7-project-ridge-lib/matrix.hpp`, `src/matrix.cpp`.

- **Encapsulation:** Implemented. `Matrix` keeps `rows_`, `cols_`, `values_`, and the bounds-checking `index()` helper private. Constructors and matrix operations are public.
- **Polymorphism:** The matrix operators (`+`, `-`, `*`) are overloaded for matrix and scalar operands. This is compile-time operator overloading, not virtual runtime polymorphism.
- **Inheritance:** None in the current Matrix code; there is no base or derived class, and no `protected` member.

<img width="1080" height="1080" alt="WhatsApp Image 2026-10-19 at 5 28 47 PM" src="https://github.com/user-attachments/assets/c91e5802-83a2-47a7-9adb-7a75daf14578" />


