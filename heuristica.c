#include "heuristica.h"

Pontos heuristica(Pontos entrada) {
    Pontos fecho = fecho_convexo(entrada);

    Pontos p_interno;
    p_interno.v = malloc(sizeof(Ponto)*fecho.n);
    
    //Fazer uma função para ordenar os pontos aqui

    //complexidade O(n^2) = RUIM
    int i, j;
    for(i = 0; i < entrada.n; i++) {
        for(j = 0; j < fecho.n; j++) {
            //se os pontos são diferentes
            if(compara_pontos(entrada.v[i], fecho.v[j]) ) {
                adiciona_ponto(&p_interno, entrada.v[i]);
                break;
            }
        }
    }

    calcula_heuristica(&fecho, &p_interno);

    free(p_interno.v);

    return fecho;
}

long long int distancia_ponto(Ponto p1, Ponto p2) {
    double d;
    d = pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);

    return (long long int)(d+0.5);
}

long long int fator_pontos(Ponto p1, Ponto p2, Ponto p3) {
    long long int d1, d2, d3;
    d1 = distancia_ponto(p1, p3);
    d2 = distancia_ponto(p3, p2);
    d3 = distancia_ponto(p1, p2);

    return (d1 + d2 - d3);
}

void calcula_heuristica(Pontos* fecho, Pontos* entrada) {
    if(entrada->n == 0 || fecho->n < 3) {
        return;
    }

    int i, j, p1=0, p2=0;

    long long int menor_d = fator_pontos(fecho->v[0], fecho->v[1], entrada->v[0]);
    //implementar esse algoritmo com uma lista encadeada
    for(i = 3; i < fecho->n; i++) {
        for(j = 0; j < entrada->n; j++) {
            long long int fator = fator_pontos(fecho->v[i-1], fecho->v[i], entrada->v[j]);
            if(fator < menor_d) {
                menor_d = fator;
                p1 = i-1;
                p2 = j;
            }
        }
    }

    adiciona_ponto(fecho, entrada->v[p2]);
    //remove_ponto(entrada, p2);

    calcula_heuristica(fecho, entrada);
}