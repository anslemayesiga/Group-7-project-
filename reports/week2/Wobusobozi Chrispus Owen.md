# Week 2 Individual Progress Report

**Name:** Wobusobozi Chrispus Owen  
**Assigned module:** Dataset loading and data preprocessing  
**Reporting period:** 6-12 October 2026  
**Evidence basis:** available Git history and existing member notes through 17 October.

> Draft prepared from the available records. No commit in Git does not prove no offline work occurred. The named member should verify the record and add or correct any work done outside the repository before submission.

## Completed / repository evidence

- Commit ad25b66 on 12 October adds include/ridge_ml/data_loader.hpp, src/data_loader.cpp, and tests/test_data_loader.cpp, and updates CMakeLists.txt. The test covers train/test split sizes and order. No preprocessing.hpp, preprocessing.cpp, or preprocessing test is present in the Week 2 tree.

## In Progress

- CSV loading and a basic contiguous split were submitted. In the Week 2 version, loadCSV returned void and stored rows privately, so a library caller could not retrieve the loaded data. The split also lacked input validation.

## Challenges/Blockers

- Preprocessing was assigned but is not represented by module files in the repository. The public data-loading result also needed to be exposed.

## Next Week - files to merge

- include/ridge_ml/data_loader.hpp, src/data_loader.cpp, tests/test_data_loader.cpp; add include/ridge_ml/preprocessing.hpp, src/preprocessing.cpp, tests/test_preprocessing.cpp. In this follow-up, the loader API has been repaired; that repair is not the member's historical Week 2 contribution.

