/*
Pucminas - Ciência da Computação - Coração Eucarístico
Grafos - Manhã
Pedro Henrique Lima Carvalho

Trabalho 1
First Graph's Implementation
- Directed Not-Valued
- Not-Directed Not-Valued
- Directed Valued
- Not-Directed Value
*/

//Dependencies
#include <iostream>

using namespace std;

/*
Graph Class - Classe de Implementação dos Grafos
Opção para Grafos direcionados e não direcionados, simples e multigrafos.
Estrutura de dados: matriz n x n -> n = número máximo de vértices.
Graph(x,x) = -1 -> vértice inexistente.
Graph(x,x) =  0 -> vértice criado, sem loop.
Graph(x,x) >= 1 -> um ou mais loops.
Graph(x,y) >= 1 -> uma ou mais arestas ligando o vertice x -> y.
* Para grafos simples valor de Graph(x,x) = -1 || 0, Graph(x,y) = 0 || 1.
* Para grafos não direcionados Graph(x,y) == Graph(y,x).
*/
class Graph{
private:
    bool simple;           // tipo definido apenas pelo construtor, não é admitida alteração.
    bool directed;
    int v_max;            // é permitida a ampliação do grafo, com custo de cópia. 
    int v_next;           // próximo índice disponível para criação de vértice 
    int** matrix;         // matriz representativa do grafo.

public:
    /*
    Constructors
    */
    //Construtor completo
    Graph(int size, bool simple, bool directed){
        this->simple = simple;
        this->directed = directed;
        v_max = size;
        v_next = 0;
        matrix = new int*[v_max];
        for(int i=0; i<v_max; i++){
            matrix[i] =  new int[v_max];
        }
    }


    //Destructor
    ~Graph(){
        for(int i=0; i<v_max; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
};
/*
Main - Main Function
*/
int main(){
    int n_vertices;
    cout << "Insira o número de vértices:" <<endl;
    cin >> n_vertices;
    Graph grafo = Graph(n_vertices, true, false);
}
