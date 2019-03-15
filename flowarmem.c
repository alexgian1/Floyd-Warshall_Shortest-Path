#include <stdio.h>
#include <stdlib.h>
#include "solve.h"

int min(int,int);
int sPath(int,int,int,int**,int***);

void solve(int n,int **graph){
	int i,j,k,d;

	/*Allocate memory for n*n*n array*/
	int ***P;
	if( (P = malloc(n*sizeof(int**))) == NULL ) return ;
	for (i=0;i<n;i++){
		if( (P[i] = malloc(n*sizeof(int*))) == NULL ) return ;
		for (j=0;j<n;j++){
			if( (P[i][j] = malloc(n*sizeof(int))) == NULL ) return ;
		}
	}
	
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			for (k=0;k<n;k++){
				P[i][j][k] = -2; /*Value that shows that Pijk has not been defined*/
			}
		}
	}
	
	for (i=0;i<n;i++){ /*Prints paths*/
		printf("\n");
		for (j=0;j<i;j++){
			d = sPath(i,j,n-1,graph,P);
			if (d == -1) {
				printf("From node %d to node %d : There is no path\n",i,j);
			}
			else {
				printf("From node %d to node %d : Length of the shortest path is %d\n",i,j,d);
			}
		}
	}
	/*Free allocated memory*/
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			free(P[i][j]);
		}
		free(P[i]);
	}
	free(P);
}

int min(int x,int y){
	if (x==-1){   /*if there is no connection do not compare distances*/
		return y;
	}
	if (y==-1){   
		return x;
	}
	return ((x<y) ? x : y);
}

int sPath(int i,int j, int k, int **graph, int ***P){
	int s;
	if (k<0){
		return graph[i][j];
	}
	
	if (P[i][j][k] == -2){ /*if Pijk is not defined*/
		s = sPath(i,k,k-1,graph,P)+sPath(k,j,k-1,graph,P);    
		if (sPath(i,k,k-1,graph,P)==-1 || sPath(k,j,k-1,graph,P)==-1) s = -1;    /*if cost of one term is infinity then the sum is infinity(-1)*/
		P[i][j][k] = min(sPath(i,j,k-1,graph,P),s);
		return min(sPath(i,j,k-1,graph,P),s);
	}
	else {
		return P[i][j][k];
	}
}
