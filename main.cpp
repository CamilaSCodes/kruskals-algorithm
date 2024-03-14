#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Definição da classe aresta
class aresta{
    int vertice;
    int vertice2;
    double peso;

public: // Modificador de acesso
    aresta(int vertice,int vertice2, double peso){ // Construtor
        this->vertice=vertice;
        this->vertice2=vertice2;
        this->peso=peso;
    }

    int retornar_vertice(){
        return vertice;
    }

    int retornar_vertice2(){
        return vertice2;
    }

    double retornar_peso(){
        return peso;
    }

    // Retorna o menor peso
    bool operator < (const aresta& aresta2) const{
        return (peso<aresta2.peso);
    }

};

// Definição da classe grafo
class grafo{
    int numero_vertices;
    vector<aresta> arestas;

public: // Modificador de acesso
    grafo(int numero_vertices){ // Construtor
        this->numero_vertices=numero_vertices;
    }

    // Cria a aresta e insere no vetor de arestas
    void adicionar_aresta(int vertice, int vertice2, double peso){
        aresta Aresta(vertice, vertice2, peso);
        arestas.push_back(Aresta);
    }

    // Encontra o subconjunto do elemento fornecido
    // Checa se dois elementos estão no mesmo subconjunto
    int achar_subconjunto(int subconjunto[], int i){
        if(subconjunto[i]==-1)
            return i;
        return achar_subconjunto(subconjunto, subconjunto[i]);
    }

    void algoritmo_kruskal(){
        // Cria memória para as árvores independentes
        int * subconjunto = (int*)malloc((numero_vertices+1) * sizeof(int));

        // Inicializa todas as árvores como -1
        memset(subconjunto, -1, sizeof(int)*(numero_vertices+1));

        // Percorre o vetor de arestas e ordena
        sort(arestas.begin(), arestas.end());

        // Vetor que recebe a MST
        vector<aresta> arvore_geradora_minima;

        // Percorre as arestas e verifica a existência de ciclos
        long long unsigned int i=0;
        while(i!=arestas.size()){

            int vertice=achar_subconjunto(subconjunto,arestas[i].retornar_vertice());
            int vertice2=achar_subconjunto(subconjunto,arestas[i].retornar_vertice2());
            if(vertice!=vertice2){
                // Insere os vértices na MST
                arvore_geradora_minima.push_back(arestas[i]);
                // Une os vértices
                int conjunto_vertice=achar_subconjunto(subconjunto,vertice);
                int conjunto_vertice2=achar_subconjunto(subconjunto,vertice2);
                subconjunto[conjunto_vertice]=conjunto_vertice2;
            }

            i++;
        }

        // Imprime a árvore gerada
        long long unsigned int j=0;
        //double peso=0;
        printf("%d \n",numero_vertices);
        while(j!=arvore_geradora_minima.size()){
            //peso=peso+arvore_geradora_minima[j].retornar_peso();
            printf("%d %d %.2f \n", arvore_geradora_minima[j].retornar_vertice(), arvore_geradora_minima[j].retornar_vertice2(),arvore_geradora_minima[j].retornar_peso());
            j++;
        }
       //printf("PESO: %f \n",peso);
    }
};

int main()
{
    /* Escrever o output do console em um arquivo
    freopen("out1.txt","w",stdout); */

    // Declaração de variáveis
    int total_vertices=0,v1,v2;
    double peso;
    string total_verticesc;

    // Abre o .txt do grafo fornecido como parâmetro
    ifstream file("grafo_W_1_1.txt");

    // Coleta o total de vértices na primeira linha do .txt e cria o grafo correspondente
    getline(file,total_verticesc);
    total_vertices=stoi(total_verticesc);
    grafo g(total_vertices);

    // Adiciona as arestas se não houver self-loop
     while(file >> v1 >> v2 >> peso){
        if(v1==v2){
            printf("Há um self-loop nesse grafo! \n");
            return 0;
        }
        else{
            g.adicionar_aresta(v1,v2,peso);
        }
    }

    // Chama o algoritmo de Kruskal
    g.algoritmo_kruskal();

    // Fecha o .txt
    file.close();
    return 0;
}
