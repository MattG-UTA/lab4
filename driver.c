// Driver for unbalanced BST.
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

int main()
{
int op,key,rank;

STinit();  // Initialize binary search tree
STverifyProperties();

scanf("%d",&op);
while (op)
{
  switch (op)
  {
    case 1:
      scanf("%d",&key);
      printf("1 %d successfully inserted\n",key);
      STinsert(key);
      break;
    case 2:
      scanf("%d",&key);
      printf("2 %d\n",key);
      rank=STinvSelect(key);
      if (rank==(-1))
        printf("Key %d is not in tree\n",key);
      else
        printf("Key %d has rank %d\n",key,rank);
      break;
    case 3:
      scanf("%d",&rank);
      printf("3 %d\n",rank);
      if (rank<1 || rank>getLive())
        printf("Rank %d range error\n",rank);
      else
        printf("Rank %d has key %d\n",rank,key(STselect(rank)));
      break;
    case 4:
      printf("4\n");
      STprintTree();
      break;
    case 5:
      printf("5\n");
      STverifyProperties();
      printf("Clean\n");
      break;
    default:
      printf("Bad operation %d\n",op);
  }
  //fflush(stdout);  // In case output is going to a fifo
  scanf("%d",&op);
}
printf("0\n");
}