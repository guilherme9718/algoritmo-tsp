#include "fecho_convexo.h"

/*procura os dois pontos com menor x e maior x, 
caso houver empate procura o pontos com menor x e y e com maior x e y */
void procura_pontos_extremos(Pontos p, Ponto *maior, Ponto *menor) {
    int i, x, y;

    maior->x = menor->x = p.v[0].x;
    maior->y = menor->y = p.v[0].y;

    for(i=1; i < p.n; i++) {
        x = p.v[i].x;
        y = p.v[i].y;

        if(x <= menor->x) {
            menor->x = x;
            if(y < menor->y) {
                menor->x = x;
                menor->y = y;
            }
            menor->y = y;
        }
        if(x >= maior->x) {
            maior->x = x;
            if(y >= maior->y) {
                maior->x = x;
                maior->y = y;
            }
            maior->y = y;
        }
    }
}

//calcula a distancia da reta p1p2 do ponto p3 
double distancia_reta_ponto(Ponto p1, Ponto p2, Ponto p3) {
    double d, aux;
    double u;
    double x1 = p1.x, y1 = p1.y; 
    double x2 = p2.x, y2 = p2.y;
    double x3 = p3.x, y3 = p3.y;  

    d = ((x2-x1)*(y3-y1));
    aux = ((y2-y1)*(x3-x1));
    aux = d-aux;

    d = aux*((x2-x1)*(y3-y1)-(y2-y1)*(x3-x1));
    d = sqrt(d);
    
    u = ((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    u = sqrt(u);

    d = d / u;

    return d;
}

//calcula a area do paralelogramo formada pelos vetores p1p2 e p1p3
long long int area_paralelogramo(Ponto p1, Ponto p2, Ponto p3) {
    long long int a;
    long long int x1 = p1.x, y1 = p1.y;
    long long int x2 = p2.x, y2 = p2.y;
    long long int x3 = p3.x, y3 = p3.y;

    a = (x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);
    
    return a;
}

/*escolhe o ponto mais distante da reta pq a esquerda 
e faz mais duas retas com este até não sobrar mais pontos a esquerda */
void mais_distante_reta_esq(Pontos* vetor, Pontos* fecho, Ponto p, Ponto q) {
    int i, j, pontos_esq;
    double maior_d, d;
    Ponto res;

    if (vetor->n <= 0) {
        return;
    }

    Pontos vetor_novo;
    vetor_novo.n = 0;
    vetor_novo.v = (Ponto*)malloc(sizeof(Ponto) * vetor->n);

    pontos_esq = 0;
    for(i = 0; i < vetor->n; i++) {
        if(area_paralelogramo(p, q, vetor->v[i]) > 0) {
            pontos_esq = 1;
            j = i;
            res.x = vetor->v[i].x;
            res.y = vetor->v[i].y;
            j = i;
            maior_d = distancia_reta_ponto(p, q, res);
            adiciona_ponto(&vetor_novo, res);
            break;
        }
    }

    if(!pontos_esq) {
        free(vetor_novo.v);
        return;
    }
    
    for(i=j+1; i < vetor->n; i++) {
        if(area_paralelogramo(p, q, vetor->v[i]) > 0) {
            d = distancia_reta_ponto(p, q, vetor->v[i]);
            if(d > maior_d) {
                maior_d = d;
                res.x = vetor->v[i].x;
                res.y = vetor->v[i].y;
            }
            adiciona_ponto(&vetor_novo, vetor->v[i]);
        }
    }

    
    mais_distante_reta_esq(vetor, fecho, res, q);
    adiciona_ponto(fecho, res);
    mais_distante_reta_esq(vetor, fecho, p, res);

    free(vetor_novo.v);
}

/*escolhe o ponto mais distante da reta pq a direita 
e faz mais duas retas com este até não sobrar mais pontos a direita */
void mais_distante_reta_dir(Pontos* vetor, Pontos* fecho, Ponto p, Ponto q) {
    int i, j, pontos_esq;
    double maior_d, d;
    Ponto res;

    if (vetor->n <= 0) {
        return;
    }

    Pontos vetor_novo;
    vetor_novo.n = 0;
    vetor_novo.v = (Ponto*)malloc(sizeof(Ponto) * vetor->n);

    pontos_esq = 0;
    for(i = 0; i < vetor->n; i++) {
        if(area_paralelogramo(p, q, vetor->v[i]) < 0) {
            pontos_esq = 1;
            j = i;
            res.x = vetor->v[i].x;
            res.y = vetor->v[i].y;
            j = i;
            maior_d = distancia_reta_ponto(p, q, res);
            adiciona_ponto(&vetor_novo, res);
            break;
        }
    }

    if(!pontos_esq) {
        free(vetor_novo.v);
        return;
    }
    
    for(i=j+1; i < vetor->n; i++) {
        if(area_paralelogramo(p, q, vetor->v[i]) < 0) {
            d = distancia_reta_ponto(p, q, vetor->v[i]);
            if(d > maior_d) {
                maior_d = d;
                res.x = vetor->v[i].x;
                res.y = vetor->v[i].y;
            }
            adiciona_ponto(&vetor_novo, vetor->v[i]);
        }
    }


    mais_distante_reta_dir(&vetor_novo, fecho, p, res);
    adiciona_ponto(fecho, res);
    mais_distante_reta_dir(&vetor_novo, fecho, res, q);

    free(vetor_novo.v);
}

/*calcula os primeiros pontos extremos,
faz uma reta e recursivamente calcula os pontos mais distantes da reta para colocar no fecho
*/
Pontos fecho_convexo(Pontos entrada) {
    Pontos fecho;
    fecho.v = (Ponto*)malloc(sizeof(Ponto)*entrada.n);
    fecho.n = 0;

    if(entrada.n == 1) {
        adiciona_ponto(&fecho, entrada.v[0]);
        return fecho;
    }

    int i, maior_x, menor_x, maior_y, menor_y;
    Ponto maior, menor;

    procura_pontos_extremos(entrada, &maior, &menor);

    adiciona_ponto(&fecho, menor);
    mais_distante_reta_dir(&entrada, &fecho, menor, maior);
    
    adiciona_ponto(&fecho, maior);
    mais_distante_reta_esq(&entrada, &fecho, menor, maior);
    
    return fecho;
}