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
        Arr[i]= rand();
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



void QuickSort (int *s_arr, int first, int last)
{

    if (first < last)
    {
        int left = first, right = last, middle = s_arr[(left + right) / 2];
        do
        {
            while (s_arr[left] < middle) left++;
            while (s_arr[right] > middle) right--;
            if (left <= right)
            {
                int tmp = s_arr[left];
                s_arr[left] = s_arr[right];
                s_arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        QuickSort(s_arr, first, right);
        QuickSort(s_arr, left, last);
    }
}

void BubbleSort (int* Arr,int nul, int Size)
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

void merge(int *array, int l, int m, int r) {
    int i, j, k, nl, nr;
    //size of left and right sub-arrays
    nl = m-l+1; nr = r-m;
    int* larr = new int [nl];
    int* rarr = new int [nr];
    //fill left and right sub-arrays
    for(i = 0; i<nl; i++)
        larr[i] = array[l+i];
    for(j = 0; j<nr; j++)
        rarr[j] = array[m+1+j];
    i = 0; j = 0; k = l;
    //marge temp arrays to real array
    while(i < nl && j<nr) {
        if(larr[i] <= rarr[j]) {
            array[k] = larr[i];
            i++;
        }else{
            array[k] = rarr[j];
            j++;
        }
        k++;
    }
    while(i<nl) {       //extra element in left array
        array[k] = larr[i];
        i++; k++;
    }
    while(j<nr) {     //extra element in right array
        array[k] = rarr[j];
        j++; k++;
    }

    delete[] larr;
    delete[] rarr;
}

void mergeSort(int *array, int l, int r) {
    int m;
    if(l < r) {
        int m = l+(r-l)/2;
        // Sort first and second arrays
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge(array, l, m, r);
    }
}

void insertionSort(int* arr,int nul, int n)
{
    n++;
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void SelectionSort(int* arr,int nul, int n)
{
    n++;
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element with the first element
        swap(arr[min_idx], arr[i]);
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

void (*sortind [5])(int*, int, int) ;









int main() {

    cout <<"Start" << endl;

    int *arr ;
    int i=0;

    sortind[0] = QuickSort ;
    sortind[1] = BubbleSort;
    sortind[2] = mergeSort;
    sortind[3] = insertionSort;
    sortind[4] = SelectionSort;


    ofstream filesort[5];

    filesort[0].open  ("qsort.txt");
    filesort[1].open ("bsort.txt");
    filesort[2].open ("msort.txt");
    filesort[3].open ("insort.txt");
    filesort[4].open ("selsort.txt");





    string Nameofsort [5] = {"qsort","bsort","msort","insort","selsort"};



    for (int size = 1024 ; size < 5000000  ; size <<= 1) {

        cout << "Sorting (" << i + 1 << " out of 13)" << endl;

        arr = new int [size];


        for  (int sn=0 ; sn<5 ; sn++){

            new_arr(arr, size);

            filesort[sn] << size << "\t";

            float start = clock();
            sortind[sn](arr,0, size-1);
            float end = clock();

            float time = end - start;

            filesort[sn] << time << "\n";

            TestArray(arr, size, Nameofsort[sn] );

            cout << Nameofsort[sn] << "-OK"<< endl;
        }

        delete[] arr;
        i++;
    }

    cout<< "Sorting finished"<< endl;

    for (int i =0; i<5 ; i++)
        filesort[i].close();

    FILE* gnuplot_fd = popen ("gnuplot\\bin\\gnuplot", "w") ;


    plot(gnuplot_fd, "qsort.txt", "Quick sort", "1" );
    plot(gnuplot_fd, "bsort.txt", "Bubble sort", "2" );
    plot(gnuplot_fd, "msort.txt", "Merge sort", "3" );
    plot(gnuplot_fd, "insort.txt", "Insertion sort", "4" );
    plot(gnuplot_fd, "selsort.txt", "Selection sort", "4" );

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
    fprintf(gnuplot_fd, "replot \"insort.txt\" using 1:2 title \"Insertion sort\" with linespoints\n");
    fprintf(gnuplot_fd, "replot \"selsort.txt\" using 1:2 title \"Selection sort\" with linespoints\n");

    fflush(gnuplot_fd);




    system ("pause");

    return 0;
}
