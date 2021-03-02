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

using namespace std;

/*
Graph Class - Classe de Implementação dos Grafos
Opção para Grafos direcionados e não direcionados, simples e multigrafos.
Estrutura de dados: matriz n x n -> n = número máximo de vértices.
Graph(x,x) = 0 -> vértice inexistente.
Graph(x,x) = 1 -> vértice criado, sem loop.
Graph(x,x) > 1 -> um ou mais loops.
Graph(x,y) = 0 -> aresta inexistente
Graph(x,y) > 0 -> uma ou mais arestas ligando o vertice x -> y.
* Para grafos simples valor de Graph(x,x) = 0 || 1, Graph(x,y) = 0 || 1.
* Para grafos não direcionados Graph(x,y) == Graph(y,x).
*/
class Graph{
private:
    bool simple;           // tipo definido apenas pelo construtor, não é admitida alteração.
    bool directed;
    int v_max;            // é permitida a ampliação do grafo, com custo de cópia. 
    int n_vertices;       // número de vértices 
    int** matrix;         // matriz representativa do grafo.

    /*
    init - Função de Inicialização do Objeto
    @param  size: número máximo de vértices
            simple: grafo simples ou multigrafo
            directed: grafo direcionado ou não-direcionado
    */
    void init(int size, bool simple, bool directed){
        this->simple = simple;
        this->directed = directed;
        v_max = size;
        n_vertices = 0;

        //alocação de memória para a matriz
        matrix = new int*[v_max];
        for(int i=0; i<v_max; i++){
            matrix[i] =  new int[v_max];
        }

        //inicialização da matriz vazia
        for(int i=0; i<v_max; i++){
            for(int j=0; j<v_max; j++){
                matrix[i][j]=0;
            }
        }
    }
public:
    /*
    Constructors
    */
    //Construtor completo
    Graph(int size, bool simple, bool directed){
        init(size, simple, directed);
    }
    //Construtor grafo simples, não-direcionado 
    Graph(int size){
        init(size, true, false);
    }
    //Construtor grafo tamnho 5, simples, não-direcionado
    Graph(){
        init(5, true, false);
    }

    //Destructor
    ~Graph(){
        for(int i=0; i<v_max; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    
    //Methods
    /*
    print - mostra a matriz
    */
    void print(){
        if(isSimple()){
            cout << endl << "Grafo Simples ";
        }
        else{
            cout << "Multigrafo "; 
        }
        if(isDirected()){
            cout << "Direcionado" << endl;
        }
        else{
            cout << "Não-Direcionado" << endl;
        }
        cout << "  || ";
        for(int i=0; i<v_max-1; i++){
            cout << i << " | ";
        }
        cout << (v_max-1) << endl;
        cout << "- - - ";
        for(int i=0; i<v_max-1; i++){
            cout << "- - ";
        }
        cout << "-" << endl;
        for (int i=0; i<v_max; i++){
            cout << i << " || ";
            for(int j=0; j<v_max-1; j++){
                cout << matrix[i][j] << " | ";
            }
            cout << matrix[i][v_max-1] << endl;
        }
    }

    /*
    isDirected - informa se o grafo é direcionado
    @return verdadeiro se direcionado, falso se não-direcionado
    */
    bool isDirected(){
        return directed;
    }

    /*
    isSimple - informa se o grafo é simples
    @return verdadeiro se simples, falso se multigrafo
    */
    bool isSimple(){
        return simple;
    }
    /*
    isFull - informa se a matriz está cheia
    @return verdadeiro se cheia, falso se não
    */
    bool isFull(){
       return (v_max == n_vertices);
    }

    /*
    nVertices - informa o número de vértices do grafo
    @return número de vértices
    */
    int nVertices(){
        return n_vertices;
    }

    /*
    nMax - informa o número máximo de vértices do grafo
    @return número máximo de vértices
    */
    int nMax(){
        return v_max;
    }

    /*
    addVertex - inclui um vértice no grafo
    @return índice do vértice || -1 se cheio 
    */
    int addVertex(){
        int i=-1;
        if(!isFull()){
            i++;
            while(matrix[i][i]!=0){
                i++;
            }
            matrix[i][i] = 1;
            n_vertices++;
        }
        return i;
    }

    /*removeVertex - remove um vértice e todas arestas incidentes
    @param índice do vértice
    @return -1 se vértice inexistente ou número de arestas excluídas com o vértice
    */
    int removeVertex(int vertex){
        int i=0;
        if(matrix[vertex][vertex]!=0){
            for(int j=0; j<v_max; j++){
                i+=matrix[vertex][j];
                matrix[vertex][j] = 0;
                i+=matrix[j][vertex];
                matrix[j][vertex] = 0;
            }
            n_vertices--;
        }
        return i-1;
    }
    /*
    addEdge - acrescenta uma aresta
    Se simples, apenas se v1!=v2 && matrix(v1,v2)==0
    Se não-direcionado matrix(v1,v2)=matrix(v2,v1)
    @param vértice 1 e vértice 2
    @return -1 para falha, >=1 número de arestas
    * para loop, o número de arestas = n-1 -> 1 indica a existência do vértice
    */
    int addEdge(int v1, int v2){
        int n = 0;
        
        //verificar se os vértices existem
        if(matrix[v1][v1]!=0 && matrix[v2][v2]!=0){
            
            //Grafo Simples
            if(isSimple()){
                if(v1!=v2 && matrix[v1][v2]==0){
                    matrix[v1][v2]=1;
                    n = 1;
                }    
            }
            //Multigrafo
            else{
                n = ++matrix[v1][v2];
            }
            //Grafo Não-Direcionado
            if(n!=0 && !isDirected()){
                matrix[v2][v1]++;
            }
        }
        if(v1==v2){
            n--;
        }
        return n;
    }

    /*
    removeEdge - remove uma aresta
    @param vértice 1, vértice 2
    @return -1 para falha || >=0 número de arestas restantes
    * 
    */
    int removeEdge (int v1, int v2){
        int n = -1;
        
        //verificar se os vértices existem
        if(matrix[v1][v1]!=0 && matrix[v2][v2]!=0){
            
            //Grafo Simples
            if(isSimple()){
                if(v1!=v2 && matrix[v1][v2]==1){
                    matrix[v1][v2]=0;
                    n = 1;
                }    
            }
            //Multigrafo
            else if(v1==v2 && matrix[v1][v2]>=2){
                n = --matrix[v1][v2];
            }
            else if(v1!=v2 && matrix[v1][v2]>=1){
                n = --matrix[v1][v2];
            }
            //Grafo Não-Direcionado
            if(n!=-1 && !isDirected()){
                matrix[v2][v1]--;
            }
        }
        return n;
    } 
};

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
            while (value_matrix[v1][v2][index] == 0x8000000){
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

/*
Main - Main Function
*/
int main(){
    Valued_Graph grafo = Valued_Graph(5, false, true, 2);
    grafo.print();
    
}
