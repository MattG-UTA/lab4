#include <stdio.h>
#include <stdlib.h>

#include "warshall_helpers.h"

// Allocate one n by n matrix with row pointers for normal matrix indexing.
int **makeMatrix(int n)
{
  int **matrix;
  int *data;
  int i;

  matrix=malloc(n*sizeof(int *));
  data=malloc(n*n*sizeof(int));
  if (matrix==NULL || data==NULL)
  {
    free(matrix);
    free(data);
    return NULL;
  }

  for (i=0;i<n;i++)
    matrix[i]=data+i*n;

  return matrix;
}

// Free a matrix created by makeMatrix.
void freeMatrix(int **matrix)
{
  if (matrix!=NULL)
  {
    free(matrix[0]);
    free(matrix);
  }
}

// Reset the leader and successor matrices to the starting graph state.
void initMatrices(int n, int **leader, int **succ)
{
  int i,j;

  for (i=0;i<n;i++)
    for (j=0;j<n;j++)
    {
      leader[i][j]=INF;
      succ[i][j]=(-1);
    }

  for (i=0;i<n;i++)
  {
    leader[i][i]=i;
    succ[i][i]=i;
  }
}

// Add a directed edge to the initial leader and successor matrices.
void addEdge(int tail, int head, int **leader, int **succ)
{
  if (tail!=head)
  {
    leader[tail][head]=(tail<head) ? tail : head;
    succ[tail][head]=head;
  }
}

// Print the current leader/successor matrix pair.
void printMatrix(int n, int **leader, int **succ)
{
  int i,j;

  for (i=0;i<n;i++)
  {
    for (j=0;j<n;j++)
      if (leader[i][j]==INF)
        printf("oo     ");
      else
        printf("%2d %2d  ",leader[i][j],succ[i][j]);
    printf("\n");
  }
  printf("-------------------------------\n");
}

// Follow successor links to print a path from start to finish.
void printPath(int start, int finish, int **succ, int endLine)
{
  int current=start;

  printf("%d",current);
  while (current!=finish)
  {
    current=succ[current][finish];
    printf(" %d",current);
  }
  if (endLine)
    printf("\n");
}
