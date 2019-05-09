#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **alocarMatriz(int n);
double *alocarB(int n);
void lerMatriz(int n, double **p, double *B);
void imprimeMatriz(int n, double **p, double *B);
void pivotear(int n, double **p, double *B, int b, int a);
void zerarTriangInf(int n, double **p, double *B);
double *calculaResultado(int n, double **p, double *B);
void imprimeResultado(int n, double *r);
void desalocaMeB(int n, double **p, double *B);
void desalocaResultado(double *r);

//MATRIZ 3x3 DE TESTES
//  1  1  1 | 1
//  2 -1  3 | 0
// -1  1 -5 | 2
// M:1 1 1 2 -1 3 -1  1 -5
// B:1 0 2
// INPUT: 3 1 1 1 2 -1 3 -1  1 -5 1 0 2
// RESULTADO ESPERADO
// 1 0.5 -0.5

int main(){
	double **p, *B;

	double *resultado;
	int n;

	printf("Dimensão da matriz: ");
	scanf("%d", &n);

	p = alocarMatriz(n);
	B = alocarB(n);
	lerMatriz(n,p,B);

	zerarTriangInf(n,p,B);
	imprimeMatriz(n,p,B);

	resultado = calculaResultado(n,p,B);
	imprimeResultado(n,resultado);

	desalocaMeB(n,p,B);
	desalocaResultado(resultado);
	return 0;	
}

double **alocarMatriz(int n){
	int i,j; 

	double **m = (double**) malloc(n * sizeof(double*)); // Aloca um vetor de ponteiros

	for (i = 0; i < n; i++)
		m[i] = (double*) malloc(n * sizeof(double));  // Aloca um vetor de valores double
	
	return m;
}

double *alocarB(int n){
	double *m = (double *) malloc(n * sizeof(double));
	return m;
}

void lerMatriz(int n, double **p, double *B){
	int i,j;

	printf("Valores da matriz M:\n");
	for(i = 0; i < n; i++){
		for(j = 0; j < (n); j++){
			scanf("%lf", &p[i][j]);
		}
	}

	printf("Valores da matriz B:\n");
	for(i = 0; i < n; i++){
		scanf("%lf", &B[i]);
	}

}

void zerarTriangInf(int n, double **p, double *B){
	int a,b,c;
	double l;

	for(a = 0; a < (n-1); a++){// Número de elementos de vezes a aplicar o algoritmo
	
		for(b = (a+1); b < n; b++){

			pivotear(n,p,B,a,a);

			if(p[a][a] == 0){
				printf("Divisão por 0 inesperada\n");
				break;
			}

			l = p[b][a] / p[a][a]; // Calcula o valor a ser aplicado as linhas

			for(c = a; c < n; c++){// Aplica o valor calculado as linhas
				p[b][c] = p[b][c] - p[a][c]*l;
			}

			B[b] = B[b] - B[a]*l;//Aplica o valor calculado ao vetor B

		}
	}
}

void pivotear(int n, double **p, double *B, int b, int a){
	double maior;
	int i; //Contador para o for
	int j; //Posição do maior elemento
	double *q, aux;
	
	maior = fabs(p[b][a]);
	j = b;

	for(i = b; i < n; i++){
		if(fabs(p[i][a]) > maior){
			maior = fabs(p[i][a]);
			j = i;
		}
	}

	//Troca as linhas para evitar divisão por 0
	q = p[b];
	p[b] = p[j];
	p[j] = q; 
	
	aux = B[b];
	B[b] = B[j];
	B[j] = aux;
}

double *calculaResultado(int n, double **p, double *B){
	double *result = malloc(n * sizeof(double));
	double sum;
	int a, b, count=(n-1);

	for(a = (n-1); a >= 0; a--){
		sum = 0;

		for(b=count; b < n; b++){
			sum += (p[a][b]*result[b]);
		}

		result[a] = (B[a]-sum)/p[a][a];
		count--;
	}

	return result;
}

void imprimeMatriz(int n, double **p, double *B){
	int i,j;

	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%+3.3lf\t", p[i][j]);
		}
		printf("|\t%+3.3lf\n", B[i]);
		putchar('\n');
	}

	putchar('\n');
}

void imprimeResultado(int n, double *r){
	int i;
	for(i = 0; i < n; i++){
		printf("Resultado de x%2d: %+3.3lf\n", i+1, r[i]);
	}
}

void desalocaMeB(int n, double **p, double *B){
	int i,j;

	for(i = 0; i < n; i++){
		free(p[i]);//Desaloca vetor de números
	}

	free(p);//Desaloca vetor de ponteiros

	free(B);//Desaloca matriz B
}

void desalocaResultado(double *r){
	free(r);
}
