#include <stdio.h>
#include "solve.h"

int min(int,int);
int sPath(int,int,int,int**);

void solve(int n,int **graph){
	
	int i,j,d;
	for (i=0;i<n;i++){
		printf("\n");
		for (j=0;j<i;j++){
			d = sPath(i,j,n-1,graph); /*Distance of shortest path from i to j*/
			if (d == -1) {
				printf("From node %d to node %d : There is no path\n",i,j);
			}
			else {
				printf("From node %d to node %d : Length of the shortest path is %d\n",i,j,d);
			}
		}
	}
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

int sPath(int i,int j, int k, int **graph){
	int s;
	if (k<0){
		return graph[i][j];
	}
	
	s = sPath(i,k,k-1,graph)+sPath(k,j,k-1,graph);    
	if (sPath(i,k,k-1,graph)==-1 || sPath(k,j,k-1,graph)==-1) s = -1;    /*if cost of one term is infinity then the sum is infinity(-1)*/
	
	return min(sPath(i,j,k-1,graph),s);
}
