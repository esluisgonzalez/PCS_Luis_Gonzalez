#pragma once
#include <iostream>

/* NOTA: #pragma once è necessario per dire al compilatore di includere unidirected_edge.hpp
al massimo una volta per unità di compilazione dato che è incluso sia in main.cpp che in
unidirected_graph.hpp.

Una alternativa sarebbe togliere #include "unidirected_edge.hpp" dal main ma a quel punto
non potrei usare unidirected_edge se non tramite unidirected_graph.hpp */

class unidirected_edge
{
    int node_from;
    int node_to;


    public:
        /* COSTRUTTORE CHE GARANTIRE FROM < TO */
        unidirected_edge(int a, int b)
        {
            if (a < b)
            {
                node_from = a;
                node_to = b;
            }
            else
            {
                node_from = b;
                node_to = a;
            }
        }

        /* RESTITUZIONE DEI NODI FROM E TO */
        int from() const { return node_from; }
        int to() const { return node_to; }

        /* OPERATORE < */
        bool operator<(const unidirected_edge& other_edge) const
        {
            if (node_from != other_edge.from())
            {
                return node_from < other_edge.from();
                // Dati due edges (a, b), (c, d), se a != c si entra in questa sezione e si confrontano a e c
                // Se a < c, restituisce TRUE, cioè è vero che (a, b) < (c, d)
                // se a > c, restituisce FALSE, cioè (a, b) non è minore di (c, d)
            }
            else
                return node_to < other_edge.to();
                // Dati due edges (a, b), (c, d), se a = c si entra in questa sezione e si confrontano b e d
                // Se b < d, restituisce TRUE, cioè è vero che (a, b) < (c, d)
                // se b > d, restituisce FALSE, cioè (a, b) non è minore di (c, d)
        }

        /* OPERATORE == */
        bool operator==(const unidirected_edge& other_edge) const
        {
            return (node_from == other_edge.from()) && (node_to == other_edge.to());
            // Dati due edges (a, b), (c, d) questo metodo restituisce TRUE se e solo se a = c e b = d
        }
};

/* OPERATORE << */
std::ostream& operator<<(std::ostream& os, const unidirected_edge& edge)
{
    os << "(" << edge.from() << ", " << edge.to() << ")";
    return os;
}