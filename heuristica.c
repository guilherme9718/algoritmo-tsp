#include "heuristica.h"

Pontos heuristica(Pontos entrada) {
    Pontos fecho, vetor_aux;
    fecho = fecho_convexo(entrada);
    int i;
    	
    vetor_aux.v = (Ponto*)malloc(sizeof(Ponto)*fecho.n);
    vetor_aux.n = 0;
	for (i = 0; i < fecho.n; i++){
		adiciona_ponto(&vetor_aux, fecho.v[i]);
	}
    Pontos p_interno;
    int tam_interno = entrada.n - fecho.n;

    if(tam_interno == 0) {
        return fecho;
    }

    p_interno.v = malloc(sizeof(Ponto)*tam_interno);
    p_interno.n = 0;
    
    //Fazer uma função para ordenar os pontos para melhorar a complexidade dessa atribuição
    quicksort(vetor_aux, 0, vetor_aux.n-1);
    

    //complexidade O(n^2) = RUIM
    //int i, j, flag;
    //printf("%d %d\n", entrada.n, fecho.n);
    /*for(i = 0; i < entrada.n; i++) {
        flag = 1;
        for(j = 0; j < teste.n; j++) {
            int cmp = compara_pontos(entrada.v[i], teste.v[j]);
            //printf("%d %d - %d %d = %d\n", entrada.v[i].x, entrada.v[i].y, fecho.v[j].x, fecho.v[j].y, cmp);
            //se os pontos são diferentes
            if(!cmp) {
                flag=0;
                break;
            }
        }
        if(flag) {
            adiciona_ponto(&p_interno, entrada.v[i]);
        }
    }*/
    
    for(i = 0; i < entrada.n; i++) {  
    	if(busca_binaria(vetor_aux, entrada.v[i], 0, vetor_aux.n - 1))
 		adiciona_ponto(&p_interno, entrada.v[i]);
    }


    lista_pontos* lista_fecho, *lista_interno;
    lista_fecho = converte_lista(fecho);
    lista_interno = converte_lista(p_interno);

    //imprime_lista(lista_interno);
    //_imprime_pontos(p_interno);

    lista_pontos* aux = converte_lista(fecho);
    Ponto p1;
    p1.x = 2; p1.y = 3;
    insere_no_depois(aux->inicio, aloca_no(p1));
    //imprime_lista(aux);
    calcula_heuristica(lista_fecho, lista_interno);

    free(fecho.v);

    fecho = converte_vetor(lista_fecho);
    //imprime_lista(lista_fecho);
    //_imprime_pontos(fecho);

    //desaloca_lista(lista_fecho);
    //desaloca_lista(lista_interno);
    //free(p_interno.v);

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

void calcula_heuristica(lista_pontos* fecho, lista_pontos* entrada) {
    if(entrada->tam == 0 || fecho->tam < 3) {
        return;
    }
    int x, n = entrada->tam;
    for(x = 0; x < n; x++) {
    long long int menor_d = fator_pontos(fecho->inicio->p, fecho->inicio->prox->p, entrada->inicio->p);
    
    No* iter1=fecho->inicio->prox, *iter2;
    No* p1=fecho->inicio, *p2=entrada->inicio;

    while(iter1 != NULL) {
        iter2 = entrada->inicio;
        while(iter2!= NULL) {
            long long int fator = fator_pontos(iter1->ant->p, iter1->p, iter2->p);
            if(fator < menor_d) {
                menor_d = fator;
                p1 =  iter1->ant;
                p2 = iter2;
            }
            iter2 = iter2->prox;
        }
        iter1 = iter1->prox;
    }

    //imprime_lista(fecho);
    //_imprime_ponto(p1->p);
    _imprime_ponto(p2->p);
    fecho->tam++;
    insere_no_depois(p1, aloca_no(p2->p));
    retira_no(p2, entrada);
    
    imprime_lista(entrada);
    }

    //calcula_heuristica(fecho, entrada);
}
