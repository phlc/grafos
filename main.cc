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
#include "valued_graph.cc"

using namespace std;

/*
Main - Main Function
*/
int main(){
    Valued_Graph grafo = Valued_Graph(5, false, true, 2);
    grafo.print();
    int v1 = grafo.addVertex();
    grafo.print();
    int v2 = grafo.addVertex();
    grafo.print();
    int a1 = grafo.addEdge(v1,v2, 4);
    grafo.print();
    int a2 = grafo.addEdge(v1,v2, 8);
    grafo.print();
    grafo.removeEdge(v1,v2,a1);
    grafo.print();
    int a3 = grafo.addEdge(v1,v2,16);
    grafo.print();
    grafo.removeVertex(v1);
    grafo.print();
}