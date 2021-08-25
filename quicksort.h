/*
Projeto e Análise de Algoritmos
Nome: Guilherme Aguilar de Oliveira
RA: 2127954

Nome: Heitor Derder Trevisol
RA: 1611810

Nome: Diego Mamprim Borges
RA: 1937537

Descrição do arquivo: 
Algoritmo para ordenação via Quick Sort e Função para busca binária
*/
#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED

#include "stdafx.h"
#include "Pontos.h"


/* Função troca
Entradas: Um vetor de pontos e duas posiçoes nesse vetor.
Saída: O vetor de pontos com os pontos nas posições específicadas trocados.
Descrição: Inverte os 2 pontos específicados de posição no vetor.
Complexidade: O(1) pois só precisa acessar o vetor nos pontos específicos.
Comentários: É utilizado um ponto auxiliar para poder fazer a inversão sem problemas de perda de dados.
*/
void troca(Pontos p, int i, int j);

/* Função particiona
Entradas: Um vetor de pontos e dois extremos esquerda e direita.
Saída: O vetor de pontos reordenado dentro do intervalo [esq,dir] e um valor para o pivo que será utilizado pela função quicksort.
Descrição: A função irá percorrer o vetor dentro do intervalo definido pelas entradas procurando pontos no vetor que sejam 
menores ou iguais ao ponto na posição extrema a direita do intervalo.
Complexidade: O(n) em sua primeira execução (chamada pela função quicksort) ele irá percorrer todo o vetor 1 vez.
Comentários: Após a primeira execução as demais execuções iram todas ser mais curtas.
*/
int particiona(Pontos p, int esq, int dir);

/* Função quicksort
Entradas: Um vetor de pontos e dois extremos esquerda e direita.
Saída: O vetor de pontos ordenado.
Descrição: Enquanto as entradas de esquerda e direita validam a condição (esquerda < direita) a função irá utilizar a funçãoo particiona
para definir um valor (pivo) que será utilizado para chamar a função quicksort recursivamente para os 2 intervalos do extremo da esquerda até o pivo
e do pivo até o extremo da direita.
Complexidade: O(n*log n) devido a complexidade da função partição em O(n) e O(log n) vezes em que será chamada a função particiona.
*/
void quicksort(Pontos p, int esq, int dir);

/* Função busca_binaria
Entradas: Um vetor de pontos, um ponto a ser buscado e dois extremos esquerda e direita.
Saída: 0 no caso de o ponto não existir no vetor buscado, e 1 no caso de existir.
Descrição: A busca irá comparar (utilizando a funçao compara_pontos) o ponto buscado com o ponto contido no meio do vetor ordenado (vetor), 
e no caso de não ser o ponto esperado irá continuar a procurar no resto do vetor.
Complexidade: O(log n) eu seu pior caso, onde irá percorrer log n posições no vetor até achar o ponto sendo buscado.
Comentários: Para decidir a metade certa para continuar a busca é utilizado o resultado da função compara_pontos.
*/
int busca_binaria(Pontos vetor, Ponto p, int esq, int dir);

#endif
