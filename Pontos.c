#include "Pontos.h"

//imprime na tela o ponto p (usado somente para teste)
void _imprime_ponto(Ponto p) {
    printf("%d %d\n", p.x, p.y);
}

//imprime na tela os pontos p (usado somente para teste)
void _imprime_pontos(Pontos p) {
    int i;

    printf("%d\n", p.n);
    for(i = 0; i < p.n; i++) {
        printf("%d:%d %d\n", p.v[i].index, p.v[i].x, p.v[i].y);
    }
}

//Lê um conjunto de pontos de um arquivo passado por parâmetro
Pontos le_pontos(char* arquivo) {
    
    FILE* file = fopen(arquivo, "r");

    if(!file) {
        printf("erro ao ler arquivo");
        exit(0);
    }

    Pontos pontos;

    int tam, i;
    fscanf(file, "%d", &tam);

    pontos.n = tam;
    pontos.v = (Ponto*)malloc(sizeof(Ponto) * tam);

    for(i=0; i < tam; i++) {
        fscanf(file, "%d %d", &pontos.v[i].x, &pontos.v[i].y);
        pontos.v[i].index = i;
    }

    fclose(file);

    return pontos;
}

//grava pontos em um arquivo
void grava_pontos(Pontos p, char* arquivo) {
    
    FILE* file = fopen(arquivo, "w");

    for(int i=0; i < p.n; i++) {
        fprintf(file, "%d %d\n", p.v[i].x, p.v[i].y);
    }

    fclose(file);
}

//adciona ponto p um vetor de pontos
void adiciona_ponto(Pontos *fecho, Ponto p) {
    fecho->v[fecho->n] = p;
    fecho->n++;
}

//compara os pontos p1 e p2 
int compara_pontos(Ponto p1, Ponto p2) {
    if(p1.x == p2.x) {
        if(p1.y == p2.y) {
            return 0;
        }
        else if (p1.y > p2.y) {
            return 1;
        }
        else {
            return -1;
        }
    }
    else if(p1.x > p2.x) {
        return 1;
    }
    else {
        return -1;
    }
}

//aloca um no na memoria
No* aloca_no(Ponto p) {
    No* noh = (No*)malloc(sizeof(No));
    noh->ant = NULL;
    noh->prox = NULL;
    noh->p = p;
}

//insere o nó no final da lista
No* insere_no_depois(No* lista, No* inserido) {
    No* aux = NULL;

    aux = lista->prox;
    lista->prox = inserido;
    inserido->prox = aux;
    inserido->ant = lista;
    if(aux)
        aux->ant = inserido;

    return inserido;
}

//insere o nó no inicio da fila
No* insere_no_antes(No* lista, No* inserido) {
    No* aux = NULL;
    
    aux = lista->ant;
    lista->ant = inserido;
    inserido->ant = aux;
    inserido->prox = lista;

    return inserido;
}

//retira o nó da fila
void retira_no(No* no, lista_pontos* lista) {
    No* aux, *ativo_prox=NULL, *ativo_ant=NULL, *ativo=NULL;

    lista->tam--;

    if(no->prox) {
        aux = no->prox;
        aux->ant = no->ant;
        ativo = ativo_prox = no->prox;
    }
    if(no->ant) {
        aux = no->ant;
        aux->prox = no->prox;
        ativo = ativo_ant = no->ant;
    }

    if(no == lista->inicio) {
        if(!ativo_ant)
            lista->inicio = ativo;
        else
            lista->inicio = ativo_ant;
    }
    else if(no == lista->fim) {
        if(!ativo_prox)
            lista->fim = ativo;
        else
            lista->fim = ativo_prox;
    }
}


lista_pontos* converte_lista(Pontos p) {
    if(p.n < 1) {
        return NULL;
    }

    lista_pontos* lista;
    lista = (lista_pontos*)malloc(sizeof(lista_pontos));

    
    
    lista->tam = p.n;
    lista->inicio = aloca_no(p.v[0]);
    if(p.n == 1) {
        lista->fim = NULL;
        return lista;
    }
    lista->fim = aloca_no(p.v[p.n - 1]);

    int i;
    No* aux, *iter;
    iter = lista->inicio;
    for(i=1; i < p.n-1; i++) {
        aux = aloca_no(p.v[i]);
        iter->prox = aux;
        aux->ant = iter;
        iter = aux;
    }

    iter->prox = lista->fim;
    lista->fim->ant = iter;

    return lista;
}

Pontos converte_vetor(lista_pontos* lista) {
    No* iter = lista->inicio;

    Pontos vetor;
    vetor.v = (Ponto*)malloc(sizeof(Ponto)*lista->tam);
    vetor.n = lista->tam;
    
    int i=0;
    while(iter != NULL) {
        vetor.v[i] = iter->p;
        
        i++;
        iter = iter->prox;
    }

    return vetor;
}

void desaloca_lista(lista_pontos* lista) {
    No* iter=lista->inicio, *aux;

    while(iter != NULL) {
        aux = iter;
        iter = iter->prox;
        free(aux);
    }

    free(lista);
}

void imprime_lista(lista_pontos* lista) {
    No* iter=lista->inicio;

    printf("%d: [", lista->tam);
    while(iter != NULL) {
        printf("%d %d, ", iter->p.x, iter->p.y);
        iter = iter->prox;
    }
    printf("]\n");
}