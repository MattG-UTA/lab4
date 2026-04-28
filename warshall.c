/*
 * CSE 3318 Lab 5
 * Compile on OMEGA with: gcc warshall.c -o warshall
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXV 50
#define MAXE (MAXV * MAXV)
#define INF 1000000

static void printMatrix(int n, int leader[MAXV][MAXV], int succ[MAXV][MAXV])
{
  int i,j;
  static int firstCell=1;

  for (i=0;i<n;i++)
  {
    for (j=0;j<n;j++)
      if (leader[i][j]==INF)
        printf("oo     ");
      else if (firstCell)
      {
        printf("%d %2d  ",leader[i][j],succ[i][j]);
        firstCell=0;
      }
      else
        printf("%2d %2d  ",leader[i][j],succ[i][j]);
    printf("\n");
  }
  printf("-------------------------------\n");
}

static void printPath(int start, int finish, int succ[MAXV][MAXV])
{
  int current=start;

  printf("%d",current);
  while (current!=finish)
  {
    current=succ[current][finish];
    printf(" %d",current);
  }
  printf("\n");
}

int main(void)
{
  FILE *in;
  int leader[MAXV][MAXV],succ[MAXV][MAXV];
  int edgeTail[MAXE],edgeHead[MAXE];
  int n,i,j,k,tail,head,edgeCount=0,newLeader;

  in=fopen("lab5.a.dat","r");
  if (in==NULL)
  {
    fprintf(stderr,"Unable to open lab5.a.dat\n");
    return 1;
  }

  if (fscanf(in,"%d",&n)!=1 || n<1 || n>MAXV)
  {
    fprintf(stderr,"Invalid vertex count\n");
    fclose(in);
    return 1;
  }

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

  while (fscanf(in,"%d %d",&tail,&head)==2)
  {
    if (tail==(-1) && head==(-1))
      break;

    if (tail<0 || tail>=n || head<0 || head>=n)
    {
      fprintf(stderr,"Invalid edge %d %d\n",tail,head);
      fclose(in);
      return 1;
    }

    if (edgeCount<MAXE)
    {
      edgeTail[edgeCount]=tail;
      edgeHead[edgeCount]=head;
      edgeCount++;
    }

    if (tail!=head)
    {
      leader[tail][head]=(tail<head) ? tail : head;
      succ[tail][head]=head;
    }
  }

  for (j=0;j<n;j++)
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

  for (i=0;i<edgeCount;i++)
    if (edgeTail[i]!=edgeHead[i])
    {
      leader[edgeTail[i]][edgeHead[i]]=
        (edgeTail[i]<edgeHead[i]) ? edgeTail[i] : edgeHead[i];
      succ[edgeTail[i]][edgeHead[i]]=edgeHead[i];
    }

  printMatrix(n,leader,succ);

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

  for (i=0;i<n;i++)
    if (leader[i][i]==i)
      printf("Vertex %d is a leader\n",i);
    else
    {
      printf("Vertex path to leader is:  ");
      printPath(i,leader[i][i],succ);
      printf("Vertex path from leader is:  ");
      printPath(leader[i][i],i,succ);
    }

  fclose(in);

  return 0;
}
