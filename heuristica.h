/*
Projeto e Análise de Algoritmos
Nome: Guilherme Aguilar de Oliveira
RA: 2127954

Descrição do arquivo: 
Algoritmo de aproximação do caixeiro viajante
*/

#include "stdafx.h"
#include "Pontos.h"
#include "fecho_convexo.h"

Pontos heuristica(Pontos entrada);

long long int distancia_ponto(Ponto p1, Ponto p2);

long long int fator_pontos(Ponto p1, Ponto p2, Ponto p3);

void calcula_heuristica(Pontos* fecho, Pontos* entrada);