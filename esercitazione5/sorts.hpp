#include <vector>

/* FUNZIONE is_sorted() */
template <typename T>
bool is_sorted(const std::vector<T>& vec)
// NOTA: Non serve usare std::optional in quanto la funzione mi deve dire solo se il vettore è ordinato o meno //
{
    if (vec.size() == 0 || vec.size() == 1)
    {
        return true;
    }

    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i - 1] > vec[i])
        {
            return false; 
        }
    }

    return true;
}

/* ALGORITMO BUBBLE SORT */
template <typename T>
void bubble_sort(std::vector<T>& vec)
{
    if (vec.size() < 2)
    {
        return;
    }

    for (int i = 0; i < vec.size() - 1; i++)
    {
        for (int j = vec.size() - 1; j > i; j--)
        {
            if (vec[j] < vec[j - 1])
            {
                T x = vec[j];
                vec[j] = vec[j - 1];
                vec[j - 1] = x;
            }
        }
    }
}

/* ALGORITMO SELECTION SORT */
template <typename T>
void selection_sort(std::vector<T>& vec)
{
    if (vec.size() < 2)
    {
        return;
    }
    
    for (int i = 0; i < vec.size() - 1; i++)
    {
        int min_index = i;

        for (int j = i + 1; j < vec.size(); j++)
        {
            if (vec[j] < vec[min_index])
            {
                min_index = j;
            }
        }
    if (min_index != i)
    {
        T x = vec[i];
        vec[i] = vec[min_index];
        vec[min_index] = x;
    }
    }
}

/* ALGORITMO INSERTION SORT */
template <typename T>
void insertion_sort(std::vector<T>& vec)
{
    if (vec.size() < 2)
    {
        return;
    }
    
    for (int i = 1; i < vec.size(); i++)
    {
        T value = vec[i];
        int j = i - 1;

        while (j >= 0 && vec[j] > value)
        {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = value;
    }
}

/* ALGORITMO MERGE SORT */
template <typename T>
void merge(std::vector<T>& vec, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    std::vector<T> L(n1);
    std::vector<T> R(n2);

    for (int i = 0; i < n1; ++i) 
    {
        L[i] = vec[p + i];
    }

    for (int j = 0; j < n2; ++j) 
    {
        R[j] = vec[q + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = p;

    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j])
        {
            vec[k] = L[i];
            ++i;
        }
        else
        {
            vec[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) 
    {
        vec[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) 
    {
        vec[k] = R[j];
        ++j;
        ++k;
    }
}

template <typename T>
void mergesort(std::vector<T>& vec, int p, int r) 
{
    if (p < r) 
    {
        int q = (p + r)/2;
        mergesort(vec, p, q);
        mergesort(vec, q + 1, r);
        merge(vec, p, q, r);
    }
}

template <typename T>
void mergesort(std::vector<T>& vec) 
{
    if (vec.size() < 2) 
    {
        return;
    }
    mergesort(vec, 0, vec.size() - 1);
}

/* ALGORITMO QUICKSORT */
template <typename T>
int partition(std::vector<T>& vec, int p, int r)
{
    T x = vec[r];
    int i = p - 1;

    for (int j = p; j < r; j++)
    {
        if (vec[j] <= x)
        {
            i++;
            T y = vec[i];
            vec[i] = vec[j];
            vec[j] = y;
        }
    }
    T y = vec[i + 1];
    vec[i + 1] = vec[r];
    vec[r] = y;

    return i + 1;
}

template <typename T>
void quicksort(std::vector<T>& vec, int p, int r)
{
    if (p < r)
    {
        int q = partition(vec, p, r);
        quicksort(vec, p, q - 1);
        quicksort(vec, q + 1, r);
    }
}

template <typename T>
void quicksort(std::vector<T>& vec)
{
    if (vec.size() < 2)
    {
        return;
    }
    quicksort(vec, 0, vec.size() - 1);
}

/* ALGORITMO QUICKSORT (MODIFICATO) */
const int SOGLIA = 32;

template <typename T>
void new_quicksort(std::vector<T>& vec, int p, int r)
{
    int len = r - p + 1;

    if (len <= SOGLIA) // Per n <= 32 uso insertion sort sul pezzo vec[p, ..., r]
    {
        for (int i = p + 1; i <= r; ++i)
        {
            T value = vec[i];
            int j = i - 1;
            while (j >= p && vec[j] > value)
            {
                vec[j + 1] = vec[j];
                --j;
            }
            vec[j + 1] = value;
        }
        return;
    }

    if (p < r)
    {
        int q = partition(vec, p, r);
        new_quicksort(vec, p, q - 1);   // chiamata ricorsiva alla versione nuova
        new_quicksort(vec, q + 1, r);
    }
}

template <typename T>
void new_quicksort(std::vector<T>& vec)
{
    if (vec.size() < 2)
    {
        return;
    }
    new_quicksort(vec, 0, vec.size() - 1);
}