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
        printf("%d %d\n", p.v[i].x, p.v[i].y);
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