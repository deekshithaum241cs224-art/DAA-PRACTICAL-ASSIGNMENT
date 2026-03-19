# CS253 Practical Assignment - Sorting Algorithms
NITK Surathkal

## Files in this repo
- sorting.c - main code with all sorting algorithms
- graphs.py - generates graphs from the output
- sample_input.txt - example input file
- results.csv - timing and comparison data (generated after running)

## Algorithms
1. Selection Sort
2. Bubble Sort
3. Insertion Sort
4. Merge Sort
5. Quick Sort - first element as pivot
6. Quick Sort - random element as pivot
7. Quick Sort - median of three as pivot
8. Heap Sort
9. Radix Sort

## How to compile

```
gcc -o sorting sorting.c -lm
```

## How to run

```
./sorting > results.csv
```

when it asks, enter 1 to run all experiments
it will take around 2-3 mins, you can see the progress in terminal

## How to generate graphs

first install the required libraries (only once):
```
pip install matplotlib pandas
```

then run:
```
python graphs.py
```

graphs will be saved as png files in the same folder

## To sort from a file

run the program and enter 2 when asked, then give the filename

file should be in this format:
```
5
23
11
45
2
67
```
first line is number of elements, rest are the elements

## Note
- each experiment is run and average is taken to reduce timing errors
- quicksort with first element pivot is skipped for large sorted/reverse inputs to avoid stack overflow, this is expected
