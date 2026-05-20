#include <iostream>
#include <map>
#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"
#include "contenitori.hpp"
#include "visite_grafo.hpp"
#include "graphviz.hpp"

int main()
{
    /* 1) GRAFO NON PESATO (abbastanza complesso) */

    unidirected_graph G;

    // Componente principale con cicli e rami
    G.add_edge(unidirected_edge(1, 2));
    G.add_edge(unidirected_edge(1, 3));
    G.add_edge(unidirected_edge(1, 4));
    G.add_edge(unidirected_edge(2, 5));
    G.add_edge(unidirected_edge(2, 6));
    G.add_edge(unidirected_edge(3, 6));
    G.add_edge(unidirected_edge(3, 7));
    G.add_edge(unidirected_edge(4, 7));
    G.add_edge(unidirected_edge(4, 8));
    G.add_edge(unidirected_edge(5, 6));  // triangolo 2-5-6
    G.add_edge(unidirected_edge(6, 7));  // ciclo 2-6-3-1-2 ecc.
    G.add_edge(unidirected_edge(7, 8));
    G.add_edge(unidirected_edge(7, 9));
    G.add_edge(unidirected_edge(8, 9));
    G.add_edge(unidirected_edge(8, 10));
    G.add_edge(unidirected_edge(9, 11));
    G.add_edge(unidirected_edge(10, 11)); // altro ciclo 8-9-11-10-8

    // Qualche duplicato per testare il filtraggio (nuovo su unidirected_graph rispetto ad esercitazione 8 dove mancava)
    G.add_edge(unidirected_edge(2, 5));
    G.add_edge(unidirected_edge(7, 8));

    std::cout << "GRAFO ORIGINALE G\n";
    std::cout << "Archi:\n";
    for (const auto& e : G.all_edges())
    {
        std::cout << "  " << e << "\n";
    }
    std::cout << "\n";

    genera_dot(G, "grafo_originale");


    /* 2) DFS ITERATIVA (graph_visit + LIFO) */

    lifo s;
    auto dfsG = graph_visit(G, 1, s);

    std::cout << "ALBERO RISULTANTE DFS (da nodo 1)\n";
    for (const auto& e : dfsG.all_edges())
    {
        std::cout << "  " << e << "\n";
    }
    std::cout << "\n";

    genera_dot(dfsG, "albero_dfs");


    /* 3) BFS (graph_visit + FIFO) */

    fifo q;
    auto bfsG = graph_visit(G, 1, q);

    std::cout << "ALBERO RISULTANTE BFS (da nodo 1)\n";
    for (const auto& e : bfsG.all_edges())
    {
        std::cout << "  " << e << "\n";
    }
    std::cout << "\n";

    genera_dot(bfsG, "albero_bfs");

    /* 4) DFS RICORSIVA */

    auto dfs_recursiveG = recursive_dfs(G, 1);

    std::cout << "ALBERO RISULTANTE DFS RICORSIVA (da nodo 1)\n";
    for (const auto& e : dfs_recursiveG.all_edges())
    {
        std::cout << "  " << e << "\n";
    }
    std::cout << "\n";

    /* 5) DIJKSTRA SU GRAFO PESATO */

    unidirected_graph G_pesato;

    // Componente principale (1–8) e un piccolo componente separato (20–21)
    G_pesato.add_edge(unidirected_edge(1, 2));
    G_pesato.add_edge(unidirected_edge(1, 3));
    G_pesato.add_edge(unidirected_edge(2, 4));
    G_pesato.add_edge(unidirected_edge(2, 5));
    G_pesato.add_edge(unidirected_edge(3, 5));
    G_pesato.add_edge(unidirected_edge(3, 6));
    G_pesato.add_edge(unidirected_edge(4, 7));
    G_pesato.add_edge(unidirected_edge(5, 7));
    G_pesato.add_edge(unidirected_edge(5, 8));
    G_pesato.add_edge(unidirected_edge(6, 8));

    // Componente scollegato rispetto al nodo sorgente 1
    G_pesato.add_edge(unidirected_edge(20, 21));

    std::map<unidirected_edge, double> pesi;
    pesi[unidirected_edge(1, 2)] = 3.0;
    pesi[unidirected_edge(1, 3)] = 1.5;
    pesi[unidirected_edge(2, 4)] = 2.0;
    pesi[unidirected_edge(2, 5)] = 2.5;
    pesi[unidirected_edge(3, 5)] = 1.0;
    pesi[unidirected_edge(3, 6)] = 2.2;
    pesi[unidirected_edge(4, 7)] = 3.3;
    pesi[unidirected_edge(5, 7)] = 1.2;
    pesi[unidirected_edge(5, 8)] = 2.8;
    pesi[unidirected_edge(6, 8)] = 1.7;

    // Pesi anche sul componente scollegato (non raggiungibile da 1)
    pesi[unidirected_edge(20, 21)] = 4.0;

    int sorgente = 1;
    std::map<int, int> predecessore;
    std::map<int, double> distanza;

    std::cout << "ESECUZIONE DI DIJKSTRA DAL NODO: " << sorgente << "\n\n";

    dijkstra(G_pesato, sorgente, pesi, predecessore, distanza);

    std::set<int> tutti_i_nodi = G_pesato.all_nodes();
    for (int nodo : tutti_i_nodi)
    {
        std::cout << "Nodo: " << nodo << " -> ";

        auto it_dist = distanza.find(nodo);
        if (it_dist != distanza.end())
        {
            std::cout << "Distanza minima: " << it_dist->second;

            auto it_pred = predecessore.find(nodo);
            std::cout << ", Predecessore: ";
            if (it_pred != predecessore.end() && it_pred->second != -1)
            {
                std::cout << it_pred->second;
            }
            else
            {
                std::cout << "Nessuno";
            }
            std::cout << "\n";
        }
        else
        {
            std::cout << "Non raggiungibile dalla sorgente.\n";
        }
    }

    std::cout << "\n";

    return 0;
}