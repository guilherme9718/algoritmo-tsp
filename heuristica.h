/*
Projeto e Análise de Algoritmos
Nome: Guilherme Aguilar de Oliveira
RA: 2127954

Nome: Heitor Derder Trevisol
RA: 1611810

Descrição do arquivo: 
Algoritmo de aproximação do caixeiro viajante
*/
#ifndef HEURISTICA_H_INCLUDED
#define HEURISTICA_H_INCLUDED

#include "stdafx.h"
#include "Pontos.h"
#include "fecho_convexo.h"
#include "quicksort.h"

/* Função Heuristica
Entradas: vetor de pontos

Saídas: retorna um vetor de Pontos que formam um ciclo hamiltomiano 
com valores próximos do menor ciclo hamiltomiano possível

Descrição: Primeiro, calcula o fecho convexo dos pontos da entrada. 
Logo em seguida, faz a subtração de conjuntos do vetor da entrada com o vetor do fecho 
gerando pontos internos ao fecho. Após gerado o vetor de pontos internos, converte os vetores fecho e 
p_interno em listas para diminuir a complexidade de inserções. Por fim calcula o ciclo hamiltoniano
fazendo inserções mínimas do vetor p_interno no vetor fecho.

Complexidade: O(n^2) (Ordem de n ao quadrado), 
pois além da subtração de conjuntos que custa O(log n), o mais custoso no algoritmo consiste em calcular
as menores inserções o que levaria O(n^3), porém como valores já são calculados são salvos em uma matriz
a só é preciso calcular o menor custo de uma tupla de pontos a cada repetição.
Custo de memória: O(n^2)

Comentários: Para diminuir a complexidade de tempo de O(n^3) para O(n^2) foi 
preciso duas matrizes de tamanho nxn  e um vetor de tamanho n.
*/ 
Pontos heuristica(Pontos entrada);

/* Função distância pontos
Entradas: dois pontos p1 e p2
Saídas: retorna em inteiro o teto da distancia euclidiana entre os dois pontos

Descrição: calcula a distância euclidiana entre p1 e p2, por fim aplica a função teto e retorna um inteiro

Complexidade: O(1) pois não há laços.

Comentários: Para não gastar muito espaço em memória já que teria que salvar uma matriz nxn de distancias,
fez-se uma aproximação da distância convertendo em inteiro.
*/ 
long long int distancia_ponto(Ponto p1, Ponto p2);

/* Função fator_pontos
Entradas: três pontos p1, p2 e p3
Saídas: retorna um custo de inserção de p3 entre p1 e p2

Descrição: calcula o custo de inserir p3 entre p1 e p2. Isse custo é dado por:
a distância de p1 e p3 adicionado a distância de p2 e p3 subtraido a distância de p1 e p2

Complexidade: O(1) pois não há laços.

Comentários: Para não gastar muito espaço em memória já que teria que salvar uma matriz nxn de distancias,
fez-se uma aproximação da distância convertendo em inteiro.
*/ 
long long int fator_pontos(Ponto p1, Ponto p2, Ponto p3);

/* Função calcula_heurística
Entradas: uma lista de pontos do fecho convexo e uma lista de pontos p_interno dentro do fecho convexo

Saídas: retorna uma lista de Pontos que formam um ciclo hamiltomiano 
com valores próximos do menor ciclo hamiltomiano possível

Descrição: Para cada dupla de pontos no fecho, calcula qual é o ponto na lista p_interno que tem o menor
custo de inserção e salva esse custo na matriz de custo e o ponto a ser inserido na matriz m_ponto. 
Antes de calcular a menor inserção, verifica se já foi calculado a menor inserção nas matrizes de custo e
m_ponto, se sim, verifica se o ponto em questão já foi adicionado ao fecho no vetor de pontos sujo.
Repete o algoritmo acima até adicionar todos os pontos de p_interno no fecho.  

Complexidade: O(n^2) (Ordem de n ao quadrado), 
O algoritmo leva O(n) para calcular a menor inserção de uma dupla de pontos do fecho, 
repetido para todas as duplas de pontos no fecho o algoritmo leva O(n^2) 
porém como é salvo os custos da menor inserção, só é preciso calcular uma vez a cada iteração
então para todas a duplas de pontos o algoritmo leva O(n). Já para repetir o laço até
não restar pontos internos, leva O(n^2).
Custo de memória: O(n^2) pois os custos são salvos em uma matriz

Comentários: Para diminuir a complexidade de tempo de O(n^3) para O(n^2) foi 
preciso duas matrizes de tamanho nxn  e um vetor de tamanho n.
*/
void calcula_heuristica(lista_pontos* fecho, lista_pontos* entrada);

/* Função calcula_minimo
Entradas: uma lista de pontos do fecho convexo e uma lista de pontos p_interno dentro do fecho convexo
e um ponto p na lista do fecho

Saídas: retorna o ponto na entrada com a menor inserção entre o ponto p e o ponto anterior a p.

Descrição: O ponto p, tem na estrutura de dados o ponto imediatamente anterior na lista, dessa forma
dado esses dois pontos, verifica se já foi calculado a menor inserção, se sim, retorna a menor inserção
pela matriz m_ponto, se não ou se o valor já calculado é inválido, é calculado a menor inserção e armazena
nas matrizes.  

Complexidade: O(n), 
O algoritmo no pior caso calcula o custo percorrendo todos os pontos da entrada que não estão no fecho

Comentários: Ocorrem mais frequentemente o algoritmo rodar em O(1) pois só retorna o ponto já calculado.
*/
No* calcula_minimo(lista_pontos* fecho, lista_pontos* entrada, No* p);

/* Função aloca_matriz
Entradas: dois inteiros tam e num
Saídas: retorna uma matriz de tamanho tam e preechida com num

Descrição: aloca uma matriz de tamanho tam e preechida com num.

Complexidade: O(n^2) pois é preciso alocar e preencher a matriz.

Comentários: 
*/ 
int** aloca_matriz(int tam, int num);

#endif