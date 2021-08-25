/*
Projeto e Análise de Algoritmos
Nome: Guilherme Aguilar de Oliveira
RA: 2127954

Nome: Heitor Derder Trevisol
RA: 1611810

Nome: Diego Mamprim Borges
RA: 1937537

Descrição do arquivo: 
Arquivo lê os pontos, executa o algoritmo e escreve o fecho em fecho.txt
*/

#include "stdafx.h"
#include "Pontos.h"
#include "heuristica.h"
#include "quicksort.h"

int main (int argc, char* argv[]) {

    if(argc != 2) {
        printf("erro: passe somente 1 argumento");
        return 1;
    }

    Pontos p = le_pontos(argv[1]);

    //começa contar o tempo a partir daqui
    clock_t begin = clock();

    Pontos fecho = heuristica(p);
    
     //termina de contar o tempo
    clock_t end = clock();

    //calcula o tempo gasto
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%.6lf ", time_spent);

    //calcula o custo do algoritmo
    double d1=0, d_aux;
    Ponto p1_aux, p2_aux;
    for(int i=1; i < fecho.n; i++) {
        p1_aux = fecho.v[i-1];
        p2_aux = fecho.v[i];
        d1 += sqrt(pow(p1_aux.x - p2_aux.x, 2) + pow(p1_aux.y - p2_aux.y, 2));
    }
    printf("%.6lf\n", d1);

    //grava os pontos no arquivo fecho.txt
    grava_pontos(fecho, "ciclo.txt");

    return 0;
}