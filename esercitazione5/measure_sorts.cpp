#include <vector>
#include <iostream>
#include <algorithm>   // Libreria necessaria per usate std::sort()
#include "sorts.hpp"
#include "randfiller.h"
#include "timecounter.h"

int main()
{
    randfiller rf;
    timecounter tc;
    std::mt19937 gen(std::random_device{}()); // Crea un generatore
    std::uniform_int_distribution<int> range_valore_minimo(1, 100); // Range dei valori per min
    std::uniform_int_distribution<int> range_valore_massimo(1, 100); // Range dei valori per max

    for (int n = 4; n <= 8192; n *= 2)
    {   
        int dimensione = n;
        int min = -range_valore_minimo(gen); // Sceglie (per ogni i) il valore minimo che posso inserire nel vettore
        int max = range_valore_massimo(gen); // Sceglie (per ogni i) il valore massimo che posso inserire nel vettore

        std::vector<int> vec(dimensione);
        rf.fill(vec, min, max);

        /* COPIA DEL VETTORE */
        std::vector<int> vec_bubble_sort = vec;
        std::vector<int> vec_selection_sort = vec;
        std::vector<int> vec_insertion_sort = vec;
        std::vector<int> vec_std_sort = vec;
        std::vector<int> vec_mergesort = vec;
        std::vector<int> vec_quicksort = vec;

        /* MISURA DEI TEMPI */
        tc.tic();
        bubble_sort(vec_bubble_sort);
        double time_bubble_sort = tc.toc();

        tc.tic();
        selection_sort(vec_selection_sort);
        double time_selection_sort = tc.toc();

        tc.tic();
        insertion_sort(vec_insertion_sort);
        double time_insertion_sort = tc.toc();

        tc.tic();
        std::sort(vec_std_sort.begin(), vec_std_sort.end());
        double time_std_sort = tc.toc();

        tc.tic();
        mergesort(vec_mergesort);
        double time_mergesort = tc.toc();

        tc.tic();
        quicksort(vec_quicksort);
        double time_quicksort = tc.toc();

        /* STAMPA DEI TEMPI */
        std::cout << "n = " << n << "\n";
        std::cout << "Bubble sort: " << time_bubble_sort << "\n";
        std::cout << "Selection sort: " << time_selection_sort << "\n";
        std::cout << "Insertion sort: " << time_insertion_sort << "\n";
        std::cout << "std::sort(): " << time_std_sort << "\n";
        std::cout << "Merge sort: " << time_mergesort << "\n";
        std::cout << "Quicksort: " << time_quicksort << "\n\n";
    }

    return 0;
}