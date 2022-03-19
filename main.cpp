#include <Windows.h>
#include <locale>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>


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

void plot(FILE* gnuplot_fd, const char* filename, const char* title, int window_number, bool plot_in_new_window)
{
    string s = to_string(window_number);

    fprintf(gnuplot_fd, "set terminal windows ");
    fprintf(gnuplot_fd, s.c_str());
    fprintf(gnuplot_fd, "\nset title \'");
    fprintf(gnuplot_fd, title);
    fprintf(gnuplot_fd, "\'\n");
    fprintf(gnuplot_fd, "set xlabel \"Number of a elements\"\nset ylabel \"Time (us)\"\n");
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

    for (int size = 16; size < 4096 ; size <<= 2){

        cout << size<< endl;

        float t=0;

        arr = new int[size];

        quicksort << size <<  "\t" ;
        new_arr(arr,size);
        t = GetTickCount();
        QuickSort(arr,0,size-1);
        quicksort << GetTickCount() - t << "\n";


        if(size < 40000) {
            bubblesort << size << "\t";
            new_arr(arr, size);
            t = GetTickCount();
            BubbleSort(arr, size);
            bubblesort << GetTickCount() - t << "\n";
        }


        delete[] arr;
        i++;
    }

    quicksort.close();
    bubblesort.close();


    FILE* gnuplot_fd;

    plot(gnuplot_fd, "bsort.txt", "BUBBLE SORT", 1, true);
    plot(gnuplot_fd, "qsort.txt", "QUICK SORT", 2, true);





    system ("pause");

    return 0;
}
