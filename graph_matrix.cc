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
        cout << "   ||";
        for(int i=0; i<v_max-1; i++){
            printf("%2d |", i);
        }
        cout << (v_max-1) << endl;
        cout << "- - - -";
        for(int i=0; i<v_max-1; i++){
            cout << " - -";
        }
        cout << endl;
        for (int i=0; i<v_max; i++){
            printf("%2d ||", i);
            for(int j=0; j<v_max-1; j++){
                if(i==j)
                    printf("%2d*|", matrix[i][j]);
                else
                    printf("%2d |", matrix[i][j]);
            }
            cout << " ";
            cout << matrix[i][v_max-1];
            if(i==v_max-1)
                cout << "*" << endl;
            else
                cout << endl;
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
        
        //verificar valores validos
        if(v1>=v_max || v2>=v_max)
            return -1;
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