#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define MAX 100000

// global comparison counter
long long comparisons = 0;

void generateRandom(int arr[],int n){
    for(int i=0;i<n;i++)
        arr[i]= rand() %10000;
}

void generateSorted(int arr[],int n){
    for(int i=0;i<n;i++)
        arr[i]=i;
}

void generateReverse(int arr[],int n){
    for(int i=0;i<n;i++)
        arr[i]=n-i;
}

void copyArray(int original[],int copyarr[],int n){
    for(int i=0;i<n;i++)
        copyarr[i] =original[i];
}

void selectionSort(int arr[],int n){
    int i,j,min,temp;

    for(i=0;i<n-1;i++){
        min=i;
        for(j=i+1;j<n;j++){
            comparisons++;
            if(arr[j]<arr[min])
                min=j;
        }
        temp=arr[i];
        arr[i]=arr[min];
        arr[min]=temp;
    }
}

void bubbleSort(int arr[],int n){
    int i,j,temp;

    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            comparisons++;
            if(arr[j]>arr[j+1]){
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

void insertionSort(int arr[],int n){
    int i,key,j;

    for(i=1;i<n;i++){
        key = arr[i];
        j = i-1;

        while(j>=0){
            comparisons++;
            if(arr[j]>key){
                arr[j+1] =arr[j];
                j--;
            } else break;
        }
        arr[j+1]=key;
    }
}

void merge(int arr[],int l,int m,int r){
    int i=l,j=m+1,k=0;
    int temp[MAX];

    while(i<=m && j<=r){
        comparisons++;
        if(arr[i]<arr[j])
            temp[k++]=arr[i++];
        else
            temp[k++]=arr[j++];
    }

    while(i<=m)
        temp[k++]=arr[i++];

    while(j<=r)
        temp[k++]=arr[j++];

    for(i=l,k=0;i<=r;i++,k++)
        arr[i]=temp[k];
}

void mergeSort(int arr[],int l,int r){
    if(l<r){
        int m=(l+r)/2;

        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[],int low,int high){
    int pivot =arr[low];
    int i =low+1;
    int j =high;
    int temp;

    while(i<=j){
        while( i<=high && arr[i]<=pivot){
            comparisons++;
            i++;
        }
        while(j >= low && arr[j] > pivot){
            comparisons++;
            j--;
        }
        if(i<j){
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }
    swap(&arr[low], &arr[j]);

    return j;
}

void quickSort_first(int arr[],int low,int high){
    if(low < high){
        int p = partition(arr, low, high);
        quickSort_first(arr, low, p-1);
        quickSort_first(arr, p+1, high);
    }
}

int randomPartition(int arr[], int low, int high){
    int randIndex = low + rand() % (high - low + 1);
    swap(&arr[low], &arr[randIndex]);
    return partition(arr, low, high);
}

void quickSort_random(int arr[],int low,int high){
    if(low<high){
        int p=randomPartition(arr,low,high);
        quickSort_random(arr,low,p-1);
        quickSort_random(arr,p+1,high);
    }
}

int medianOfThree(int arr[], int low, int high){
    int mid = (low + high) / 2;

    if(arr[low] > arr[mid])
        swap(&arr[low], &arr[mid]);

    if(arr[low] > arr[high])
        swap(&arr[low], &arr[high]);

    if(arr[mid] > arr[high])
        swap(&arr[mid], &arr[high]);

    swap(&arr[low], &arr[mid]);
    return partition(arr, low, high);
}

void quickSort_median(int arr[],int low,int high){
    if(low < high){
        int p = medianOfThree(arr,low,high);
        quickSort_median(arr,low,p-1);
        quickSort_median(arr,p+1,high);
    }
}

void heapify(int arr[],int n,int i){
    int largest=i;
    int l=2*i+1;
    int r=2*i+2;
    int temp;

    comparisons++;
    if(l<n && arr[l]>arr[largest])
        largest=l;

    comparisons++;
    if(r<n && arr[r]>arr[largest])
        largest=r;

    if(largest!=i){
        temp=arr[i];
        arr[i]=arr[largest];
        arr[largest]=temp;

        heapify(arr,n,largest);
    }
}

void heapSort(int arr[], int n){
    int i,temp;
    
    for(i=n/2-1;i>=0;i--)
        heapify(arr,n,i);

    for(i=n-1;i>0;i--){
        temp=arr[0];
        arr[0]=arr[i];
        arr[i]=temp;

        heapify(arr,i,0);
    }
}

int getMax(int arr[],int n){
    int max=arr[0];
    for(int i=1;i<n;i++)
        if(arr[i]>max)
            max=arr[i];
    return max;
}

void countSort(int arr[],int n,int exp){
    int output[n];
    int count[10]={0};

    for(int i=0;i<n;i++)
        count[(arr[i]/exp)%10]++;

    for(int i=1;i<10;i++)
        count[i]+=count[i-1];

    for(int i=n-1;i>=0;i--){
        output[count[(arr[i]/exp)%10]-1]=arr[i];
        count[(arr[i]/exp)%10]--;
    }

    for(int i=0;i<n;i++)
        arr[i]=output[i];
}

void radixSort(int arr[],int n){
    int m=getMax(arr,n);

    for(int exp=1;m/exp>0;exp*=10)
        countSort(arr,n,exp);
}

// read array from file
// file format: first line is n, then one element per line
int readFromFile(char *filename, int arr[]){
    FILE *f = fopen(filename, "r");
    if(!f){
        printf("Error: cannot open file %s\n", filename);
        return -1;
    }
    int n;
    fscanf(f, "%d", &n);
    for(int i=0; i<n; i++)
        fscanf(f, "%d", &arr[i]);
    fclose(f);
    return n;
}

// run one sort, return time in microseconds
double runSort(void (*sortFn)(int*,int), int original[], int n, long long *cmp){
    int temp[MAX];
    copyArray(original, temp, n);
    comparisons = 0;
    clock_t start = clock();
    sortFn(temp, n);
    clock_t end = clock();
    *cmp = comparisons;
    return (double)(end-start)/CLOCKS_PER_SEC * 1000000.0;
}

// mergesort wrapper since it takes different args
void mergeSortWrapper(int arr[], int n){
    mergeSort(arr, 0, n-1);
}
void quickSortFirstWrapper(int arr[], int n){
    quickSort_first(arr, 0, n-1);
}
void quickSortRandomWrapper(int arr[], int n){
    quickSort_random(arr, 0, n-1);
}
void quickSortMedianWrapper(int arr[], int n){
    quickSort_median(arr, 0, n-1);
}

int main(){
    int original[MAX];
    int temp[MAX];

    srand(time(NULL));

    int choice;
    printf("=== CS253 Sorting Assignment ===\n");
    printf("1. Run full experiments (outputs CSV)\n");
    printf("2. Sort from input file\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if(choice == 2){
        char filename[256];
        printf("Enter filename: ");
        scanf("%s", filename);

        int n = readFromFile(filename, original);
        if(n == -1) return 1;

        printf("\nFile: %s  |  n = %d\n", filename, n);
        printf("%-25s %12s %15s\n", "Algorithm", "Time(us)", "Comparisons");
        printf("------------------------------------------------------\n");

        long long cmp;
        double t;

        t = runSort(selectionSort, original, n, &cmp);
        printf("%-25s %12.2f %15lld\n", "Selection Sort", t, cmp);

        t = runSort(bubbleSort, original, n, &cmp);
        printf("%-25s %12.2f %15lld\n", "Bubble Sort", t, cmp);

        t = runSort(insertionSort, original, n, &cmp);
        printf("%-25s %12.2f %15lld\n", "Insertion Sort", t, cmp);

        t = runSort(mergeSortWrapper, original, n, &cmp);
        printf("%-25s %12.2f %15lld\n", "Merge Sort", t, cmp);

        t = runSort(quickSortFirstWrapper, original, n, &cmp);
        printf("%-25s %12.2f %15lld\n", "Quick (First Pivot)", t, cmp);

        t = runSort(quickSortRandomWrapper, original, n, &cmp);
        printf("%-25s %12.2f %15lld\n", "Quick (Random Pivot)", t, cmp);

        t = runSort(quickSortMedianWrapper, original, n, &cmp);
        printf("%-25s %12.2f %15lld\n", "Quick (Median Pivot)", t, cmp);

        t = runSort(heapSort, original, n, &cmp);
        printf("%-25s %12.2f %15lld\n", "Heap Sort", t, cmp);

        t = runSort(radixSort, original, n, &cmp);
        printf("%-25s %12.2f %15lld\n", "Radix Sort", t, cmp);

        return 0;
    }

    // choice 1 - full experiments, output CSV
    int sizes[] = {100,500,1000,2000,5000,10000,50000,100000};
    int numSizes = 8;

    char *inputTypes[] = {"Random","Sorted","Reverse"};

    printf("Algorithm,InputType,n,Time_us,Comparisons\n");

    for(int s=0; s<numSizes; s++){
        int n = sizes[s];

        for(int type=0; type<3; type++){
            if(type==0)
                generateRandom(original, n);
            else if(type==1)
                generateSorted(original, n);
            else
                generateReverse(original, n);

            long long cmp;
            double t;

            t = runSort(selectionSort, original, n, &cmp);
            printf("Selection,%s,%d,%.2f,%lld\n", inputTypes[type], n, t, cmp);

            t = runSort(bubbleSort, original, n, &cmp);
            printf("Bubble,%s,%d,%.2f,%lld\n", inputTypes[type], n, t, cmp);

            t = runSort(insertionSort, original, n, &cmp);
            printf("Insertion,%s,%d,%.2f,%lld\n", inputTypes[type], n, t, cmp);

            t = runSort(mergeSortWrapper, original, n, &cmp);
            printf("MergeSort,%s,%d,%.2f,%lld\n", inputTypes[type], n, t, cmp);

            // skip quicksort first on large sorted/reverse - stack overflow
            if(n > 10000 && (type==1 || type==2))
                printf("QuickV1,%s,%d,SKIP,SKIP\n", inputTypes[type], n);
            else{
                t = runSort(quickSortFirstWrapper, original, n, &cmp);
                printf("QuickV1,%s,%d,%.2f,%lld\n", inputTypes[type], n, t, cmp);
            }

            t = runSort(quickSortRandomWrapper, original, n, &cmp);
            printf("QuickV2,%s,%d,%.2f,%lld\n", inputTypes[type], n, t, cmp);

            t = runSort(quickSortMedianWrapper, original, n, &cmp);
            printf("QuickV3,%s,%d,%.2f,%lld\n", inputTypes[type], n, t, cmp);

            t = runSort(heapSort, original, n, &cmp);
            printf("HeapSort,%s,%d,%.2f,%lld\n", inputTypes[type], n, t, cmp);

            t = runSort(radixSort, original, n, &cmp);
            printf("RadixSort,%s,%d,%.2f,%lld\n", inputTypes[type], n, t, cmp);
        }
        fprintf(stderr, "Done n=%d\n", n);
    }

    return 0;
}
