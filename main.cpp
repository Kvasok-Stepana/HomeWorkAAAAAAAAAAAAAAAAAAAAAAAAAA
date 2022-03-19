#include <Windows.h>
#include <locale>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

void new_arr(int*& Arr,int Size)
{
    Arr = new int [Size];
    for (int i=0; i<Size;i++)
    {
        Arr[i]= rand()%10000;
    }
}


void Exit(int* Arr)
{
    delete[] Arr;
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




int main() {


    int *arr ;



    int i=0;

    std::ofstream quicksort("qsort.txt", std::ios::out);
    std::ofstream bubblesort("bsort.txt", std::ios::out);

    for (int size = 16; size < 5000000 ; size <<= 2){

        int t=0;


        quicksort << size <<  "\t" ;
        new_arr(arr,size);
        t = GetTickCount();
        QuickSort(arr,0,size-1);
        quicksort << GetTickCount() - t << "\n";

        quicksort << size <<  "\t" ;
        new_arr(arr,size);
        t = GetTickCount();
        BubbleSort(arr,size);
        bubblesort << GetTickCount() - t << "\n";


        std::cout << i << endl;
        i++;
    }

    quicksort.close();
    bubblesort.close();

    FILE* gnuplot_fd;

    if ((gnuplot_fd = _popen("gnuplot\\bin\\gnuplot", "w")) == NULL)
    {
        fprintf(stderr, "Error opening pipe to gnuplot.\n");
        exit(1);
    }





    return 0;
}
