# Week 3 Individual Progress Report

**Name:** Ainemugabe Crisbert  
**Assigned module:** Hyperparameter tuning  
**Reporting period:** 13-19 October 2026 (status as of 17 October)

> Drafted from the agreed Week 1 responsibilities and the Git history available in the project. A missing commit is not proof that no work was done. The member should add evidence for offline or unmerged work and verify all details before submission.

## Completed / repository evidence

- The Week 3 history contains updates to the Week 2 report on 13 October. No tuning HPP/CPP/test commit is present.

## In Progress

- The Week 2 note describes grid-search activity, but the tuning controller and tests are not in the repository. Treat the activity as member-reported until the files or branch are linked.

## Challenges/Blockers

- Tuning depends on a working ridge estimator and evaluation metric API.

## Next Week - files to merge

- Add tests for candidate selection, empty candidates, null model factories, and validation shapes; confirm that validation R-squared is the agreed selection metric. Review the Codex-assisted tuner. No tests were run during this follow-up.

## AI Use

- **OpenAI Codex (17 October):** drafted this report from repository evidence and repaired integration in the shared checkout across Matrix, CSV loading, feature scaling, normal-equation solving, ridge cost, CMake, and a demo. This is group-level AI-assisted work, not an individual contribution by Ainemugabe Crisbert. The team must review and understand these changes before accepting them.
- Add any other AI tools this member used for their own module work; do not mark none without checking.

## Week 3 shared code status (Codex-assisted)

The current checkout now contains `include/Group-7-project-ridge-lib/tuning.hpp` and `src/tuning.cpp`, prepared as a group-level grid-search draft with Codex assistance. The available history does not establish this as Ainemugabe's individual work. Review and adapt the candidate parameter/model interface and add personal work/evidence before submitting.

## OOP Concepts and Class Layout (Week 3)

**Code files prepared for the assigned module:** `include/Group-7-project-ridge-lib/tuning.hpp`, `src/tuning.cpp`.

- **Encapsulation:** `GridSearchTuner` stores its model factory privately and exposes a public search method. `GridSearchResult` returns the best parameter, score, and model using public fields.
- **Runtime polymorphism:** The tuner creates and uses models through `std::unique_ptr<Regressor>`, calling virtual `fit` and `predict`. It has no inheritance relationship itself.
- **Layout to draw:** `GridSearchTuner` private `factory_`; public `ModelFactory`, constructor, and `fit`. `GridSearchResult` public `best_parameter`, `best_score`, and `best_model`. The model base is `Regressor`.

These files were prepared with OpenAI Codex assistance for the group. Review and understand them before claiming individual authorship. Draw the actual class layout by hand and add a clear photo. See [shared class-layout guide](../class-layouts.md#ainemugabe-crisbert-hyperparameter-tuning).
