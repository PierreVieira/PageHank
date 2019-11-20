//
// Created by pierr on 20/11/2019.
//

#ifndef DISCRETAPGR_ESTRUTURAS_H
#define DISCRETAPGR_ESTRUTURAS_H
typedef struct{
    char *nome;
    float score;
}Vertice;

typedef struct{
    Vertice* vertices;
    int tamanho;
    int ** matrizadj;
}Grafo;
#endif //DISCRETAPGR_ESTRUTURAS_H
