// Unbalanced binary search tree implementation

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

link z,head;               // Pointers to sentinel and root
Item NULLitem=(-9999999);  // Data for sentinel

link NEW(Item item, link l, link r, int N)
// Allocates and fills in a node
{
link x; 

x = malloc(sizeof *x); 
x->item = item;
x->l = l;
x->r = r;
x->N = N;
return x;
}

void STinit()
{
// Empty tree contains just the root/sentinel (head/z)
head = (z = NEW(NULLitem, 0, 0, 0));
}

Item searchR(link h, Key v)
// Recursive search for a key
{ 
Key t = key(h->item);
if (h == z) 
  return NULLitem;
if (eq(v, t))
  return h->item;
if (less(v, t))
  return searchR(h->l, v);
return searchR(h->r, v);
}

Item STsearch(Key v) 
{
return searchR(head, v);
}

Item selectR(link h, int i)
// Returns the ith smallest key where i=1 returns the smallest
// key.  Thus, this is like flattening the tree inorder into an array
// and applying i as a subscript.
{ 
int r;

if (h == z)
{
  printf("Impossible situation in selectR\n");
  STprintTree();
  exit(0);
}

r = h->l->N+1;
if (i==r)
  return h->item;
if (i<r)
  return selectR(h->l, i);
return selectR(h->r, i-r);
}

Item STselect(int k)
{
if (k<1 || k>head->N)
{
  printf("Range error in STselect() k %d N %d\n",k,head->N);
  exit(0);
}
return selectR(head, k);
}

int invSelectR(link h, Key v)
// Inverse of selectR
{
Key t = key(h->item);
int work;

if (h==z)
  return -1;  // v doesn't appear as a key
if (eq(v, t))
  return h->l->N+1;
if (less(v, t))
  return invSelectR(h->l,v);
work=invSelectR(h->r,v);
if (work==(-1))
  return -1;  // v doesn't appear as a key
return 1+h->l->N + work;
}

int STinvSelect(Key v)
{
return invSelectR(head,v);
}

void fixN(link h)
// Fixes subtree size of h, assuming that subtrees have correct sizes
{

h->N=h->l->N + h->r->N + 1;
}

link STinsertR(link h, Item item)
// Simple unbalanced insert
{
Key v = key(item);

if (h == z)
  return NEW(item, z, z, 1);  // Attach leaf

if (eq(v, key(h->item)))
  h->item=item;
else if (less(v, key(h->item)))
  h->l = STinsertR(h->l, item); // Insert in left subtree
else
  h->r = STinsertR(h->r, item); // Insert in right subtree

fixN(h);
return h;
}

void STinsert(Item item)
{
head = STinsertR(head, item);
}

Key lastInorder;    // Saves key from last node processed

void checkInorder(link h)
// Checks that inorder yields keys in ascending order
{
if (h==z)
  return;

checkInorder(h->l);
if (less(h->item,lastInorder))
{
  printf("Inorder error\n");
  STprintTree();
  exit(0);
}
lastInorder=key(h->item);
checkInorder(h->r);
}

void checkN(link h)
// Verifies that subtree sizes are correct
{
int work;

if (h==z)
{
  if (h->N!=0)
  {
    printf("Count for sentinel is %d, should be 0\n",h->N);
    STprintTree();
    exit(0);
  }
  return;
}

checkN(h->l);
checkN(h->r);

work=h->l->N + h->r->N + 1;
if (h->N!=work)
{
  printf("Count for key %d is %d, should be %d\n",key(h->item),h->N,work);
  STprintTree();
  exit(0);
}
}

void STverifyProperties()
// Checks all required properties.
// If a fatal problem is found, the tree is printed before exit(0)
{

lastInorder=(-99999999);
checkInorder(head);

checkN(head);
}

void printTree(link h,int depth)
{
int i;

if (h==z)
  return;

printTree(h->r,depth+1);
for (i=0;i<depth;i++)
  printf("     ");
printf("%d %d\n",key(h->item),h->N);
printTree(h->l,depth+1);
}

void STprintTree()
{
printTree(head,0);
}

void fixAllN(link h)
// Recomputes subtree sizes for an otherwise correct tree
{
if (h->l)
  fixAllN(h->l);
else
  h->l=z;
if (h->r)
  fixAllN(h->r);
else
  h->r=z;
fixN(h);
}

int getLive()
{
return head->N;
}