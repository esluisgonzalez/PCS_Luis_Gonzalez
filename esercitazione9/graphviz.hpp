#include <fstream>
#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"

// Genera un file DOT a partire da unidirected_graph
void genera_dot(const unidirected_graph& grafo, const std::string& nome_file_base)
{
    // Nome del file .dot che verrà creato
    std::string nome_dot = nome_file_base + ".dot";

    std::ofstream output_file(nome_dot);
    if (!output_file) {
        std::cerr << "Errore: impossibile aprire il file " << nome_dot << " per la scrittura\n";
        return;
    }

    // Intestazione di un grafo non orientato in DOT
    output_file << "graph G {\n";

    // Stampo tutti gli archi del grafo
    // all_edges() restituisce una std::list<unidirected_edge> [file:5]
    for (const unidirected_edge& edge : grafo.all_edges())
    {
        int u = edge.from();
        int v = edge.to();

        output_file << "  " << u << " -- " << v << ";\n";
    }

    output_file << "}\n";
}