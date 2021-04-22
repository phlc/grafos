/*
Pucminas - Ciência da Computação - Coração Eucarístico
Grafos - Manhã
Pedro Henrique Lima Carvalho

Desafio Finding Bridges
*/

//Dependencies
#include <iostream>
#include "graph_matrix.cc"

using namespace std;

/*
Main - Main Function
*/
int main(){
    Graph grafo = Graph(6, true, false);
    for (int i=0; i<6; i++){
        grafo.addVertex();
    }
    grafo.addEdge(0, 1);
    grafo.addEdge(0, 3);
    grafo.addEdge(0, 4);
    grafo.addEdge(1, 2);
    grafo.addEdge(1, 3);
    grafo.addEdge(1, 4);
    grafo.addEdge(2, 3);
    grafo.addEdge(2, 4);
    grafo.addEdge(2, 5);
    grafo.addEdge(3, 5);
    grafo.addEdge(4, 5);
    grafo.print();

    cout << endl;

}