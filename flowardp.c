#include <stdio.h>
#include <stdlib.h>
#include "solve.h"
/*#define PATH*/

void solve(int n,int **graph){
	int i,j,k,t;
	int **next; /*Used for path reconstruction*/
	int **Q;
	
	/*Allocate memory for n*n array (next) */
	if( (next = malloc(n*sizeof(int*))) == NULL ) return ;
	for (i=0;i<n;i++){
		if( (next[i] = malloc(n*sizeof(int))) == NULL ) return ;
	}
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			for (k=0;k<n;k++){
				next[i][j] = -1; /*first value of next[i][j] is -1 (null)*/
			}
		}
	}
	
	/*Allocate memory for n*n array (Q)*/
	if( (Q = malloc(n*sizeof(int*))) == NULL ) return ;
	for (i=0;i<n;i++){
		if( (Q[i] = malloc(n*sizeof(int))) == NULL ) return ;
	}
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			for (k=0;k<n;k++){
				Q[i][j] = graph[i][j]; /*first value of Qij is direct distance of ij*/
				next[i][j] = j;
			}
		}
	}
	
	
	for (k=0;k<n-1;k++){ 
		for (i=0;i<n;i++){
			for (j=0;j<n;j++){
				if (Q[i][j] == -1){   /*if there is no path from i to j*/
					if (Q[i][k] != -1 && Q[k][j] != -1){  /*and there is a path from i to k and k to j*/ 
						Q[i][j] = Q[i][k] + Q[k][j];  /*then this is the path from i to j*/
						next[i][j] = next[i][k];
					}
				}
				else if (Q[i][k] != -1 && Q[k][j] != -1){  /*if there is a path from i -> j and from i->k->j*/
					if (Q[i][k] + Q[k][j] < Q[i][j]){ /*and if cost of i->k->j is less than the cost of i->j*/
						Q[i][j] = Q[i][k] + Q[k][j]; /*then i->k->j is the new path*/
						next[i][j] = next[i][k]; 
					} 
				}
			}
		}
	}
	
	for(i=0;i<n;i++){
		printf("\n");
		for(j=0;j<i;j++){
			if (Q[i][j] != -1){
				printf("From node %d to node %d: Length of the shortest path is %d\n",i,j,Q[i][j]);
				#ifdef PATH
				/*Modified version of this algorithm: en.wikipedia.org/wiki/Floyd–Warshall_algorithm#Path_reconstruction*/
				if (next[i][j]!=-1){
					t = i;
					printf(" Shortest path is: %d",t);
					while (t!=j) {
						t = next[t][j];
						printf("->%d",t);
					}
					printf("\n");
				}
				#endif
			}
			else{
				printf("From node %d to node %d: There is no path\n",i,j);				
			}
		}
	}
	
	/*Free allocated memory*/
	for (i=0;i<n;i++){
		free(Q[i]);
		free(next[i]);
	}
	free(Q);
	free(next);
}
