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
            new_arr(arr, size);
            auto start = chrono::high_resolution_clock::now();
            BubbleSort(arr, size);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<float> timeS = end - start;

            bubblesort << timeS.count() << "\n";
            TestArray(arr, size, "bubble_sort");

            cout << "bsort - OK"<< endl;
        }

        if (size < 5000000){
            mergesort << size << "\t";

            new_arr(arr, size);

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



    plot(gnuplot_fd, "qsort.txt", "Quick sort", "1" );
    plot(gnuplot_fd, "bsort.txt", "Bubble sort", "2" );
    plot(gnuplot_fd, "msort.txt", "Merge sort", "3" );


    fprintf(gnuplot_fd, "set terminal windows ");
    fprintf(gnuplot_fd, "0");
    fprintf(gnuplot_fd, "\nset title \'");
    fprintf(gnuplot_fd, "All sorts");
    fprintf(gnuplot_fd, "\'\n");
    fprintf(gnuplot_fd, "set xlabel \"Number of a elements\"\nset ylabel \"Time\"\n");
    fprintf(gnuplot_fd, "plot \"bsort.txt\" using 1:2 title \"Bubble sort\" with linespoints\n");
    fprintf(gnuplot_fd, "replot \"qsort.txt\" using 1:2 title \"Quick sort\" with linespoints\n");
    fprintf(gnuplot_fd, "replot \"msort.txt\" using 1:2 title \"Merge sort\" with linespoints\n");

    fflush(gnuplot_fd);




    system ("pause");

    return 0;
}
