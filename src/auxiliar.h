//
// Created by pierr on 20/11/2019.
//
#include "estruturas.h"
#ifndef DISCRETAPGR_AUXILIAR_H
#define DISCRETAPGR_AUXILIAR_H
int ** Aloca(int lin, int col);
float* normalizaVetor(float* vetor, int numero_vertices);
static int cmp(const void *p1, const void *p2);
int myStrCmp(const void *s1, const void *s2);
Vertice* ordenaBubbleSort(Vertice *vertice, int tamanho);
void imprimeTopKPageRank(Grafo *grafo,int k);
void obtemVertices(Grafo* grafo,char arquivo[]);
void criaMatrizAdjacencia(Grafo *grafo,char arquivo[]);
#endif //DISCRETAPGR_AUXILIAR_H
