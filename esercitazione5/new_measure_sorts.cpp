#include <vector>
#include <iostream>
#include <algorithm>
#include "sorts.hpp"
#include "randfiller.h"
#include "timecounter.h"

int main()
{
    randfiller rf;
    timecounter tc;
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> range_valore_minimo(1, 100);
    std::uniform_int_distribution<int> range_valore_massimo(1, 100);

    int numero_vettori = 100;

    for (int n = 4; n <= 128; n *= 2)
    {
        std::vector<std::vector<int>> vettori(numero_vettori, std::vector<int>(n)); // Contiene i 100 vettori di dimensione n

        for (auto& v : vettori)
        {
            int min = -range_valore_minimo(gen);
            int max =  range_valore_massimo(gen);
            rf.fill(v, min, max);
        }

        /* COPIA DEI VETTORI */
        auto vettori_bubble_sort = vettori;
        auto vettori_selection_sort = vettori;
        auto vettori_insertion_sort = vettori;
        auto vettori_mergesort = vettori;
        auto vettori_quicksort = vettori;
        auto vettori_std_sort = vettori;
        auto vettori_new_quicksort = vettori;

        /* BUBBLE SORT */
        tc.tic();
        for (auto& v : vettori_bubble_sort)
            bubble_sort(v);
        double media_bubble_sort = tc.toc() / numero_vettori;

        /* SELECTION SORT */
        tc.tic();
        for (auto& v : vettori_selection_sort)
            selection_sort(v);
        double media_selection_sort = tc.toc() / numero_vettori;

        /* INSERTION SORT */
        tc.tic();
        for (auto& v : vettori_insertion_sort)
            insertion_sort(v);
        double media_insertion_sort = tc.toc() / numero_vettori;

        /* MERGE SORT */
        tc.tic();
        for (auto& v : vettori_mergesort)
            mergesort(v);
        double media_mergesort = tc.toc() / numero_vettori;

        /* QUICKSORT */
        tc.tic();
        for (auto& v : vettori_quicksort)
            quicksort(v);
        double media_quicksort = tc.toc() / numero_vettori;

        /* NEW QUICKSORT */
        tc.tic();
        for (auto& v : vettori_new_quicksort)
            new_quicksort(v);
        double media_new_quicksort = tc.toc() / numero_vettori;

        /* std::sort */
        tc.tic();
        for (auto& v : vettori_std_sort)
            std::sort(v.begin(), v.end());
        double media_std_sort = tc.toc() / numero_vettori;

        // 4) stampa risultati
        std::cout << "n = " << n << "\n";
        std::cout << "Bubble sort (media): " << media_bubble_sort << "\n";
        std::cout << "Selection sort (media): " << media_selection_sort << "\n";
        std::cout << "Insertion sort (media): " << media_insertion_sort << "\n";
        std::cout << "Merge sort (media): " << media_mergesort << "\n";
        std::cout << "Quick sort (media): " << media_quicksort << "\n";
        std::cout << "New quick sort (media): " << media_new_quicksort << "\n";
        std::cout << "std::sort (media): " << media_std_sort << "\n\n";
    }

    return 0;
}