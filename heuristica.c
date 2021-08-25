#include "heuristica.h"
//#define TAM_ROTA

int **custo;
No* **m_ponto;
char *sujo;

Pontos heuristica(Pontos entrada) {
    Pontos fecho, vetor_aux;
    fecho = fecho_convexo(entrada);
    int i, j;
    	
    custo = aloca_matriz(entrada.n, -1);

    //Aloca matriz de ponteiros de No
    int tam = entrada.n;
    No* **m = (No***)malloc(sizeof(No**)*tam);
    for(i=0; i < tam; i++) {
        m[i] = (No**)malloc(sizeof(No*)*tam);
        for(j = 0; j < tam; j++) {
            m[i][j] = NULL;
        }
    }
    m_ponto = m; 

    //Aloca vetor para caso os pontos sejam modificados
    sujo = (char*)malloc(sizeof(char)*entrada.n);

    for(i=0; i < entrada.n; i++) {
        sujo[i] = 1;
    }

    //Cria um vetor auxiliar e copia os conteúdos do fecho nele
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
    
    quicksort(vetor_aux, 0, vetor_aux.n-1);
    
    //Faz subtração de conjuntos entrada - fecho
    for(i = 0; i < entrada.n; i++) {  
    	if(busca_binaria(vetor_aux, entrada.v[i], 0, vetor_aux.n - 1))
 		adiciona_ponto(&p_interno, entrada.v[i]);
    }

    //define indices para cada ponto para indexá-los nos vetores e matrizes para programação dinâmica
    int init;
    for(i=0; i < p_interno.n; i++) {
        p_interno.v[i].index = i;
        init=i;
    }
    for(i=0; i < fecho.n; i++) {
        init++;
        fecho.v[i].index = init;
    }

    //converte vetores em listas
    lista_pontos* lista_fecho, *lista_interno;
    lista_fecho = converte_lista(fecho);
    lista_interno = converte_lista(p_interno);
    
    //calcula o ciclo
    calcula_heuristica(lista_fecho, lista_interno);

	free(vetor_aux.v);
    free(fecho.v);

    fecho = converte_vetor(lista_fecho);
    Ponto primeiro = fecho.v[0];
    fecho.v[fecho.n-1] = primeiro;

    //Desaloca matrizes e vetores da programação dinâmica
    free(sujo);
    for(i=0; i < tam; i++){
        free(m_ponto[i]);
        free(custo[i]);
    }
    free(m_ponto);
    free(custo);

    //desaloca listas
    lista_fecho->tam--;
    desaloca_lista(lista_fecho);
    desaloca_lista(lista_interno);

    //Calcula o tamanho da rota
    #ifdef TAM_ROTA
    double d1=0, d_aux;
    Ponto p1_aux, p2_aux;
    for(i=1; i < fecho.n; i++) {
        p1_aux = fecho.v[i-1];
        p2_aux = fecho.v[i];
        d1 += sqrt(pow(p1_aux.x - p2_aux.x, 2) + pow(p1_aux.y - p2_aux.y, 2));
    }
    printf("tam da rota = %lf\n", d1);
    #endif

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
    No* p_aux = NULL;
    for(x = 0; x < n; x++) {
        long long int menor_d = fator_pontos(fecho->inicio->p, fecho->inicio->prox->p, entrada->inicio->p);

        No* iter1=fecho->inicio->prox, *iter2;
        No* p1=fecho->inicio, *p2=entrada->inicio;
        No* aux=entrada->inicio;
        long long int fator;
        while(iter1 != NULL) {
            iter2 = entrada->inicio;
            aux = calcula_minimo(fecho, entrada, iter1);
            fator = custo[iter1->ant->p.index][iter1->p.index];
            
            if(fator < menor_d) {
                menor_d = fator;
                p1 = iter1->ant;
                p2 = aux;
            }
            iter1 = iter1->prox;
        }

        fecho->tam++;
        sujo[p2->p.index] = 1;
        p_aux = aloca_no(p2->p);
        m_ponto[p1->p.index][p1->prox->p.index] = p_aux;
        insere_no_depois(p1, p_aux);
        retira_no(p2, entrada);
        
    }
    
    fecho->tam++;

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

int** aloca_matriz(int tam, int num) {
    int i, j;
    int **m = (int**)malloc(sizeof(int*)*tam);
    for(i=0; i < tam; i++) {
        m[i] = (int*)malloc(sizeof(int)*tam);
        for(j = 0; j < tam; j++) {
            m[i][j] = (int)num;
        }
    }
    return m;
}