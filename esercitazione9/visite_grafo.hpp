/* NOTA: Per l'esercitazione 8, dato che non era richiesto, non ho usato classi template per unidirected_edge 
e unidirected_graph, quindi i nodi sono tutti di tipo int */

#include <set>
#include <map>
#include <queue>
#include <utility>
#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"
#include "contenitori.hpp"


/* FUNZIONE graph_visit() */
template<typename Container>
unidirected_graph graph_visit(const unidirected_graph& grafo, int nodo_sorgente, Container& contenitore)
{
    // Grafo che contiene l'albero risultante dalla visita
    unidirected_graph albero_visite;

    // Insieme di tutti i nodi visitati
    std::set<int> nodi_visitati;

    // Inserisco il nodo sorgente nella struttura
    contenitore.put(nodo_sorgente);

    // Segno subito la sorgente come visitata (come fa la tua amica)
    nodi_visitati.insert(nodo_sorgente);

    // Finché ci sono nodi da esplorare
    while (!contenitore.empty())
    {
        // Prendo un nodo dalla struttura (stack per DFS, coda per BFS)
        int u = contenitore.get();

        // Trovo tutti i nodi adiacenti a u
        auto nodi_adiacenti = grafo.neighbors(u); // std::set<int>

        // Itero sui vicini di u
        for (int v : nodi_adiacenti)
        {
            // Se v non è ancora stato visitato
            if (nodi_visitati.find(v) == nodi_visitati.end())
            {
                // Lo segno come visitato
                nodi_visitati.insert(v);

                // Aggiungo l'arco (u, v) all'albero delle visite
                albero_visite.add_edge(unidirected_edge(u, v));

                // Inserisco v nella struttura per esplorare i suoi vicini in seguito
                contenitore.put(v);
            }
        }
    }

    // Restituisco l'albero risultante sotto forma di grafo
    return albero_visite;
}

/* FUNZIONE recursive_dfs() */
// Funzione di supporto ricorsiva
void dfs_visit(const unidirected_graph& grafo, int u, std::set<int>& nodi_visitati, unidirected_graph& albero_visite)
    {
        nodi_visitati.insert(u);

        auto nodi_adiacenti = grafo.neighbors(u); // Sempre auto per std::set<int>

        for (int v : nodi_adiacenti) // Sempre range-based for
        {
            if (nodi_visitati.find(v) != nodi_visitati.end()) {
                continue;
            }

            albero_visite.add_edge(unidirected_edge(u, v));

            dfs_visit(grafo, v, nodi_visitati, albero_visite);
        }
    }

// Vera funzione recursive_dfs()
unidirected_graph recursive_dfs(const unidirected_graph& grafo, int nodo_sorgente)
{
    unidirected_graph albero_visite;
    std::set<int> nodi_visitati;

    dfs_visit(grafo, nodo_sorgente, nodi_visitati, albero_visite);

    return albero_visite;
}

/* ALGORITMO DIJKSTRA */
// Ho usato Perplexity in quanto ancora non ho visto bene le note sui cammini minimi (notes 11)

void dijkstra(const unidirected_graph& grafo,
              int nodo_sorgente,
              const std::map<unidirected_edge, double>& pesi, // mappa unidirected_edge -> peso (double) per ogni arco
              std::map<int, int>& predecessore, // mappa nodo -> predecessore lungo il cammino minimo
              std::map<int, double>& distanza) // mappa nodo -> distanza minima dalla sorgente
{
    // Insieme di tutti i nodi del grafo
    std::set<int> nodi = grafo.all_nodes();

    // Mappa per tenere traccia di quali nodi hanno una distanza finita (cioè già calcolata)
    std::map<int, bool> distanza_finita;

    // Inizializzazione: nessun nodo ha distanza finita, predecessore "vuoto"
    for (auto it = nodi.begin(); it != nodi.end(); ++it)
    {
        int i = *it;
        predecessore[i] = -1;       // -1 come "nessun predecessore"
        distanza_finita[i] = false;     // equivale a distanza infinita
    }

    // Inizializzo la sorgente
    predecessore[nodo_sorgente] = nodo_sorgente; // la sorgente ha se stessa come predecessore
    distanza[nodo_sorgente] = 0.0;
    distanza_finita[nodo_sorgente] = true;

    // Coda di priorità (min-heap) che contiene coppie (distanza, nodo)
    std::priority_queue<
        std::pair<double, int>,
        std::vector<std::pair<double, int>>,
        std::greater<std::pair<double, int>>
    > coda_prioritaria;

    // Inserisco la sorgente nella coda di priorità
    coda_prioritaria.push(std::make_pair(0.0, nodo_sorgente));

    // Loop principale dell'algoritmo di Dijkstra
    while (!coda_prioritaria.empty())
    {
        // Estraggo la coppia (distanza, nodo) con distanza minima
        std::pair<double, int> elemento_top = coda_prioritaria.top();
        coda_prioritaria.pop();

        double distanza_u = elemento_top.first;
        int u = elemento_top.second;

        // Se esiste già una distanza migliore per u, questo elemento è "vecchio" e lo scarto
        if (distanza_finita[u] && distanza_u > distanza[u])
        {
            continue;
        }

        // Ottengo i nodi adiacenti a u
        std::set<int> nodi_adiacenti = grafo.neighbors(u);  // neighbors(u) del tuo grafo [file:5]

        // Relax sugli archi (u, v) per tutti i vicini v
        for (auto it_v = nodi_adiacenti.begin(); it_v != nodi_adiacenti.end(); ++it_v)
        {
            int v = *it_v;

            // Recupero il peso dell'arco (u, v) usando unidirected_edge
            unidirected_edge arco_corrente(u, v);
            double peso_u_v = 0.0;

            auto it_peso = pesi.find(arco_corrente);
            if (it_peso != pesi.end())
            {
                peso_u_v = it_peso->second;
            }
            else
            {
                // Se non esiste un peso per questo arco, lo salto
                continue;
            }

            // Se v non ha ancora distanza finita, oppure ho trovato un cammino migliore, aggiorno
            if (!distanza_finita[v] || distanza[v] > distanza[u] + peso_u_v)
            {
                distanza[v] = distanza[u] + peso_u_v;
                predecessore[v] = u;
                distanza_finita[v] = true;

                // Inserisco la nuova stima di distanza in coda (simula DecreaseKey)
                coda_prioritaria.push(std::make_pair(distanza[v], v));
            }
        }
    }
}