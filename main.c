#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "src/estruturas.h"
#include "src/auxiliar.h"

int *getVetorOutdegree(Grafo *grafo){
    /* Gera, para cada vértice, o seu grau de saída
    (ou seja, o número de arestas adjacentes).
    Armazena todos no vetor out_degree.
    Em que out_degree[v] é o grau de saída do
    vértice v. */
    int *out_degree;
    out_degree = malloc(sizeof(int)*grafo->tamanho);
    int saida=0;
    for(int i=0; i<grafo->tamanho; i++){
        for(int j=0; j<grafo->tamanho; j++){
            if(grafo->matrizadj[i][j] == 1){
                saida++; //conta quantas ocorrencias saídas do vertices
            }
        }
        out_degree[i] = saida;
        saida=0;
    }

//    for(int i = 0; i<grafo->tamanho; i++){
//        printf("i: %d : %d\n",i,out_degree[i]);
//    }
    return out_degree;
}

float CalculaPageRankVertice(Grafo *grafo, const float *page_rank, const int *out_degree, int vertice,float dumping_factor){
    /*  Calcula a partir do grafo o page rank
    do vértice passado como parametro.
    Também são parametros:
    page_rank[u]: o PageRank (anterior) do vértice u.
    out_degree[u]: o grau de saída do vértice u.
    dumping_factor: dumping factor a ser usado.ce */
    int i;
    float pageRank=0;

    for(i=0; i<grafo->tamanho; i++){
        if(grafo->matrizadj[i][vertice]==1){
            pageRank += page_rank[i]/(float)out_degree[i]; //Soma o pagerank de cada vértice e divide pelo out degre
        }
    }
    pageRank = pageRank*dumping_factor + (1-dumping_factor); //Multiplica a soma encontrada pelo dumping factor
    //printf("Page Rank vertice %d , soma: %f\n",vertice,pageRank);
    return pageRank;
}

void CalculaPageRank(Grafo *grafo, float dumping_factor){
    /* Função que irá calcular o Page Rank de todos os vértices
    com a partir do CalculaPageRankVertice e irá normalizar os
    resultados até atingirem a condição
    de parada somaDifPR <=0.1 */
    float *vetorPR;
    float *vetorPR_atual;
    vetorPR = malloc(sizeof(int)*grafo->tamanho);

    vetorPR_atual = malloc(sizeof(int)*grafo->tamanho);

    int *out_degree;
    out_degree = getVetorOutdegree(grafo);

    for(int i = 0;i<grafo->tamanho;i++){
        vetorPR[i] = 1-dumping_factor; //inicializa o vetor
    }
    float somaDifPR = 0;

    do{
        for(int vertice = 0 ;vertice<grafo->tamanho;vertice++) {//para cada vertice associado a linha analisada..
            vetorPR_atual[vertice] = CalculaPageRankVertice(grafo,vetorPR,out_degree,vertice,dumping_factor);
        }
        vetorPR_atual = normalizaVetor(vetorPR_atual,grafo->tamanho);
        somaDifPR =0;
        for(int vertice = 0; vertice < grafo->tamanho; vertice++){
            somaDifPR += fabsf(vetorPR_atual[vertice] - vetorPR[vertice]);
            vetorPR[vertice] = vetorPR_atual[vertice];
        }
    }while(somaDifPR >=0.1);

    for(int i = 0; i<grafo->tamanho; i++){
        grafo->vertices[i].score = vetorPR[i];
    }
//    for(int i = 0; i<grafo->tamanho; i++){
//        printf("Posicao i %d possui page rank de %f\n",i,grafo->vertices[i].score);
//    }
    free(vetorPR);
    free(vetorPR_atual);
    free(out_degree);
}

int main(){
    Grafo grafo;
    char arquivo[] = "text_files/brasileirao.txt";
    //char arquivo[] = "text_files/grafo.txt";
    obtemVertices(&grafo,arquivo);
    criaMatrizAdjacencia(&grafo,arquivo);

    /// Parte de teste destinada aos alunos
    /// Testa a getVetorOutdegree
    int *out_degree;
    out_degree = getVetorOutdegree(&grafo);

    ///Testa a CalculaPageRankVertice (você deverá descomentar a operação de obter o out-degree)
    float page_rank[] = {0.15f,0.15f,0.15f,0.15f};
    int vertice = 1;
    CalculaPageRankVertice(&grafo,page_rank,out_degree,vertice,0.85f);

    ///Testa o pageRank
    CalculaPageRank(&grafo,0.85f);
    imprimeTopKPageRank(&grafo,20);
}