/*
Projeto e Análise de Algoritmos
Nome: Guilherme Aguilar de Oliveira
RA: 2127954

Nome: Heitor Derder Trevisol
RA: 1611810

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
    //Pontos fecho = p;
    //termina de contar o tempo
    clock_t end = clock();

    //calcula o tempo gasto
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%.6lf\n", time_spent);

    //grava os pontos no arquivo fecho.txt
    grava_pontos(fecho, "fecho.txt");

    //desaloca vetores de pontos
    //free(p.v);
    //free(fecho.v);
    return 0;
}