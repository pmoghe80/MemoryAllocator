#include <iostream>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

typedef struct Node * Node_t;

struct Node {
   void * item;
   Node_t next;
   Node_t prev;
};


void InitList (Node_t *head);
Node_t AllocNode ();
Node_t fetchFreeNode (Node_t n);
Node_t Insert (Node_t *head, Node_t n, void *item);
int Delete (Node_t n);
void InsertEnd (Node_t *head, Node_t n);
