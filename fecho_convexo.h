/*
Projeto e Análise de Algoritmos
Nome: Guilherme Aguilar de Oliveira
RA: 2127954

Nome: Heitor Derder Trevisol
RA: 1611810

Descrição do arquivo: 
Arquivo que contém algoritmo fecho convexo.
*/

#ifndef FECHO_CONVEXO_H_INCLUDED
#define FECHO_CONVEXO_H_INCLUDED

#include "stdafx.h"
#include "Pontos.h"

/* Função procura_pontos_extremos
Entradas: um vetor de pontos e dois pontos
Saídas: dois pontos extremos, um com o maior x e outro com o menor x
Descrição: procura e retorna os dois pontos mais distantes no eixo x
Complexidade: O(n) pois é preciso ler o vetor de pontos p inteiro uma vez
Comentários: caso houver empate procura o pontos com menor x e y e com maior x e y
*/
void procura_pontos_extremos(Pontos p, Ponto *maior, Ponto *menor);

/* Função distancia_reta_ponto
Entradas: três pontos
Saídas: a distancia entre a reta formada pelo vetor p1p2 do ponto p3
Descrição: calcula a distancia da reta p1p2 do ponto p3
Complexidade: O(1) pois não há laços, somente instruções simples
Comentários:
*/ 
double distancia_reta_ponto(Ponto p1, Ponto p2, Ponto p3);

/* Função area_paralelogramo
Entradas: três pontos
Saídas: a area do paralelogramo formado pelos vetores p1p2 e p1p3
Descrição: calcula a area do paralelogramo formado pelos vetores p1p2 e p1p3
Complexidade: O(1) pois não há laços, somente instruções simples
Comentários: foi preciso utilizar long long int pois os números estouravam o tamanho do int
*/ 
long long int area_paralelogramo(Ponto p1, Ponto p2, Ponto p3);

/* Função mais_distante_reta_esq
Entradas: vetor de pontos possiveis a esquerda da reta pq, vetor do fecho, dois pontos do fecho p e q
Saídas: retorna metade do fecho completo, todos os pontos a esquerda da reta dos primeiros pontos extremos
Descrição: escolhe o ponto mais distante da reta pq a esquerda 
e faz mais duas retas com este até não sobrar mais pontos a esquerda.
Complexidade: O(n^2) (Ordem de n ao quadrado), 
pois no pior caso o algoritmo irá verificar n-2 pontos possíveis a esquerda de pq a cada chamada da função.
Dessa forma com n-2 pontos possíveis a função irá ser chamada em ordem de n vezes.
Comentários: Foi preciso adaptar o algoritmo para adicionar os pontos no fecho no sentido anti-horario.
Também, se fez necessário haver duas funções adicionar todos os pontos do fecho, 
uma função que adiciona ao fecho os pontos a esquerda da reta pq e outra a direita da reta pq. 
*/ 
void mais_distante_reta_esq(Pontos* vetor, Pontos* fecho, Ponto p, Ponto q);

/* Função mais_distante_reta_dir
Entradas: vetor de pontos possiveis a direita da reta pq, vetor do fecho, dois pontos do fecho p e q
Saídas: retorna metade do fecho completo, todos os pontos a direita da reta dos primeiros pontos extremos
Descrição: escolhe o ponto mais distante da reta pq a direita 
e faz mais duas retas com este até não sobrar mais pontos a direita
Complexidade: O(n^2) (Ordem de n ao quadrado), 
pois no pior caso o algoritmo irá verificar n-2 pontos possíveis a direita de pq a cada chamada da função.
Dessa forma com n-2 pontos possíveis a função irá ser chamada em ordem de n vezes.
Comentários: Foi preciso adaptar o algoritmo para adicionar os pontos no fecho no sentido anti-horario.
Também, se fez necessário haver duas funções adicionar todos os pontos do fecho, 
uma função que adiciona ao fecho os pontos a esquerda da reta pq e outra a direita da reta pq. 
*/ 
void mais_distante_reta_dir(Pontos* vetor, Pontos* fecho, Ponto p, Ponto q);

/* Função fecho convexo
Entradas: um vetor de pontos
Saídas: o fecho convexo desse vetor de pontos
Descrição: calcula o fecho convexo dos pontos na seguinte sequencia,
calcula os primeiros dois pontos extremos,
calcula o fecho a esquerda da reta dos dois pontos extremos, 
depois calcula a direita da reta dos dois pontos extremos.
Complexidade: O(n^2) (Ordem de n ao quadrado), 
pois no pior caso o algoritmo chama duas funções com complexidade O(n^2) e uma função com O(n)
Comentários: Para n=1 foi necessário fazer uma excessão para a função apenas retornasse o fecho com o único ponto.
A ordem da inserção dos primeiros pontos extremos no fecho teve que ser adaptada 
para inserir no sentido anti-horário.
*/ 
Pontos fecho_convexo(Pontos entrada);

#endif