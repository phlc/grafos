/*
Pucminas - Ciência da Computação - Coração Eucarístico
Grafos - Manhã
Pedro Henrique Lima Carvalho

Trabalho 1
First Graph's Implementation
- Directed Not-Valued
- Not-Directed Not-Valued
- Directed Valued
- Not-Directed Valued
*/

//Dependencies
#include <iostream>
#include "graph_matrix.cc"

using namespace std;
/* Valued_Graph Class - Classe de Implementação de Valoração das Arestas
Opção para Grafos direcionados e não direcionados, simples e multigrafos.
Estrutura de dados para valoração: matriz n x n x m
n = número máximo de vértices
m = número máximo de arestas paralelas a serem valoradas
Matrix(x,y,z) = 0x8000000 -> Aresta não valorada
Matrix(x,y,z) != 0x8000000 -> Aresta valorada, admite valor zero
*/

class Valued_Graph : public Graph{
private:
    int*** value_matrix;
    int e_max; // número máximo de arestas

    void init(int edges){
        e_max = edges;
        int v_max = Graph::nMax();
        value_matrix = new int**[v_max];
        for(int i=0; i<v_max; i++){
            value_matrix[i] = new int*[v_max];
            for(int j=0; j<v_max; j++){
                value_matrix[i][j] = new int[edges];
                for(int k=0; k<e_max; k++){
                    value_matrix[i][j][k] = 0x80000000;
                }
            }
        }

    }

public:
    /*
    Constructors
    */
    //Construtor completo
    Valued_Graph(int size, bool simple, bool directed, int edges): Graph(size, simple, directed){
        init(edges);
    }
    //Construtor grafo simples, não-direcionado, 
    Valued_Graph(int size): Graph(size){
        init(1); // Grafo Simples - Não tem loops ou arestas paralelas
    }
    //Construtor grafo tamnho 5, simples, não-direcionado, 5
    Valued_Graph(): Graph(){
        init(1); // Grafo Simples - Não tem loops ou arestas paralelas
    }

    //Destructor
    ~Valued_Graph(){
        int v_max = Graph::nMax();
        for(int i=0; i<v_max; i++){
            for(int j=0; j<v_max; j++){
                delete[] value_matrix[i][j];
            }
        }
        delete[] value_matrix;
    }

    //Methods
    /*
    print - mostra a matriz e a matriz de valores
    */
    void print(){
        Graph::print();
        int v_max = Graph::nMax();
        cout << endl;
        for(int i=0; i<v_max; i++){
            for(int j=0; j<v_max; j++){
                cout << "Value_Matrix (" << i << ", " << j << "): ";
                for (int k=0; k<e_max-1; k++){
                    if(value_matrix[i][j][k] == 0x80000000){
                        cout << "_ ";
                    }
                    else{
                            cout << value_matrix[i][j][k] << "  ";
                    }
                }
                if(value_matrix[i][j][e_max-1] == 0x80000000){
                        cout << "_ " << endl;
                }
                else{
                    cout << value_matrix[i][j][e_max-1] << endl;
                }
           }
       }
   }
    /*removeVertex - remove um vértice, todas arestas incidentes e suas valorações
    @param índice do vértice
    @return -1 se vértice inexistente ou número de arestas excluídas com o vértice
    */
    int removeVertex(int vertex){
        int control= Graph::removeVertex(vertex);
        int v_max = Graph::nMax();
        if(control!=-1){
            for(int i=0; i<v_max; i++){
                for(int j=0; j<e_max; j++){
                    value_matrix[vertex][i][j] = 0x80000000;
                    value_matrix[i][vertex][j] = 0x80000000;
                }
            }
        }
        return control;
    }
    
    /*
    addEdge - acrescenta uma aresta valorada
    Se simples, apenas se v1!=v2 && matrix(v1,v2)==0
    Se não-direcionado matrix(v1,v2)=matrix(v2,v1)
    @param vértice 1, vértice 2, valor
    @return -1 para falha, >=0 índice da arestas
    */
    int addEdge(int v1, int v2, int value){
        int control = Graph::addEdge(v1, v2);
        int index = -1;

        //verificar se houve inclusão
        if(control!=-1){
            index = 0;
            while (value_matrix[v1][v2][index] != 0x80000000){
                index++;
            }
            if(index>=e_max){
                index = -1;
            }
            else{
                value_matrix[v1][v2][index] = value;
            }
        }
        return index;
    }

    /*
    removeEdge - remove uma aresta valorada
    @param vértice 1, vértice 2, indice da aresta a ser removida
    @return -1 para falha || >=0 número de arestas restantes
    * 
    */
    int removeEdge (int v1, int v2, int index){
        int control = -1;
        //verificar se os vértices existem
        if(value_matrix[v1][v2][index]!=0x80000000){
            value_matrix[v1][v2][index]=0x80000000;
            control = Graph::removeEdge(v1, v2);
        }
        return control;
    } 
    /*
    Overload para grafos simples
    @param vertice 1, vertice 2;
    @return -1 falha || 0 sucesso
    */
    int removeEdge(int v1, int v2){
        int control = -1;
        if(Graph::isSimple() && value_matrix[v1][v2][0]!=0x80000000){
            value_matrix[v1][v2][0]=0x80000000;
            control = Graph::removeEdge(v1, v2);
        }
        return control;
    }
};
