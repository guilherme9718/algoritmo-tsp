/*
Projeto e Análise de Algoritmos
Nome: Guilherme Aguilar de Oliveira
RA: 2127954

Nome: Heitor Derder Trevisol
RA: 1611810

Descrição do arquivo: 
Algoritmo de aproximação do caixeiro viajante
*/
#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED

#include "stdafx.h"
#include "Pontos.h"

void troca(Pontos p, int i, int j);

int particiona(Pontos p, int esq, int dir);

void quicksort(Pontos p, int esq, int dir);

#endif