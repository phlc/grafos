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

Desafio 1
- Finding Bridges

Desafio 2 
- Printing Cycles
*/

//Dependencies
#include <iostream>

//Namespade
using namespace std;


//--------------------------------- Implementação do Grafo ----------------------------------------------------


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

    /*
    nEdges - informa o número de arestas do grafo
    @return número de arestas
    */
    int nEdges(){
        //valor indicativo de erro
        int n = -1;
        if(simple){
            n++;
            for(int i=0; i<v_max; i++){
                for(int j=i+1; j<v_max; j++)
                {
                    n+=matrix[i][j];
                }
            }
        }
        if(simple && directed){
            for(int i=0; i<v_max; i++){
                for(int j=i+1; j<v_max; j++)
                {
                    n+=matrix[j][i];
                }
            }
        }

        return n;
    }

    /* 
    isConnected - Verica se um grafo é conexo
    @return bool 
    */
    bool isConnected(){
        int nV1 = 0;
        int nV2 = 0;
        int v_init = 0;

        while(this->matrix[v_init][v_init] != 1){
            v_init++;
        }

        int* parents = this->deepFirstSearch(v_init);
        for(int i=0; i<v_max; i++){
            if(this->matrix[i][i]==1){
                nV1++;
            }
            if(parents[i] != -1){
                nV2++;
            }
        }
        return nV1==nV2;
    }

    /*
    isRegular - Verificar se o grafo é regular no grau d
    @param int d
    @return bool
    */
    bool isRegular(int d){
        bool answer = false;
        if(!this->isDirected()){
            answer = true;
            for(int i=0; i<this->v_max && answer; i++){
                if(this->matrix[i][i]==1){
                    int degree = 0;
                    for(int j=(i+1); i!=j; j=(j+1)%this->v_max){
                        degree += this->matrix[i][j];
                    }
                    if(degree!=d){
                        answer=false;
                    }
                }
            }
        }
        return answer;
    }
// ----------------------------------- Desafio Finding Bridges -------------------------------------------------

    /*
    findBridges - Encontra as pontes do grafo.
    @param - vértice de início
    @return - matrix "bridges" com as arestas pontes.
    bridges(x,y) =  0  -> aresta inexistente
    bridges(x,y) =  1  -> aresta ponte
    bridges(x,y) = -1  -> aresta não ponte
    */
    int** findBridges(int v){
        //Testar para vértice válido
        if(v>=v_max || matrix[v][v]==0)
            return NULL;
        
        //definitions
        int** bridges = new int*[v_max];
        for(int i=0; i<v_max; i++){
            bridges[i] = new int[v_max];
            //inicializar linha
            for(int j=0; j<v_max; j++){
                bridges[i][j] = 0;
            }
        }
        int parents[v_max];
        int visited[v_max];
        int discoveryTime[v_max];
        int time = 0;

        //inicializar arranhos
        for(int i=0; i<v_max; i++){
            parents[i]=visited[i]=discoveryTime[i]=-1;
        }

        //marcar v como visitado
        visited[v] = 1;

        //registrar discoveryTime de v
        discoveryTime[v] = time++;

        //registrar pai de v como ele mesmo -> vértice inicial
        parents[v] = v;

        //chamar findBridges recursivamente para todos os filhos
        for (int i=1; i<v_max; i++){
            int v_son = (v+i)%v_max; // todos menos ele próprio

            //verificar se aresta existe e se já não foi visitada
            if(matrix[v][v_son]!=0 && visited[v_son]!=1){
                //registrar v como pai de v_son - OBS: como v é vértice inicial !precisa verificar se v_son visitado
                parents[v_son] =  v;
                //chamar findBridges recursivamente
                findBridges(v_son, bridges, parents, visited, discoveryTime, time);
            }
        }

        //marcar as pontes
        for(int i=0; i<v_max; i++){
            for(int j=0; j<v_max; j++){
                if(i!=j && matrix[i][j]!=0 && bridges[i][j]==0){
                    bridges[i][j]=1;
                }
            }
        }
        return bridges;
    }

private:
    /*
    findBridges - Overload
    @param - vértice, edgeNode, parents[], visited[], discoveryTime[], &time 
    */
    void findBridges(int v, int** bridges, int parents[], int visited[], int discoveryTime[], int &time){
        //marcar v como visitado
        visited[v] = 1;

        //registrar discoveryTime de v
        discoveryTime[v] = time++;

        //chamar findBrigdes recursivamente para todos os filhos
        for (int i=1; i<v_max; i++){
            int v_son = (v+i)%v_max; // todos menos ele próprio

            //verificar se aresta exite
            if(matrix[v][v_son]!=0){
                //verificar se v_son não é pai de v
                if(parents[v]!=v_son){
                    //verificar se v_son já foi visitado
                    if(visited[v_son]!=1){
                        //registrar v como pai de v_son
                        parents[v_son] = v;
                        //chamar findBridges recursivamente
                        findBridges(v_son, bridges, parents, visited, discoveryTime, time);
                    }
                    //se já visitado
                    //verificar se tempo de entrada pai maior que filho
                    else if(discoveryTime[v]>discoveryTime[v_son]){
                        //voltar pela árvore até v_son marcando as arestas como não ponte
                        int son = v_son;
                        int parent = v;
                        do{
                            bridges[parent][son] = -1;
                            //implementação apenas para grafos simples
                            bridges[son][parent] = -1;
                            son = parent;
                            parent = parents[parent];
                        }while(son != v_son);
                    }
                } 
            }
        }
    } 


// --------------------------------------- Desafio Printing Cycles ------------------------------------------------
private:
    /*
    deepFirstSearch - Busca por um ou todos os vértices - Recusivo
    @param matriz de Adjacência, número de vértices, vértice de início, vértice procurado
    @return sinal de target encontrado
    */
    int deepFirstSearch(int** mAdj, int n_v, int v1, int v_target, int visited[], int* parents){
        //definições
        int signal = 0; //sinal de parada para v_target encontrado

        //caminhamento
        for (int i=1; i<n_v && signal==0; i++){
            int v2 = (v1+i)%n_v;
            if(mAdj[v1][v2]==1 && visited[v2]==0){
                visited[v2]=1;
                parents[v2]=v1;
                if(v2==v_target)
                    return 1;
                signal = deepFirstSearch(mAdj, n_v, v2, v_target, visited, parents);
            }
        }    
        return signal;
    }

    /*
    deepFirstSearch - Busca por um ou todos os vértices
    @param matriz de Adjacência, número de vértices, vértice de início, vértice procurado
    @return array de ancestralidade
    */
    int* deepFirstSearch (int** mAdj, int n_v, int v_init, int v_target){
        //definições
        int visited[n_v];
        int signal = 0; //sinal de parada para v_target encontrado
        int* parents = new int[n_v];
        
        //inicialização do arrranho de ancestralidade
        for(int i=0; i<n_v;i++){
            visited[i]=0;
            parents[i]=-1;
        }

        //vértice raiz
        parents[v_init] = v_init;
        visited[v_init] =  1;
        if(v_init == v_target) 
            signal = 1;
        
        //caminhamento
        for (int i=1; i<n_v && signal==0; i++){
            int v2 = (v_init+i)%n_v;
            if(mAdj[v_init][v2]==1 && visited[v2]==0){
                visited[v2]=1;
                parents[v2] = v_init;
                if(v2==v_target)
                    i=n_v;
                else
                   signal = deepFirstSearch(mAdj, n_v, v2, v_target, visited, parents);
            }
        }

        return parents;
    }

    /*
    deepFirstSearch - Overload - Passar por todo o grafo
    @param matriz de Adjacência, número de vértices, vértice de início.
    @return array de ancestralidade
    */
    int* deepFirstSearch (int** mAdj, int n_v, int v_init){
        return deepFirstSearch(mAdj, n_v, v_init, -1);
    }

public:
    /*
    deepFirstSearch - Overload - Chamada do Objeto
    @param vértice de início, vértice procurado.
    @return array de ancestralidade
    */
    int* deepFirstSearch (int v_init, int v_target){
        return deepFirstSearch(matrix, v_max, v_init, v_target);
    }

    /*
    deepFirstSearch - Overload - Chamada do Objeto - Passar por todo grafo
    @param vértice de início,.
    @return array de ancestralidade
    */
    int* deepFirstSearch (int v_init){
        return deepFirstSearch(matrix, v_max, v_init, -1);
    }


private:
    /*
    printMatrix - mostra a matriz - static para debug
    @param matriz, número de vértices
    */
    void printMatrix(int** m, int n){

    }

public:
    /*
    spanningTree - gera uma spanningtree do grafo
    @param vértice de início
    @return grafo representativo da árvore
    */
    Graph spanningTree(int v){
        //verificar se o vértice é válido
        if(v>=v_max || matrix[v][v] == 0)
            return NULL;

        //definições
        int** mAdj = new int*[v_max];
        Graph* sTree = new Graph(this->v_max);
        sTree->n_vertices = this->n_vertices;
        sTree->directed = this->directed;
        sTree->simple = true;

        //preencher a diagonal principal da matriz da spanningTree
        for(int i=0; i<v_max; i++){
            sTree->matrix[i][i] = this->matrix[i][i];
        }
        int* parents = deepFirstSearch(v);

        //preencher as arestas da matriz da spanningTree
        for(int i=0; i<v_max; i++){
            if(parents[i]!=i && parents[i]!=-1)
                sTree->matrix[i][parents[i]] = sTree->matrix[parents[i]][i] = 1;
        }
        return *sTree;
    }
private:
    /*
    toBinary - Preenche um arranjo com a representação binária de um número
    @param tamanho, arranjo, número
    */
    static void toBinary(int t, int arr[], int n){
        for (int i=0; i<t; i++){
            int remainder = n%2;
            n/=2;
            arr[i] = remainder;
        }
    }

    /*
    power - Calcula n elevado a e
    @param int n, int e
    @return int resultado
    */
    static int power(int n, int e){
        int result = 1;
        while(e>0){
            result*=n;
            e--;
        }
        return result;
    }

    /* xorGraph - Realiza a operação XOR entre cada posição das matrizes de dois grafos (objeto e parâmetro)
    @param Graph*
    @return Graph*
    */
    Graph* xorGraph(Graph* graph2){
        Graph* answer = new Graph(this->v_max);
        answer->n_vertices = this->n_vertices;
        for(int i=0; i<this->v_max; i++){
            for(int j=i+1; j<this->v_max; j++){
                if(this->matrix[i][j]!=graph2->matrix[i][j]){
                    answer->matrix[i][j] = 1;
                    answer->matrix[j][i] = 1;
                    answer->matrix[i][i] = 1;
                    answer->matrix[j][j] = 1;
                }
                else{
                    answer->matrix[i][j] = 0;
                    answer->matrix[j][i] = 0;
                }
            }
        }
        return answer;
    }

public:

    /*
    printCycles_walk - Mostra os ciclos encontrados no grafo
    * pressupõe todas posições de vértices na matriz de Adjacência são vértices válidos
    * implementação apenas para grafos simples - não direcionados
    */
    void printCycles(){
        //criar uma spanning tree a partir do grafo
        Graph sTree = spanningTree(0);

        //Arranjo de matrizes representativas dos grafos fundamentais
        int nFund = this->nEdges() - sTree.nEdges();
        int index = 0;
        Graph* fundGraphs[nFund];

        //Criar Grafos dos Ciclos Fundamentais a partir das Arestas nåo inclusas
        for(int i=0; i<v_max; i++){
            for(int j=i+1; j<v_max; j++){
                //aresta não inclusa na spanningTree
                if (this->matrix[i][j]!=sTree.matrix[i][j]){
                    //caminho até cada vértice
                    int* path_i = sTree.deepFirstSearch(0, i);
                    int* path_j = sTree.deepFirstSearch(0, j);

                    //Construir Grafo Ciclo
                    fundGraphs[index] = new Graph(this->v_max);
                    fundGraphs[index]->n_vertices = this->n_vertices;
                    fundGraphs[index]->directed = this->directed;
                    fundGraphs[index]->simple = true;

                    //aresta que gera o ciclo fundamental
                    fundGraphs[index]->matrix[i][j] = 1;
                    fundGraphs[index]->matrix[j][i] = 1;

                    for(int k=0; k<this->v_max; k++){
                        if(path_i[k]!=path_j[k]){
                            if(path_i[k]!= -1){
                                //arestas
                                fundGraphs[index]->matrix[path_i[k]][k] = 1;
                                fundGraphs[index]->matrix[k][path_i[k]] = 1;
                                //diagonal
                                fundGraphs[index]->matrix[k][k] = 1;
                                fundGraphs[index]->matrix[path_i[k]][path_i[k]]=1;
                            }
                            if(path_j[k]!= -1){
                                //arestas
                                fundGraphs[index]->matrix[path_j[k]][k] = 1;
                                fundGraphs[index]->matrix[k][path_j[k]] = 1;
                                //diagonal
                                fundGraphs[index]->matrix[k][k] = 1;
                                fundGraphs[index]->matrix[path_j[k]][path_j[k]]=1;
                            }
                        }
                    }
                    index++;
                }
            }
        }
        // Gerar todas combinações possíveis dos ciclos fundamentais
        int nComb =  power(2, nFund) -1; //numero de combinações (vazio excluído)
        int bin[nFund];
        int n = 0;
        for(int i=1; i<=nComb; i++){
            Graph* cycle = new Graph(this->v_max);
            toBinary(nFund, bin, i);
            for (int j=0; j<nFund; j++){
                if(bin[j]==1){
                    Graph* buffer = cycle;
                    cycle = cycle->xorGraph(fundGraphs[j]);
                    delete buffer;
                }
            }
            if(cycle->isConnected() && cycle->isRegular(2)){
                cout << endl << endl << i << endl;
                cycle->print();
                n++;
            }
            delete cycle;
        }
        cout << "Número de Ciclos: " << n << endl;
    }
};