#include <vector>
#include <cstdlib> // Libreria necessaria per usare EXIT_SUCCESS e EXIT_FAILURE
#include <random> // Libreria necessaria per generare i valori di dimensione, min, max
#include "sorts.hpp"
#include "randfiller.h"

int main()
{
    /* ============================
    TEST ORDINAMENTO SU 100 VETTORI
    ============================ */

    randfiller rf;
    std::mt19937 gen(std::random_device{}()); // Crea un generatore
    std::uniform_int_distribution<int> range_dimensione_vec(0, 100); // Range per la dimensione del vettore 
    std::uniform_int_distribution<int> range_valore_minimo(1, 100); // Range dei valori per min
    std::uniform_int_distribution<int> range_valore_massimo(1, 100); // Range dei valori per max

    bool ordinati = true; // Considero il vettore ordinato a priori, se non è così questo valore verrà modificato nel ciclo

    for (int i = 0; i < 100 ; i++)
    {
        /* SCELTA DELLA DIMENSIONE, MIN, MAX E CREAZIONE DEL VETTORE */
        int dimensione = range_dimensione_vec(gen); // Sceglie (per ogni i) la dimensione del vettore (tra 0 e 100)
        int min = -range_valore_minimo(gen); // Sceglie (per ogni i) il valore minimo che posso inserire nel vettore
        int max = range_valore_massimo(gen); // Sceglie (per ogni i) il valore massimo che posso inserire nel vettore

        /* CREAZIONE E RIEMPIMENTO DEL VETTORE */
        std::vector<int> vec(dimensione); // Crea un vettore "vec" di dimensione "dimensione" scelta a caso
        rf.fill(vec, min, max); // Riempie di valori il vettore creato fuori dal ciclo
        
        if (dimensione > 1) // Se il vettore ha almeno 2 elementi garantisce che ci siano sempre sia valori positivi che negativi
        {
            vec[0] = -1;
            vec[dimensione -1] = 1;
        }

        /* ESECUZIONE ALGORITMO E CONTROLLO DELL'ORDINAMENTO */
        mergesort(vec);

        if (!is_sorted(vec))
        {
            ordinati = false;
        }
    }

    /* ========================
    TEST ORDINAMENTO SU STRINGA
    ======================== */

    std::vector<std::string> vec_string = {"c", "a", "b", "e", "d", "z", "x", "m", "n", "l"};

    /* ESECUZIONE ALGORITMO E CONTROLLO DELL'ORDINAMENTO */
    mergesort(vec_string);

    if (!is_sorted(vec_string))
    {
        ordinati = false;
    }

    /* ==============
    FEEDBACK DEI TEST
    ============== */

    if (ordinati) return EXIT_SUCCESS;
    else return EXIT_FAILURE;
}