#include <iostream>
#include <set>
#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"

/* TEST unidirected_edge: costruttore, from(), to(), operator==, operator<, operator<< */
void test_unidirected_edge()
{
    std::cout << "\nTEST unidirected_edge\n";

    // edge_1 creato con (5,2) deve diventare (2,5)
    unidirected_edge edge_1(5, 2);
    unidirected_edge edge_2(2, 5);
    unidirected_edge edge_3(1, 4);

    std::cout << "Input:  unidirected_edge edge_1(5, 2);\n";
    std::cout << "Output: edge_1 = " << edge_1 << "\n";
    // atteso: (2,5)

    std::cout << "Input:  unidirected_edge edge_2(2, 5);\n";
    std::cout << "Output: edge_2 = " << edge_2 << "\n";
    // atteso: (2,5)

    std::cout << "Input:  unidirected_edge edge_3(1, 4);\n";
    std::cout << "Output: edge_3 = " << edge_3 << "\n\n";
    // atteso: (1,4)

    // TEST from() e to()
    std::cout << "Test from() e to() su edge_1\n";
    std::cout << "edge_1.from() = " << edge_1.from()
              << ", edge_1.to() = " << edge_1.to() << "\n";
    // atteso: from() = 2, to() = 5

    std::cout << "Test from() e to() su edge_3\n";
    std::cout << "edge_3.from() = " << edge_3.from()
              << ", edge_3.to() = " << edge_3.to() << "\n\n";
    // atteso: from() = 1, to() = 4

    // TEST operator==
    std::cout << "Test operator==\n";
    std::cout << "Input:  edge_1 == edge_2\n";
    std::cout << "Output: " << (edge_1 == edge_2 ? "true" : "false") << "\n";
    // atteso: true

    std::cout << "Input:  edge_1 == edge_3\n";
    std::cout << "Output: " << (edge_1 == edge_3 ? "true" : "false") << "\n";
    // atteso: false

    // TEST operator<
    std::cout << "Test operator<\n";
    std::cout << "Input:  edge_3 < edge_1\n";
    std::cout << "Output: " << (edge_3 < edge_1 ? "true" : "false") << "\n\n";
    // atteso: true perché (1,4) < (2,5)
}

/* TEST add_edge e all_edges */
void test_add_edge_and_all_edges()
{
    std::cout << "TEST add_edge e all_edges\n";

    unidirected_graph grafo;

    unidirected_edge edge_1(1, 3);
    unidirected_edge edge_2(2, 5);
    unidirected_edge edge_3(3, 4);

    std::cout << "Input:  grafo.add_edge(" << edge_1 << ")\n";
    grafo.add_edge(edge_1);
    std::cout << "Input:  grafo.add_edge(" << edge_2 << ")\n";
    grafo.add_edge(edge_2);
    std::cout << "Input:  grafo.add_edge(" << edge_3 << ")\n";
    grafo.add_edge(edge_3);

    std::cout << "Output: lista di tutti gli edge in ordine di inserimento:\n";
    int indice = 0;
    for (const auto& edge : grafo.all_edges()) {
        std::cout << "  Edge " << indice << ": " << edge << "\n";
        ++indice;
    }
    std::cout << "\n";
    // atteso: (1,3), (2,5), (3,4)
}

/* TEST neighbors */
void test_neighbors()
{
    std::cout << "TEST neighbors\n";

    unidirected_graph grafo;
    grafo.add_edge(unidirected_edge(1, 2));
    grafo.add_edge(unidirected_edge(1, 3));
    grafo.add_edge(unidirected_edge(2, 4));

    int nodo_1 = 1;
    int nodo_2 = 2;
    int nodo_3 = 5;  // nodo inesistente nel grafo

    std::cout << "Input:  grafo.neighbors(" << nodo_1 << ")\n";
    std::set<int> adiacenti_nodo_1 = grafo.neighbors(nodo_1);
    std::cout << "Output: nodi adiacenti a " << nodo_1 << ": ";
    for (int nodo_adiacente : adiacenti_nodo_1) {
        std::cout << nodo_adiacente << " ";
    }
    std::cout << "\n";
    // atteso: 2 e 3

    std::cout << "Input:  grafo.neighbors(" << nodo_2 << ")\n";
    std::set<int> adiacenti_nodo_2 = grafo.neighbors(nodo_2);
    std::cout << "Output: nodi adiacenti a " << nodo_2 << ": ";
    for (int nodo_adiacente : adiacenti_nodo_2) {
        std::cout << nodo_adiacente << " ";
    }
    std::cout << "\n";
    // atteso: 1 e 4

    std::cout << "Input:  grafo.neighbors(" << nodo_3 << ") (nodo inesistente)\n";
    std::set<int> adiacenti_nodo_3 = grafo.neighbors(nodo_3);
    std::cout << "Output: nodi adiacenti a " << nodo_3 << ": ";
    for (int nodo_adiacente : adiacenti_nodo_3) {
        std::cout << nodo_adiacente << " ";
    }
    std::cout << "\n\n";
    // atteso: insieme vuoto
}

/* TEST all_nodes */
void test_all_nodes()
{
    std::cout << "TEST all_nodes\n";

    unidirected_graph grafo;
    grafo.add_edge(unidirected_edge(1, 2));
    grafo.add_edge(unidirected_edge(2, 3));
    grafo.add_edge(unidirected_edge(4, 5));

    std::cout << "Input:  grafo.all_nodes()\n";
    std::set<int> lista_nodi = grafo.all_nodes();

    std::cout << "Output: nodi nel grafo: ";
    for (int nodo : lista_nodi) {
        std::cout << nodo << " ";
    }
    std::cout << "\n\n";
    // atteso: 1 2 3 4 5 (ognuno una sola volta)
}

/* TEST edge_number e edge_at */
void test_edge_number_and_edge_at()
{
    std::cout << "TEST edge_number e edge_at\n";

    unidirected_graph grafo;
    unidirected_edge edge_1(1, 2);
    unidirected_edge edge_2(2, 3);
    unidirected_edge edge_3(3, 4);

    grafo.add_edge(edge_1);
    grafo.add_edge(edge_2);
    grafo.add_edge(edge_3);

    // Arco che sicuramente NON esiste nel grafo
    unidirected_edge edge_mancante(10, 20);

    std::cout << "Input:  grafo.edge_number(" << edge_1 << ")\n";
    int indice_edge_1 = grafo.edge_number(edge_1);
    std::cout << "Output: indice_edge_1 = " << indice_edge_1 << "\n";
    // atteso: 0

    std::cout << "Input:  grafo.edge_number(" << edge_2 << ")\n";
    int indice_edge_2 = grafo.edge_number(edge_2);
    std::cout << "Output: indice_edge_2 = " << indice_edge_2 << "\n";
    // atteso: 1

    std::cout << "Input:  grafo.edge_number(" << edge_3 << ")\n";
    int indice_edge_3 = grafo.edge_number(edge_3);
    std::cout << "Output: indice_edge_3 = " << indice_edge_3 << "\n";
    // atteso: 2

    std::cout << "Input:  grafo.edge_number(" << edge_mancante << ") (non esiste)\n";
    int indice_edge_mancante = grafo.edge_number(edge_mancante);
    if (indice_edge_mancante == -1) {
        std::cout << "Output: indice_edge_mancante = not found\n";
        // atteso: not found
    } else {
        std::cout << "Output: indice_edge_mancante = " << indice_edge_mancante << "\n";
    }

    std::cout << "\nInput:  grafo.edge_at(0)\n";
    std::cout << "Output: " << grafo.edge_at(0) << "\n";
    // atteso: edge_1

    std::cout << "Input:  grafo.edge_at(1)\n";
    std::cout << "Output: " << grafo.edge_at(1) << "\n";
    // atteso: edge_2

    std::cout << "Input:  grafo.edge_at(2)\n";
    std::cout << "Output: " << grafo.edge_at(2) << "\n\n";
    // atteso: edge_3
}

/* TEST operator- */
void test_operator_minus()
{
    std::cout << "TEST operator-\n";

    unidirected_graph grafo_G;
    grafo_G.add_edge(unidirected_edge(1, 2));
    grafo_G.add_edge(unidirected_edge(2, 3));
    grafo_G.add_edge(unidirected_edge(3, 4));

    unidirected_graph grafo_H;
    grafo_H.add_edge(unidirected_edge(2, 3));
    grafo_H.add_edge(unidirected_edge(4, 5));

    std::cout << "Input:  grafo_G = {(1,2), (2,3), (3,4)}\n";
    std::cout << "        grafo_H = {(2,3), (4,5)}\n";

    unidirected_graph grafo_diff = grafo_G - grafo_H;

    std::cout << "Output: G - H contiene gli edge:\n";
    for (const auto& edge : grafo_diff.all_edges()) {
        std::cout << "  " << edge << "\n";
    }
    std::cout << "\n";
    // atteso: (1,2) e (3,4)
}

int main()
{
    test_unidirected_edge();
    test_add_edge_and_all_edges();
    test_neighbors();
    test_all_nodes();
    test_edge_number_and_edge_at();
    test_operator_minus();

    return 0;
}