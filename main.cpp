#include <Windows.h>
#include <locale>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <chrono>

/*We had 2 standard libraries, 11 strings in for cycle,
 * 7 sorting algorithms, a memory half-full of arrays
 * and a whole galaxy of data, arrays, random integers,
 * graphs... Not that we strictly needed all of that
 * for the module homework, but once you started desperate
 * attempts of obtaining advanced standing for the course,
 * the tendency is to push it as far as you can.
 * The only thing that really worried me was the multithreaded sort.
 * There is nothing in the world more annoying and complex and shooting itself
 * in the leg than several threads writing simultaneously into one data structure,
 * and I knew we'd get into that rotten stuff pretty soon.
 */


using namespace std;

void new_arr(int* Arr,int Size)
{
    for (int i=0; i<Size;i++)
    {
        Arr[i]= rand()%10000;
    }
}

void TestArray(int* Arr, int size, string sortname){
    for (int i=0;i<size-1;i++){
        if(Arr[i]>Arr[i++])
        {
            cout << "Erorre in" <<  sortname << "with size " << size << endl << "Array is not sorted"<< endl;
            system ("pause");
        }
    }
}



void QuickSort (int *ar, int lo, int hi)
{
    if (lo < hi) {
        int pivot = ar[hi];
        int i = lo-1;
        for (int j = lo; j < hi; ++j)
            if (ar[j] <= pivot)
                swap(ar[++i], ar[j]);

        if (ar[hi] < ar[i+1])
            swap(ar[i+1], ar[hi]);

        int prt = i+1;
        QuickSort(ar, lo, prt-1);
        QuickSort(ar, prt+1, hi);
    }

}

void BubbleSort (int* Arr,int Size)
{
    Size++;

    for (int i = 0; i < Size; ++i)
    {
        for (int j = i + 1   ; j < Size; j++)
        {
            if (Arr[i] < Arr[j])
            {
                swap(Arr[i],Arr[j]);
            }
        }
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int* L = (int*)malloc(sizeof(int) * n1);
    int* R = (int*)malloc(sizeof(int) * n2);

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }

    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }

        else
        {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int* a, int r, int l)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(a, m, l);
        mergeSort(a, r, m + 1);

        merge(a, l, m, r);
    }
}





void plot(FILE* gnuplot_fd, const char* filename, const char* title, const char* window_number)
{


    fprintf(gnuplot_fd, "set terminal windows ");
    fprintf(gnuplot_fd, window_number);
    fprintf(gnuplot_fd, "\nset title \'");
    fprintf(gnuplot_fd, title);
    fprintf(gnuplot_fd, "\'\n");
    fprintf(gnuplot_fd, "set xlabel \"Number of a elements\"\nset ylabel \"Time \"\n");
    fprintf(gnuplot_fd, "plot \'");
    fprintf(gnuplot_fd, filename);
    fprintf(gnuplot_fd, "\' using 1:2 with linespoints \n");

    fflush(gnuplot_fd);
}



void CallSort (int Num,int* Arr, int size, int i)
{


}





int main() {

    cout <<"Start" << endl;

    int *arr ;
    int i=0;



    std::ofstream quicksort("qsort.txt", std::ios::out);
    std::ofstream bubblesort("bsort.txt", std::ios::out);
    std::ofstream mergesort("msort.txt", std::ios::out);

    for (int size = 16; size < 5000000  ; size <<= 1) {

        cout << "Sorting (" << i + 1 << " out of 19)" << endl;

        arr = new int [size];

        new_arr(arr, size);
        quicksort << size << "\t";
        auto start = chrono::high_resolution_clock::now();
        QuickSort(arr, 0, size - 1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> timeS = end - start;
        quicksort << timeS.count() << "\n";
        TestArray(arr, size, "quick_sort" );


        cout << "qsort - OK"<< endl;

        if (size < 90000) {
            bubblesort << size << "\t";
            arr = new int[size];
            auto start = chrono::high_resolution_clock::now();
            BubbleSort(arr, size);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<float> timeS = end - start;
            bubblesort << timeS.count() << "\n";
            TestArray(arr, size, "bubble_sort");

            cout << "bsort - OK"<< endl;
        }

        if (1 == 1){
            mergesort << size << "\t";
            arr = new int[size];
            auto start = chrono::high_resolution_clock::now();
            mergeSort(arr, 0, size - 1);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<float> timeS = end - start;
            mergesort << timeS.count() << "\n";

            TestArray(arr, size, "merge_sort");

            cout << "msort - OK"<< endl;
       }






        delete[] arr;
        i++;
    }

    cout<< "Sorting finished"<< endl;
    quicksort.close();
    bubblesort.close();
    mergesort.close();

    FILE* gnuplot_fd = popen ("gnuplot\\bin\\gnuplot", "w") ;



/*
    plot(gnuplot_fd, "qsort.txt", "Quick sort", "1" );
    plot(gnuplot_fd, "bsort.txt", "Bubble sort", "2" );
    plot(gnuplot_fd, "msort.txt", "Merge sort", "3" );
*/

    fprintf(gnuplot_fd, "set terminal windows ");
    fprintf(gnuplot_fd, "0");
    fprintf(gnuplot_fd, "\nset title \'");
    fprintf(gnuplot_fd, "All sorts");
    fprintf(gnuplot_fd, "\'\n");
    fprintf(gnuplot_fd, "set xlabel \"Number of a elements\"\nset ylabel \"Time\"\n");
    fprintf(gnuplot_fd," \n set logscale x \n");
    fprintf(gnuplot_fd, "plot \"bsort.txt\" using 1:2 title \"Bubble sort\" with linespoints\n");
    fprintf(gnuplot_fd, "replot \"qsort.txt\" using 1:2 title \"Quick sort\" with linespoints\n");
    fprintf(gnuplot_fd, "replot \"msort.txt\" using 1:2 title \"Merge sort\" with linespoints\n");

    fflush(gnuplot_fd);




    system ("pause");

    return 0;
}
