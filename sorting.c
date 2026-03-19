/*  CS253: Design and Analysis of Algorithms
  Practical Assignment - All Sorting Algorithms
 
  HOW TO COMPILE: gcc -o sorting sorting.c -lm
  HOW TO RUN: ./sorting > results.csv

  Then run the Python script to generate graphs:   python3 graphs.py  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global comparison counter — reset before every sort 
long long comparisons = 0;

void swap(int *a, int *b) {
    int tmp = *a; *a = *b; *b = tmp;
}

//1.SELECTION SORT ->  Always O(n^2). Find min in unsorted part, swap to front.

void selection_sort(int *arr, int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        swap(&arr[min_idx], &arr[i]);
    }
}


   //2. BUBBLE SORT -> O(n) best, O(n^2) worst. Swap adjacent pairs until no swaps needed.
void bubble_sort(int *arr, int n) {
    int i, j, swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

   //3. INSERTION SORT  ->  O(n) best, O(n^2) worst. Pick element, slide left to correct position.

void insertion_sort(int *arr, int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j   = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) { arr[j+1] = arr[j]; j--; }
            else break;
        }
        arr[j+1] = key;
    }
}


   //4. MERGE SORT  ->  Always O(n log n).Split in half, sort each, merge back.
  
void merge(int *arr, int l, int m, int r) {
    int n1 = m-l+1, n2 = r-m, i, j, k;
    int *L = (int*)malloc(n1*sizeof(int));
    int *R = (int*)malloc(n2*sizeof(int));
    for (i=0;i<n1;i++) L[i]=arr[l+i];
    for (j=0;j<n2;j++) R[j]=arr[m+1+j];
    i=0; j=0; k=l;
    while (i<n1 && j<n2) {
        comparisons++;
        arr[k++] = (L[i]<=R[j]) ? L[i++] : R[j++];
    }
    while (i<n1) arr[k++]=L[i++];
    while (j<n2) arr[k++]=R[j++];
    free(L); free(R);
}
void merge_rec(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r-l)/2;
        merge_rec(arr, l, m);
        merge_rec(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
void merge_sort(int *arr, int n) { merge_rec(arr, 0, n-1); }

// Shared partition for all QuickSort versions 
int partition(int *arr, int lo, int hi) {
    int pivot = arr[hi], i = lo-1, j;
    for (j=lo; j<hi; j++) {
        comparisons++;
        if (arr[j] <= pivot) { i++; swap(&arr[i],&arr[j]); }
    }
    swap(&arr[i+1], &arr[hi]);
    return i+1;
}

// 5. QUICKSORT V1  ->  Pivot = first element. O(n^2) on sorted/reverse input!
  
void qs1(int *arr, int lo, int hi) {
    if (lo < hi) {
        swap(&arr[lo], &arr[hi]);
        int p = partition(arr, lo, hi);
        qs1(arr, lo, p-1); qs1(arr, p+1, hi);
    }
}
void quicksort_v1(int *arr, int n) { qs1(arr, 0, n-1); }

// 6. QUICKSORT V2  ->  Pivot = random element .No input reliably causes worst case.
  
void qs2(int *arr, int lo, int hi) {
    if (lo < hi) {
        int r = lo + rand()%(hi-lo+1);
        swap(&arr[r], &arr[hi]);
        int p = partition(arr, lo, hi);
        qs2(arr, lo, p-1); qs2(arr, p+1, hi);
    }
}
void quicksort_v2(int *arr, int n) { qs2(arr, 0, n-1); }

//7. QUICKSORT V3  ->  Pivot = median of 3. Best version: handles sorted/reverse well.
  
int med3(int *arr, int lo, int hi) {
    int mid = lo+(hi-lo)/2;
    if (arr[lo]>arr[mid])  swap(&arr[lo], &arr[mid]);
    if (arr[lo]>arr[hi])   swap(&arr[lo], &arr[hi]);
    if (arr[mid]>arr[hi])  swap(&arr[mid],&arr[hi]);
    return mid;
}
void qs3(int *arr, int lo, int hi) {
    if (lo < hi) {
        int m = med3(arr, lo, hi);
        swap(&arr[m], &arr[hi]);
        int p = partition(arr, lo, hi);
        qs3(arr, lo, p-1); qs3(arr, p+1, hi);
    }
}
void quicksort_v3(int *arr, int n) { qs3(arr, 0, n-1); }

// 8. HEAP SORT  ->  Always O(n log n), in-place. Build max-heap, repeatedly extract max
void heapify(int *arr, int n, int i) {
    int lg=i, l=2*i+1, r=2*i+2;
    comparisons++; if (l<n && arr[l]>arr[lg]) lg=l;
    comparisons++; if (r<n && arr[r]>arr[lg]) lg=r;
    if (lg!=i) { swap(&arr[i],&arr[lg]); heapify(arr,n,lg); }
}
void heap_sort(int *arr, int n) {
    int i;
    for (i=n/2-1; i>=0; i--) heapify(arr,n,i);
    for (i=n-1;   i>0;  i--) { swap(&arr[0],&arr[i]); heapify(arr,i,0); }
}

// 9. RADIX SORT  -> O(n*k), not comparison-based. Sort digit by digit using counting sort.
  
void count_digit(int *arr, int n, int exp) {
    int *out=(int*)malloc(n*sizeof(int)), cnt[10]={0}, i;
    for (i=0;i<n;i++) cnt[(arr[i]/exp)%10]++;
    for (i=1;i<10;i++) cnt[i]+=cnt[i-1];
    for (i=n-1;i>=0;i--) { int d=(arr[i]/exp)%10; out[--cnt[d]]=arr[i]; }
    for (i=0;i<n;i++) arr[i]=out[i];
    free(out);
}
void radix_sort(int *arr, int n) {
    int i, mx=arr[0];
    for (i=1;i<n;i++) if(arr[i]>mx) mx=arr[i];
    int exp; for(exp=1; mx/exp>0; exp*=10) count_digit(arr,n,exp);
}

 //  INPUT GENERATORS

void gen_random (int *a, int n) { int i; for(i=0;i<n;i++) a[i]=rand()%100000; }
void gen_sorted (int *a, int n) { int i; for(i=0;i<n;i++) a[i]=i; }
void gen_reverse(int *a, int n) { int i; for(i=0;i<n;i++) a[i]=n-i; }


   //RUN ONE SORT: copies array first, returns microseconds, sets *cmp
   
double run_once(void(*fn)(int*,int), int *orig, int n, long long *cmp) {
    int *arr = (int*)malloc(n*sizeof(int));
    memcpy(arr, orig, n*sizeof(int));
    comparisons = 0;
    clock_t s = clock();
    fn(arr, n);
    clock_t e = clock();
    *cmp = comparisons;
    free(arr);
    return (double)(e-s)/CLOCKS_PER_SEC*1e6;
}

// Run 5 times, return average time + average comparisons 
double avg_run(void(*fn)(int*,int), int *orig, int n, long long *cmp) {
    double tsum=0; long long csum=0, c; int r;
    for(r=0;r<5;r++) { tsum+=run_once(fn,orig,n,&c); csum+=c; }
    *cmp = csum/5;
    return tsum/5.0;
}

/* READ ARRAY FROM FILE
   File format:
     n
     element1
     element2  ...  */
int* read_file(const char *filename, int *n_out) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Error: could not open file '%s'\n", filename);
        return NULL;
    }
    int n;
    fscanf(f, "%d", &n);
    int *arr = (int*)malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++)
        fscanf(f, "%d", &arr[i]);
    fclose(f);
    *n_out = n;
    return arr;
}

void run_on_file(const char *filename) {
    int n;
    int *arr = read_file(filename, &n);
    if (!arr) return;

    char *names[] = {
        "Selection","Bubble","Insertion",
        "MergeSort","QuickV1","QuickV2","QuickV3",
        "HeapSort","RadixSort"
    };
    void (*fns[])(int*,int) = {
        selection_sort, bubble_sort, insertion_sort,
        merge_sort, quicksort_v1, quicksort_v2, quicksort_v3,
        heap_sort, radix_sort
    };
    int na = 9, ai;

    printf("\nFile: %s  |  n = %d\n", filename, n);
    printf("%-12s  %12s  %15s\n", "Algorithm", "Time (us)", "Comparisons");
    printf("-----------------------------------------------\n");
    for (ai = 0; ai < na; ai++) {
        long long cmp;
        double t = avg_run(fns[ai], arr, n, &cmp);
        printf("%-12s  %12.2f  %15lld\n", names[ai], t, cmp);
    }
    free(arr);
}

// MAIN
  
int main(int argc, char *argv[]) {
    if (argc == 2) {
        run_on_file(argv[1]);
        return 0;
    }
    int sizes[] = {100,500,1000,2000,5000,10000,50000,100000};
    int ns = 8;

    char *names[] = {
        "Selection","Bubble","Insertion",
        "MergeSort","QuickV1","QuickV2","QuickV3",
        "HeapSort","RadixSort"
    };
    void (*fns[])(int*,int) = {
        selection_sort, bubble_sort, insertion_sort,
        merge_sort, quicksort_v1, quicksort_v2, quicksort_v3,
        heap_sort, radix_sort
    };
    int na = 9;

    char *itypes[] = {"Random","Sorted","Reverse"};
    void (*gens[])(int*,int) = {gen_random, gen_sorted, gen_reverse};

    srand(42);

    // CSV header 
    printf("Algorithm,InputType,n,Time_us,Comparisons\n");

    int si, ti, ai;
    for (si=0; si<ns; si++) {
        int n = sizes[si];
        int *arr = (int*)malloc(n*sizeof(int));

        for (ti=0; ti<3; ti++) {
            gens[ti](arr, n);

            for (ai=0; ai<na; ai++) {
                /* QuickV1 on large sorted/reverse = stack overflow, skip */
                if (ai==4 && (ti==1||ti==2) && n>10000) {
                    printf("%s,%s,%d,SKIP,SKIP\n", names[ai], itypes[ti], n);
                    continue;
                }
                long long cmp;
                double t = avg_run(fns[ai], arr, n, &cmp);
                printf("%s,%s,%d,%.2f,%lld\n", names[ai], itypes[ti], n, t, cmp);
            }
        }

        free(arr);
        fprintf(stderr, "Done n=%d\n", n);
    }
    return 0;
}
