#include <stdio.h>
#include <stdlib.h>
#include "solve.h"

int main(void){
	int n,i,j;
	int **graph;
	
	if(scanf("%d",&n) != 1) return 1;
	
	if ((graph = malloc(n*sizeof(int*))) == NULL) return 2; /*Allocate space for n*n array*/
	for (i=0;i<n;i++){
		if ((graph[i] = malloc(n*sizeof(int))) == NULL) return 3;
	}
	
	for (i=0;i<n;i++){
		for (j=0;j<=i;j++){
			if (i==j) graph[i][j] = 0; /*zero diagonal elements (distance i to i is 0)*/
			if (i>j){  /*left triangle side of array*/
				if (scanf("%d",&graph[i][j]) != 1);
				graph[j][i]=graph[i][j]; /*distance i->j = distance j->i*/
			}
		}
	}
	
	/*for (i=0;i<n;i++){  //print the array
		for (j=0;j<n;j++){
			printf("%d ",graph[i][j]);
		}
		printf("\n");
	}*/
	
	solve(n,graph);
	
	for (i=0;i<n;i++){
		free(graph[i]);
	}
	free(graph);
	
	return 0;
}
