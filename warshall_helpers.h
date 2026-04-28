#ifndef WARSHALL_HELPERS_H
#define WARSHALL_HELPERS_H

#define INF 1000000

int **makeMatrix(int n);
void freeMatrix(int **matrix);
void initMatrices(int n, int **leader, int **succ);
void addEdge(int tail, int head, int **leader, int **succ);
void printMatrix(int n, int **leader, int **succ);
void printPath(int start, int finish, int **succ, int endLine);

#endif
