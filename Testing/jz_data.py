import random
import sys
import csv
from os.path import basename, splitext
from os import system

def take_name(elem):
    """Take the name column from a .csv file as a key."""
    return elem[1]

def filename(file):
    """Return the filename (i.e. directory with no extentions or path) of
    a given file."""
    return splitext(basename(file))[0]

def write_csv(outfile_name, list):
    """Write a list ([[row1], [row2], ...]) to a given file name."""
    outfile = open(outfile_name, 'w')
    writer = csv.writer(outfile)
    writer.writerows(list)
    outfile.close()
    return

def size_dataset(input_file, size):
    """ Output a csv containing 'size' randomised entries, ordered entries
    and return a list of keys for testing."""

    # Read in csv data and store as list, which can be randomised with .shuffle
    csv_file = open(input_file, "r")
    csv_data = csv.reader(csv_file, delimiter =',')
    csv_list = [row for row in csv_data]
    csv_file.close()

    # Create a randomised subset of the list, containing 'size' rows
    random.shuffle(csv_list)
    new_list = csv_list[:size]
    # Write to csv
    outfile_name = "Data/{}_rando_{}.csv".format(
        filename(input_file), size)
    write_csv(outfile_name, new_list)

    # Create a test file containing 5 randomised keys
    random.shuffle(new_list)
    keys = [[r[1]] for r in new_list[:5]]
    outfile_name = "Data/{}_key{}_{}.csv".format(
        filename(input_file), 1, size)
    write_csv(outfile_name, keys)

    # Write ordered data subset to output
    new_list = sorted(new_list, key=take_name)
    outfile_name = "Data/{}_order_{}.csv".format(
        filename(input_file), size)
    write_csv(outfile_name, new_list)

    return

def make_datasets(input_file, sizes):
    """Create a collection of test data files of given sample sizes."""
    for sample_size in sizes:
        size_dataset(input_file, sample_size)
    return

def total_key_comparisons(input_file):
    """Return the total number of key comparisons from a dict stdout."""
    key_file = open(input_file, "r")
    key_data = csv.reader(key_file, delimiter = ' ')
    comparisons = sum([int(r[-1]) for r in key_data])
    key_file.close()
    return comparisons

def test_dataset(dataset, sizes):
    """For a dataset, run:
        - Each of its subset sample sizes through
        - Each of the programs dict1, dict2 for
        - Each of the types randomised, ordered
        and output a table summarising the average key comparisons for each
       I.e. output a table with columns containing:
        sample_size, dict1 rand, dict2 rand, dict1 ordered, dict2 ordered"""

    table = [["size", "dict1 rand", "dict2 rand", "dict1 order", "dict2 order"]]

    for sample_size in sizes:
        row = [sample_size]
        for type in ["rando", "order"]:
            dict1_comps, dict2_comps = 0, 0
            for k in range(1,2):
                # Print test being done
                print("###TESTING: Size = {} || Key list = {} || Type = {} ".format(sample_size, k, type))

                # Get names of files to test
                key_file = "Data/{}_key{}_{}.csv".format(filename(dataset), k, sample_size)
                input_file = "Data/{}_{}_{}.csv".format(filename(dataset), type, sample_size)

                # Run dict1 and dict2 tests
                command = "{} {} output.txt < {} > dict1_comp.txt".format("./dict1", input_file, key_file)
                system(command)
                command = "{} {} output.txt < {} > dict2_comp.txt".format("./dict2", input_file, key_file)
                system(command)

                # Collect output in current_output.txt
                dict1_comps += total_key_comparisons("dict1_comp.txt")
                dict2_comps += total_key_comparisons("dict2_comp.txt")

            # Add average key comps for type to row
            row = row + [dict1_comps/5, dict2_comps/5]
        # Append row to table
        table = table + [row]
        print(table[0])
        print(table[-1])
    return table

# Read in large data file for testing from argv[1]
input_file = sys.argv[1]
# Create data subsets of given (hardcoded) sizes - change as you wish
# Make sure the max subset size does not exceed the total number of data entries
sizes = range(10000, 250001, 20000)
make_datasets(input_file, sizes)

# Test data sets
table = test_dataset(input_file, sizes)
print(table)

# Summarise average key comparisons for:
# each sample size, each program, each ordered and randomised data
output_file = filename(input_file) + "_summary.csv"
write_csv(output_file, table)
