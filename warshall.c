// Matthew Gutierrez
// 1002333697
// Lab 5
// Compile Command: gcc warshall.c warshall_helpers.c -o Lab 5

#include <stdio.h>
#include <stdlib.h>

#include "warshall_helpers.h"

int main(void)
{
  int **leader,**succ;
  int *edgeTail,*edgeHead;
  int n,i,j,k,tail,head,edgeCount=0,newLeader;

  if (scanf("%d",&n)!=1 || n<1)
  {
    fprintf(stderr,"Invalid vertex count\n");
    return 1;
  }

  // Allocate all storage based on the vertex count from stdin.
  leader=makeMatrix(n);
  succ=makeMatrix(n);
  edgeTail=malloc(n*n*sizeof(int));
  edgeHead=malloc(n*n*sizeof(int));
  if (leader==NULL || succ==NULL || edgeTail==NULL || edgeHead==NULL)
  {
    fprintf(stderr,"Out of memory\n");
    freeMatrix(leader);
    freeMatrix(succ);
    free(edgeTail);
    free(edgeHead);
    return 1;
  }

  // Read and validate the directed edges, storing them for later setup.
  while (scanf("%d %d",&tail,&head)==2)
  {
    if (tail==(-1) && head==(-1))
      break;

    if (tail<0 || tail>=n || head<0 || head>=n)
    {
      fprintf(stderr,"Invalid edge %d %d\n",tail,head);
      freeMatrix(leader);
      freeMatrix(succ);
      free(edgeTail);
      free(edgeHead);
      return 1;
    }

    if (edgeCount<n*n)
    {
      edgeTail[edgeCount]=tail;
      edgeHead[edgeCount]=head;
      edgeCount++;
    }
  }

  // Build and print the starting matrix before the Warshall passes.
  initMatrices(n,leader,succ);

  for (i=0;i<edgeCount;i++)
    addEdge(edgeTail[i],edgeHead[i],leader,succ);

  printMatrix(n,leader,succ);

  // Run Warshall's algorithm one intermediate vertex at a time.
  for (j=0;j<n;j++)
  {
    for (i=0;i<n;i++)
      if (leader[i][j]!=INF)
        for (k=0;k<n;k++)
          if (leader[j][k]!=INF)
          {
            newLeader=leader[i][j];
            if (leader[j][j]<newLeader)
              newLeader=leader[j][j];
            if (leader[j][k]<newLeader)
              newLeader=leader[j][k];

            if (leader[i][k]==INF)
            {
              leader[i][k]=newLeader;
              succ[i][k]=succ[i][j];
            }
            else if (newLeader<leader[i][k])
              leader[i][k]=newLeader;
          }
    printMatrix(n,leader,succ);
  }

  // Print each vertex's leader status and paths to and from its leader.
  for (i=0;i<n;i++)
    if (leader[i][i]==i)
    {
      printf("Vertex %d is a leader",i);
      if (i<n-1)
        printf("\n");
    }
    else
    {
      printf("Vertex path to leader is:  ");
      printPath(i,leader[i][i],succ,1);
      printf("Vertex path from leader is:  ");
      printPath(leader[i][i],i,succ,i<n-1);
    }

  // Release dynamically allocated memory before exiting.
  freeMatrix(leader);
  freeMatrix(succ);
  free(edgeTail);
  free(edgeHead);

  return 0;
}
