/*
Pucminas - Ciência da Computação - Coração Eucarístico
Grafos - Manhã
Pedro Henrique Lima Carvalho

Desafio Finding Bridges
- Deep Search First
- Finding Bridges
*/

//Dependencies
#include <iostream>
#include "graph_matrix.cc"

using namespace std;

/*
Main - Main Function
*/
int main(){
    Graph grafo = Graph(12, true, false);
    for (int i=0; i<12; i++){
        grafo.addVertex();
    }
    grafo.addEdge(0, 1);
    grafo.addEdge(0, 2);
    grafo.addEdge(1, 2);
    grafo.addEdge(1, 3);
    grafo.addEdge(2, 4);
    grafo.addEdge(4, 5);
    grafo.addEdge(4, 6);
    grafo.addEdge(4, 7);
    grafo.addEdge(5, 7);
    grafo.addEdge(6, 7);
    grafo.addEdge(7, 8);
    grafo.addEdge(7, 10);
    grafo.addEdge(7, 11);
    grafo.addEdge(8, 9);
    grafo.addEdge(9, 10);
    grafo.print();

    int** bridges = grafo.findBridges(0);

    //mostrar pontes
    for (int i=0; i<12; i++){
        for (int j=0; j<12; j++){
            if(bridges[i][j]==1){
                cout << "("<< i << ", " << j << ") " << endl;
            }
        }
    }
}