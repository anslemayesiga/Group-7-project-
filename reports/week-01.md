
Week 1 Individual Progress Report

Member Name: Wobusobozi Chrispus Owen
Registration Number: 25/U/0860 BELE
Assigned Feature Group: Dataset Loading & Data Preprocessing
Reporting Period: 28th September to 5th October 2026

 1. Core Engineering Status

• Status: COMPLETED 
• Assigned Modules Initialized:
• Assigned Modules Initialized:
	• include/ridgelib/dataset.hpp
	• include/ridgelib/preprocessing.hpp

 2. Work Completed This Week


System Environment Configuration
• Successfully established a local Git connection inside VS Code to interface with the shared remote group repository (https://github.com).
• Verified multi-directional repository commands (git clone, commit, push, pull) locally to ensure zero pipeline disruptions during future feature merges.

Architectural API Blueprinting

• Collaborated with the group to finalize the global project layout contract, explicitly defining file mapping targets across the include/, src/, and tests/ directories.
• Outlined the initial public class interfaces for my assigned modules inside the public header space:
	• Designed the structural layout for class Dataset to map core features matrix arrays (X) away from target labels (y).
	• Declared baseline data cleaning structures inside class Preprocessing to establish clear function dependencies before writing source implementations.

Dataset Pre-Analysis

• Researched standard file streaming (std::ifstream), raw string manipulation pipelines, and file stream tokenizers.
• Analyzed requirements for processing comma-separated value sequences (CSV) containing varied real-world numeric records.

 3. Challenges Addressed & Resolved

• Challenge: Designing an independent dataset container that could map out internal features smoothly while the core math engine (matrix.hpp) was still being written by other team members.
• Resolution: Agreed on a shared data-contract matrix signature using raw primitive vectors (std::vector<std::vector<double>>) as a temporary interface. This allowed me to continue drafting my loading loops without waiting for external structural mathematical• classes to compile.

 4. Objectives For Next Week (Week 2)

• Write the fully functional loop parsing algorithm inside src/dataset.cpp to read text assets line by line.
• Code the double-pass column imputation methods inside src/preprocessing.cpp to identify corrupted placeholders and overwrite anomalies with calculated column mean • averages.
• Construct an independent automated unit test suite inside tests/test_dataset.cpp to run verification checks on data parsing tasks.

 5. AI Use Declaration

• Tool: Claude
• Purpose: Analyzed the global grading rubric requirements, assisted in summarizing standard Ridge Regression workflow structures, and suggested directory skeleton architectures.
• Reason: Allowed the entire 10-member group to agree on structural class parameters and function names simultaneously on day one, reducing overlapping file dependency conflicts. 
