#include <Windows.h>
#include <locale>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>


using namespace std;

void new_arr(int*& Arr,int Size)
{
    for (int i=0; i<Size;i++)
    {
        Arr[i]= rand()%10000;
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

int Savedata(){


}

void plot(FILE* gnuplot_fd, const char* filename, const char* title, const char* window_number)
{


    fprintf(gnuplot_fd, "set terminal windows ");
    fprintf(gnuplot_fd, window_number);
    fprintf(gnuplot_fd, "\nset title \'");
    fprintf(gnuplot_fd, title);
    fprintf(gnuplot_fd, "\'\n");
    fprintf(gnuplot_fd, "plot \'");
    fprintf(gnuplot_fd, filename);
    fprintf(gnuplot_fd, "\' using 1:2 with linespoints\n");

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

    for (int size = 16; size < 5000000  ; size <<= 1){

        cout << "Sorting (" << i+1 << " out of 19)" << endl;

        float t=0;
        float t1=0;

        arr = new int[size];



        quicksort << size <<  "\t" ;
        new_arr(arr,size);
        t = clock();
        QuickSort(arr,0,size-1);
        t1 = clock();
        quicksort << t1-t << "\n";



        if(size < 170000) {
            bubblesort << size << "\t";
            new_arr(arr, size);
            t = clock();
            BubbleSort(arr, size);
            t1 = clock();
            bubblesort << t1-t << "\n";
        }









        delete[] arr;
        i++;
    }

    quicksort.close();
    bubblesort.close();


    FILE* gnuplot_fd ;

    if ((gnuplot_fd = popen ("gnuplot\\bin\\gnuplot", "w")) == NULL)
    {
        fprintf(stderr, "Error opening pipe to gnuplot.\n");
        exit(1);
    }


    plot(gnuplot_fd, "bsort.txt", "BUBBLE SORT", "1" );
    plot(gnuplot_fd, "qsort.txt", "QUICK SORT", "2" );






    system ("pause");

    return 0;
}
