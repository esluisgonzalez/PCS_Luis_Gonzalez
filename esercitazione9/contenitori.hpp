#pragma once
#include <stack>
#include <queue>

/* NOTA: Per l'esercitazione 8, dato che non era richiesto, non ho usato classi template per unidirected_edge 
e unidirected_graph, quindi i nodi sono tutti di tipo int */

/* CONTENITORE DI TIPO LIFO */
class lifo
{
    std::stack<int> stack;

    public:
        /* COSTRUTTORE DI DEFAULT */
        lifo() {}

        /* METODO PUT */
        void put(const int& x)
        {
            stack.push(x);
        }

        /* METODO GET */
        int get()
        {
            int top_element = stack.top();
            stack.pop();
            return top_element;
        }

        /* METODO EMPTY */
        bool empty() const
        {
            return stack.empty();
        }
};

/* CONTENITORE DI TIPO FIFO */
class fifo
{
    std::queue<int> queue;

    public:
        /* COSTRUTTORE DI DEFAULT */
        fifo() {}

        /* METODO PUT */
        void put(const int& x)
        {
            queue.push(x);
        }

        /* METODO GET */
        int get()
        {
            int first_element = queue.front();
            queue.pop();
            return first_element;
        }

        /* METODO EMPTY */
        bool empty() const
        {
            return queue.empty();
        }
};