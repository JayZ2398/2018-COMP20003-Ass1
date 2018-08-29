import random
import sys
import csv
from os.path import basename, splitext
from os import system

def take_name(elem):
    return elem[1]

def filename(file):
    return splitext(basename(file))[0]

def write_csv(outfile_name, list):
    outfile = open(outfile_name, 'w')
    writer = csv.writer(outfile)
    writer.writerows(list)
    outfile.close()
    return

def size_dataset(input_file, size):
    """ Output a csv containing 'size' randomised entries, ordered entries
    and return a list of 5 keys for testing."""

    # Read in csv data and store as list, which can be randomised with .shuffle
    csv_file = open(input_file, "r")
    csv_data = csv.reader(csv_file, delimiter =',')
    csv_list = [row for row in csv_data]
    csv_file.close()

    # Create a randomised subset of the list, containing 'size' rows
    random.shuffle(csv_list)
    new_list = csv_list[:size]
    # Write to csv
    outfile_name = "Data/{}_order_{}.csv".format(
        filename(input_file), size)
    write_csv(outfile_name, new_list)

    # Create 5 test files each containing 5 randomised keys
    for i in range(1,6):
        random.shuffle(new_list)
        keys = [[r[1]] for r in new_list[:5]]
        outfile_name = "Data/{}_key{}_{}.csv".format(
            filename(input_file), i, size)
        write_csv(outfile_name, keys)

    # Write ordered data subset to output
    new_list = sorted(new_list, key=take_name)
    outfile_name = "Data/{}_rando_{}.csv".format(
        filename(input_file), size)
    write_csv(outfile_name, new_list)

    return

def make_datasets(input_file):
    """Create a collection of test data of different sample sizes.
    Small sizes are of 10,000 increments up to 50,000
    Large sizes are of 50,000 increments up to 250,000."""
    # Create small datasets
    for sample_size in range(10000, 50000, 10000):
        size_dataset(input_file, sample_size)
    # Create large datsets
    for sample_size in range(50000, 250001, 50000):
        size_dataset(input_file, sample_size)
    return

def total_key_comparisons(input_file):
    """Return the total number of key comparisons from a dict stdout."""
    key_file = open(input_file, "r")
    key_data = csv.reader(key_file, delimiter = ' ')
    comparisons = sum([int(r[-1]) for r in key_data])
    key_file.close()
    return comparisons

def overall_program():
    """Not sure yet."""

    # For each sample size:
        # For each dict1 and dict2
            # For the ordered and random sets:
                # Run the ordered sample through the program
                # Use the 5 key tests, collect all the total comparisons
                # Find average comparisons for ordered file (total comp/25)
        # Store the sample-specific average comparisons for both dict1 and dict2, random and ordered
    return

def test_dataset(dataset):
    """For a dataset, run:
        - Each of its subset sample sizes through
        - Each of the programs dict1, dict2 for
        - Each of the types randomised, ordered
        and output a table summarising the average key comparisons for each
       I.e. output a table with columns containing:
        sample_size, dict1 rand, dict2 rand, dict1 ordered, dict2 ordered"""

    # Table = size, dict1 rand, dict2 rand, dict1 order, dict2 order
    #for size in [range(10000, 50000, 10000), range(50000, 250000, 50000)]

    sizes = list(range(10000, 50000, 10000)) + list(range(50000,250001,50000))
    table = []

    for sample_size in sizes:
        row = [sample_size]
        dict1_comps, dict2_comps = 0, 0
        for type in ["rando", "order"]:
            for k in range(1,6):
                # Print test being done
                print("###TESTING: Size = {} || Key list = {} || Type = {} ".format(sample_size, k, type))

                # Get names of files to test
                key_file = "Data/{}_key{}_{}.csv".format(filename(dataset), k, sample_size)
                input_file = "Data/{}_{}_{}.csv".format(filename(dataset), type, sample_size)

                # Run program
                command = "{} {} output.txt < {} > dict1_comp.txt".format("dict1", input_file, key_file)
                #print("###RUN: " + command)
                system(command)
                command = "{} {} output.txt < {} > dict2_comp.txt".format("dict2", input_file, key_file)
                #print("###RUN: " + command)
                system(command)

                # Collect output in current_output.txt
                dict1_comps += total_key_comparisons("dict1_comp.txt")
                dict2_comps += total_key_comparisons("dict2_comp.txt")
                #print("Comparisons = {}".format(total_key_comparisons("comparisons.txt")))
            # Add average key comps for type to row
            row = [row, dict1_comps/5, dict1_comps/5]
        # Append row to table
        table = [table, row]
    return table

input_file = sys.argv[1]
#make_datasets(input_file)
table = test_dataset("athlete_events_filtered.csv")
print(table)

"""
for size in range(start, stop + 1, step):
    for exp in range(0, num_experiments):
        data = size_dataset(csvdata, size)
        # run ordered tests
        # run random tests
        # add average comparisons in each
        # sort out keys somewhere
"""
