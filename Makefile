all:
	gcc -o tsp heuristica.h heuristica.c fecho_convexo.h fecho_convexo.c Pontos.h Pontos.c stdafx.h main.c -lm

clean:
	rm -rf tsp