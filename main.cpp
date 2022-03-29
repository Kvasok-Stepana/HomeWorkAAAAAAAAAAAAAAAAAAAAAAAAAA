#include <Windows.h>
#include <locale>
#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <string>

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
        if(Arr[i]>Arr[i+1])
        {
            cout<< i+1 << endl;
            cout << "Erorre in " <<  sortname << " with size " << size << endl << "Array is not sorted"<< endl;
            system ("pause");
        }
    }
}



void QuickSort (int *Arr, int first, int last)
{

    if (first < last)
    {
        int left = first, right = last, middle = Arr[(left + right) / 2];
        do
        {
            while (Arr[left] < middle) left++;
            while (Arr[right] > middle) right--;
            if (left <= right)
            {
                int tmp = Arr[left];
                Arr[left] = Arr[right];
                Arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        QuickSort(Arr, first, right);
        QuickSort(Arr, left, last);
    }
}

void QSortThread (int *Arr, int first, int last){
    int left = first, right = last, middle = Arr[(left + right) / 2];
    do
    {
        while (Arr[left] < middle) left++;
        while (Arr[right] > middle) right--;
        if (left <= right)
        {
            int tmp = Arr[left];
            Arr[left] = Arr[right];
            Arr[right] = tmp;
            left++;
            right--;
        }
    } while (left <= right);

    thread streamA (QuickSort,Arr,first,right);
    thread streamB (QuickSort,Arr,left, last);

    streamA.join();
    streamB.join();

}

void BubbleSort (int* Arr,int nul, int Size)
{
    Size++;

    for (int i = 0; i < Size; ++i)
    {
        for (int j = i + 1   ; j < Size; j++)
        {
            if (Arr[i] > Arr[j])
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

void BrickSort (int* arr,int nul, int size){
    size++;
    for (int i = 0; i < size; i++) {
        // (i % 2) ? 0 : 1 возвращает 1, если i четное, 0, если i не четное
        for (int j = (i % 2) ? 0 : 1; j + 1 < size; j += 2) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void GnomeSort(int* arr,int nul, int Size){
    Size++;

    int i = 0;
    while (i < Size)
    {
        if (i == 0 || arr[i - 1] <= arr[i])
            ++i;
        else
        {
            int tmp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = tmp;
            --i;
        }
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

void (*sortind [8])(int*, int, int) ;




int main() {

    cout <<"Start" << endl;

    int *arr ;
    int i=0;

    sortind[0] = QuickSort ;
    sortind[1] = BubbleSort;
    sortind[2] = mergeSort;
    sortind[3] = insertionSort;
    sortind[4] = SelectionSort;
    sortind[5] = QSortThread;
    sortind[6] = BrickSort;
    sortind[7] = GnomeSort;

    ofstream filesort[8];

    filesort[0].open  ("qsort.txt",ios::out);
    filesort[1].open ("bsort.txt",ios::out);
    filesort[2].open ("msort.txt",ios::out);
    filesort[3].open ("insort.txt",ios::out);
    filesort[4].open ("selsort.txt",ios::out);
    filesort[5].open ("qsortthread.txt",ios::out);
    filesort[6].open ("brsort.txt",ios::out);
    filesort[7].open ("gnsort.txt",ios::out);

    string Nameofsort [8] = {"qsort","bsort","msort","insort","selsort","qsortthread","brsort","gnsort"};

    int stopsort[8]={0,0,0,0,0,0,0,0};

    int size = 1000;

    for (int i = 0 ; i < 56 ; i++) {

        cout << "Sorting (" << i + 1 << " out of 56)" << endl;

        arr = new int [size];


        for  (int sn=0 ; sn<8 ; sn++){
            if (stopsort[sn] == 0){
                new_arr(arr, size);

                filesort[sn] << size << "\t";

                auto start = chrono::high_resolution_clock::now();
                sortind[sn](arr, 0, size - 1);
                auto end = chrono::high_resolution_clock::now();

                unsigned int time = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                filesort[sn] << time << "\n";

                if (time>1000000000){
                    stopsort[sn]++;
                }

                TestArray(arr, size, Nameofsort[sn]);

                cout << Nameofsort[sn] << "-OK" << endl;
            }
        }

        if (size < 50000)
            size += 1000;
        else
            size *=2;


        delete[] arr;

    }

    cout<< "Sorting finished"<< endl;

    for (int i =0; i<8 ; i++)
        filesort[i].close();

    FILE* gnuplot_fd = popen ("gnuplot\\bin\\gnuplot", "w") ;


    plot(gnuplot_fd, "qsort.txt", "Quick sort", "1" );
    plot(gnuplot_fd, "bsort.txt", "Bubble sort", "2" );
    plot(gnuplot_fd, "msort.txt", "Merge sort", "3" );
    plot(gnuplot_fd, "insort.txt", "Insertion sort", "4" );
    plot(gnuplot_fd, "selsort.txt", "Selection sort", "5" );
    plot(gnuplot_fd, "qsortthread.txt", "Quick sort multithreaded", "6" );
    plot(gnuplot_fd, "brsort.txt", "Brick sort", "7" );
    plot(gnuplot_fd, "gnsort.txt", "Gnome sort", "8" );

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
    fprintf(gnuplot_fd, "replot \"qsortthread.txt\" using 1:2 title \"Quick sort multithreaded\" with linespoints\n");
    fprintf(gnuplot_fd, "replot \"brsort.txt\" using 1:2 title \"Brick sort\" with linespoints\n");
    fprintf(gnuplot_fd, "replot \"gnsort.txt\" using 1:2 title \"Gnome sort\" with linespoints\n");

    fflush(gnuplot_fd);


    system ("pause");

    return 0;
}
