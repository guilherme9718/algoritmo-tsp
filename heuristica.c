#include "heuristica.h"

long long int **custo;
No* **m_ponto;
char *sujo;

Pontos heuristica(Pontos entrada) {
    Pontos fecho, vetor_aux;
    fecho = fecho_convexo(entrada);
    int i, j;
    	
    custo = aloca_matriz(entrada.n, -1);
    //m_ponto = aloca_matriz(entrada.n, -1);

    int tam = entrada.n;
    No* **m = (No***)malloc(sizeof(No**)*tam);
    for(i=0; i < tam; i++) {
        m[i] = (No**)malloc(sizeof(No*)*tam);
        for(j = 0; j < tam; j++) {
            m[i][j] = NULL;
        }
    }
    m_ponto = m; 

    sujo = (char*)malloc(sizeof(char)*entrada.n);

    for(i=0; i < entrada.n; i++) {
        sujo[i] = 1;
    }

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
    
    
    for(i = 0; i < entrada.n; i++) {  
    	if(busca_binaria(vetor_aux, entrada.v[i], 0, vetor_aux.n - 1))
 		adiciona_ponto(&p_interno, entrada.v[i]);
    }

    int init;
    for(i=0; i < p_interno.n; i++) {
        p_interno.v[i].index = i;
        init=i;
    }
    for(i=0; i < fecho.n; i++) {
        init++;
        fecho.v[i].index = init;
    }

    lista_pontos* lista_fecho, *lista_interno;
    lista_fecho = converte_lista(fecho);
    lista_interno = converte_lista(p_interno);
    

    //imprime_lista(lista_fecho);
    //_imprime_pontos(fecho);

    //lista_pontos* aux = converte_lista(fecho);
    //Ponto p1;
    //p1.x = 2; p1.y = 3;
    //insere_no_depois(aux->inicio, aloca_no(p1));
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
    d = sqrt(d);
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
        
        //imprime_lista(fecho);

        No* iter1=fecho->inicio->prox, *iter2;
        No* p1=fecho->inicio, *p2=entrada->inicio;
        No* aux=entrada->inicio;
        long long int fator;
        while(iter1 != NULL) {
            iter2 = entrada->inicio;
            aux = calcula_minimo(fecho, entrada, iter1);
            fator = custo[iter1->ant->p.index][iter1->p.index];
            printf("%d %d %lld\n", iter1->ant->p.index, iter1->p.index, fator);
            
            if(fator < menor_d) {
                menor_d = fator;
                p1 = iter1->ant;
                p2 = aux;
            }
            iter1 = iter1->prox;
            /* while(iter2!= NULL) {
                long long int fator = fator_pontos(iter1->ant->p, iter1->p, iter2->p);
                if(fator < menor_d) {
                    menor_d = fator;
                    p1 =  iter1->ant;
                    p2 = iter2;
                }
                iter2 = iter2->prox;
            }
            iter1 = iter1->prox; */
        }

        //imprime_lista(fecho);
        //_imprime_ponto(p1->p);
        //_imprime_ponto(p2->p);
        fecho->tam++;
        sujo[p2->p.index] = 1;
        insere_no_depois(p1, aloca_no(p2->p));
        retira_no(p2, entrada);
        
        //imprime_lista(entrada);
    }

    //calcula_heuristica(fecho, entrada);
}

No* calcula_minimo(lista_pontos* fecho, lista_pontos* entrada, No* p) {
    int i1=p->ant->p.index, i2=p->p.index;
    No* aux = m_ponto[i1][i2];
    if(aux != NULL) {
        if((sujo[aux->p.index] == 0) && (custo[i1][i2] != -1)) {
            return aux;
        }
    }

    No* iter = entrada->inicio;
    No* p1=p->ant, *p2=p, *p3=entrada->inicio;
    long long int menor = fator_pontos(p->ant->p, p->p, entrada->inicio->p);
    while(iter != NULL) {
        long long int fator = fator_pontos(p->ant->p, p->p, iter->p);
        if(fator < menor) {
            menor = fator;
            p3 = iter;
        }
        iter = iter->prox;
    }
    
    custo[i1][i2] = menor;
    m_ponto[i1][i2] = p3;
    sujo[p3->p.index] = 0;

    return p3;
}

long long int** aloca_matriz(int tam, int num) {
    long long int i, j;
    long long int **m = (long long int**)malloc(sizeof(long long int*)*tam);
    for(i=0; i < tam; i++) {
        m[i] = (long long int*)malloc(sizeof(long long int)*tam);
        for(j = 0; j < tam; j++) {
            m[i][j] = (long long int)num;
        }
    }
    return m;
}

void desaloca_matriz(int **m, int tam) {

}