#include <list>
#include <set>
#include <map>
#include <iostream>
#include <cstdlib>
#include "unidirected_edge.hpp"

class unidirected_graph
{
    std::list<unidirected_edge> edges_list; // Lista di tutti gli edges
    std::map<int, std::set<int>> nodi_adiacenti; // Mappa nodo -> insieme dei nodi adiacenti
    std::map<unidirected_edge, int> numerazione_edges; // Mappa edge -> numerazione all'interno del grafo
    // NOTA (sulla sintassi per mappe): La sintassi generale per le mappe è std::map<Key, T>

    public:
        /* COSTRUTTORE DI DEFAULT */
        unidirected_graph() {} // std::list e std::map si inizializzano già vuote con il loro costruttore di default

        /* COSTRUTTORE USER-DEFINED */
        unidirected_graph(const unidirected_graph& other_graph)
        {
            edges_list = other_graph.edges_list;
            nodi_adiacenti = other_graph.nodi_adiacenti;
            numerazione_edges = other_graph.numerazione_edges;
        }

        /* METODO neighbors */
        std::set<int> neighbors(int nodo) const
        {
            auto iteratore = nodi_adiacenti.find(nodo);

            if (iteratore != nodi_adiacenti.end()) { return iteratore->second; } // Spiegano nelle note ma equivale a (*iteratore).second
            else { return std::set<int>{}; } // Restituisce set vuoto

            /* 
            NOTE IMPORTANTI (Ho usato Perplexity per capire alcune cose)
            1. Con "auto" dichiaro una variabile e lascio che il compilatore ne riconosca automaticamente il tipo
            2. "iteratore" è un iteratore alla mappa, cioè un "puntatore intelligente" che mi permette di scorrere gli elementi
                di un contenitore (in questo caso una mappa) senza sapere com'è implementato dentro. In questo caso "iteratore" 
                punta alla coppia (chiave, valore) e it->first punta  alla chiave mentre it->second punta al valore
            3. Scrivere it->first è come scrivere (*it).first
            4. In una std::map<Key, T>, ogni elemento è una coppia std::pair<const Key, T> e questa coppia ha due campi pubblici;
               first e second (dove first è Key e second è T, come spiegato nel punto 2)
            5. std::map::find e std::map::end sono metodi della classe std::map definita nella libreria <map>
               5.1. generic_map.find(key) prende una chiave e, se esiste nella mappa, l'iteratore punta alla coppia (chiave, valore), se
               la chiave non esiste, restituisce generic_map.end()
               5.2. nodi_adiacenti.end() è un iteratore “di fine” che non punta a nessun elemento valido, ma rappresenta un passo 
               oltre l’ultimo elemento della mappa 
            */
        }
        
        /* METODO add_edge */
        void add_edge(const unidirected_edge& edge)
        {
            int u = edge.from();
            int v = edge.to();

            edges_list.push_back(edge); // Aggiungo l’arco alla lista degli edge

            nodi_adiacenti[u].insert(v); // v diventa vicino di u
            nodi_adiacenti[v].insert(u); // u diventa vicino di v

            int index = edges_list.size() - 1; // L’indice dell'edge sarà la dimensione della lista - 1
            numerazione_edges[edge] = index; // Associa all’arco edge il numero index nella mappa edge -> numerazione
        }

        /* METODO all_edges */
        const std::list<unidirected_edge>& all_edges() const
        {
            return edges_list;
        }

        /* METODO all_nodes */
        std::set<int> all_nodes() const
        {
            std::set<int> nodes_list;

            for (const auto& coppia : nodi_adiacenti) // Scorro tutte le coppie (nodo, insieme_vicini) nella mappa
            {
                int nodo = coppia.first;   // la chiave della mappa
                nodes_list.insert(nodo);     // aggiungo il nodo all'insieme dei nodi
            }

            return nodes_list;
        }

        /* METODO edge_number */
        int edge_number(const unidirected_edge& edge) const
        {
            auto it = numerazione_edges.find(edge);

            if (it != numerazione_edges.end()) 
            {
                return it->second; // Restituisce la numerazione associata all'arco
            } 
            else 
            {
                return -1; // Se l'arco non è presente sul grafo restituisce -1
            }
        }

        /* METODO edge_at */
        const unidirected_edge& edge_at(std::size_t index) const //
        {
            if (index >= edges_list.size()) 
            {
                std::cerr << "ERRORE: edge_at(" << index << ") indice fuori dai limiti\n";
                std::exit(EXIT_FAILURE);
            }

            auto iterator = edges_list.begin();
            for (std::size_t i = 0; i < index; ++i) 
            {
                ++iterator;
            }
            return *iterator;

            /* 
            NOTA (su std::size_t):
            std::size_t è un tipo intero senza segno usato dalla libreria standard per rappresentare dimensioni e indici di 
            contenitori (come size(), length(), ecc.). Lo uso come tipo del parametro index perché un indice non dovrebbe 
            mai essere negativo e così è compatibile con il tipo restituito da edges_list.size().
            */
        }

        /* OPERATORE - */
        unidirected_graph operator-(const unidirected_graph& other_graph) const
        {
            unidirected_graph result;

            for (const auto& edge : this->all_edges()) 
            {
                if (other_graph.edge_number(edge) == -1) 
                {
                    result.add_edge(edge);
                }
            }

            return result;
        }
};