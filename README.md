# COMP20003-Ass1
Project implements a dictionary with binary search trees (with both standard and linked-list versions), then generates and runs tests on the search operation to determine the complexity of BSTs.

A **summary report** of the findings on BST complexity is available in the root directory.

## Purpose
The purpose of this project is to test the speed complexity of data depending on:
1. Dataset size
2. Ordering (i.e. random vs. sorted)

Testing of these factors is automated by using a script (written in `python`) to create subsets of a large dataset and then run the binary search program (written in `C`).

## Dataset
- By default, this project is configured to use an Olympian event dataset with ~250k entries. Each entry uses the athlete's name as a key and stores information (date, medal, etc.) for a specific event (i.e. 'Men's 100m Sprint').
- Duplicates exist (i.e. multiple events for the same athlete name).

## Custom Testing
To run your own data tests:
1. `cd` to `/Testing/`. 
2. Open `jz_data.py`, and change the sizes array to include the sample sizes you would like to test.
3. Run `python jz_data.py <input_file.csv>`, where input_file is an original dataset .csv (i.e. 'athlete_events_filtered.csv').
