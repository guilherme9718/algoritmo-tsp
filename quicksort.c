#include "quicksort.h"

//inverte os a coordenada do vertice
void troca(Pontos p, int i, int j) {
	Ponto aux = p.v[i];
	p.v[i] = p.v[j];
	p.v[j] = aux;
}

//Particiona o vetor para comparar os pontos que estão contidos no vetor
int particiona(Pontos p, int esq, int dir) {
	Ponto pivo = p.v[dir];
	int i = esq - 1;
	int j;
	for (j = esq; j <= dir - 1; j++) {
		if (compara_pontos(p.v[j], pivo) <= 0) {
			i++;
			troca (p, i, j);
		}
	}
	troca (p, i+1, dir);
	return i + 1;
}

// ordenação dos pontos quicksort recursivo
void quicksort(Pontos p, int esq, int dir) {
	if (esq < dir) {
		int pivo = particiona (p, esq, dir);
		quicksort (p, esq, pivo-1);
		quicksort (p, pivo+1, dir); 
	}
}

//realiza a busca binaria do vetor do ponto no meio do vetor com o vetor esperado atraves do metodo compara_pontos
int busca_binaria(Pontos vetor, Ponto p, int esq, int dir) {
	while (esq <= dir) {
		int meio = (esq + dir ) / 2;
		int controle = compara_pontos(vetor.v[meio], p);
		if (controle == 0)
			return 0;			
		else if (controle == -1)
			esq = meio + 1;
		else
			dir = meio - 1;
	}
	
	return 1;
}
