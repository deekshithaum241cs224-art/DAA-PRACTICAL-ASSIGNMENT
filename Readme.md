# CS253 -DAA Practical Assignment


## Files
- sorting.c - all the sorting algorithms
- graphs.py - for generating graphs using matplotlib
- sample_input.txt - sample input file

## How to compile and run

first compile the c file:

gcc -o sorting sorting.c -lm


then run it:

./sorting > results.csv

it will ask you to pick 1 or 2
- pick 1 for running all experiments (this generates the csv file for graphs)
- pick 2 if you want to sort from a file

it takes like 2-3 mins to finish, you'll see "Done n=..." in terminal

## For graphs

install matplotlib first if you dont have it:

pip install matplotlib pandas


then run:

python3 graphs.py


make sure results.csv is in the same folder before running this

graphs will be saved as png files (fig1, fig2... etc)

## Input file format

if you want to sort from a file, format should be like this:

5
64
25
12
22
11

first line is n (number of elements), then each element on a new line

sample_input.txt is already there as an example

## Algorithms implemented
1. Selection Sort
2. Bubble Sort
3. Insertion Sort
4. Merge Sort
5. Quick Sort - first element pivot
6. Quick Sort - random pivot
7. Quick Sort - median of three pivot
8. Heap Sort
9. Radix Sort

## Note
quicksort v1 will be skipped for large inputs on sorted/reverse arrays because it causes stack overflow, thats normal
