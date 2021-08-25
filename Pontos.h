/*
Projeto e Análise de Algoritmos
Nome: Guilherme Aguilar de Oliveira
RA: 2127954

Nome: Heitor Derder Trevisol
RA: 1611810

Descrição do arquivo: 
Arquivo para definir a estrutura de dados utilizada e suas funções auxiliares,
no caso o ponto em si e um vetor de pontos.
*/

#ifndef PONTOS_H_INCLUDED
#define PONTOS_H_INCLUDED

#include "stdafx.h"

/* Estrutura Ponto
Armazena as coordenadas x e y dos pontos
Usada na Estrutura vetor_pontos para armazenar um conjunto de pontos */
typedef struct ponto {
    int x;
    int y;
    int index;
} Ponto;

/* Estrutura Pontos
Armazena em um vetor dinamicamente alocado um conjunto de pontos
O vetor tem tamanho n 
Usada nas leitura e escrita de pontos nos arquivos e no algoritmo do fecho convexo */
typedef struct vetor_pontos {
    Ponto* v;
    int n;
} Pontos;

/* Estrutura no_lista
Armazena um nó da lista encadeada de pontos.
Usada no algoritmo tsp para inserir nos no meio com custo zero */
typedef struct no_lista {
    Ponto p;
    struct no_lista* prox;
    struct no_lista* ant;
} No;

/* Estrutura no_lista
Estrutura que contém a lista encadeada apontando para os nós do começo e do fim
Usada no algoritmo tsp para inserir nos no meio com custo zero */
typedef struct lista_pontos {
    No* inicio;
    No* fim;
    int tam;
} lista_pontos;

//imprime na tela o ponto p (usado somente para teste)
void _imprime_ponto(Ponto p);

//imprime na tela os pontos p (usado somente para teste)
void _imprime_pontos(Pontos p);

/* Função le_pontos
Entradas: uma string com o caminho do arquivo
Saídas: um vetor de pontos alocado na memória
Descrição: Lê um conjunto de pontos de um arquivo passado por parâmetro
Complexidade: O(n)
Comentários: 
*/
Pontos le_pontos(char* arquivo);

/* Função grava_pontos
Entradas: um vetor de pontos e uma string com o caminho do arquivo
Saídas: escreve no arquivo os pontos no vetor p
Descrição: grava um conjunto de pontos em um arquivo passado por parâmetro
Complexidade: O(n)
Comentários: 
*/
void grava_pontos(Pontos p, char* arquivo);

/* Função adiciona_ponto
Entradas: um vetor de pontos e um ponto
Saídas: 
Descrição: adiciona um ponto p no final do vetor fecho
Complexidade: O(1)
Comentários: 
*/
void adiciona_ponto(Pontos *fecho, Ponto p);

/* Função compara_pontos
Entradas: dois pontos
Saídas: 0 se os dois pontos são iguais, 1 se p1 > p2 e -1 se p1 < p2
Descrição: compara dois pontos e retorna se são iguais ou indica qual é o maior;
Complexidade: O(1)
Comentários: 
*/
int compara_pontos(Ponto p1, Ponto p2);

No* aloca_no(Ponto p);

No* insere_no_depois(No* lista, No* inserido);

No* insere_no_antes(No* lista, No* inserido);

void retira_no(No* no, lista_pontos* lista);

lista_pontos* converte_lista(Pontos p);

Pontos converte_vetor(lista_pontos* lista);

void desaloca_lista(lista_pontos* lista);

void imprime_lista(lista_pontos* lista);

#endif