#include "my_list.h"

void InitList (Node_t *head) {
     *head = (Node_t)malloc(sizeof(**head));
     (*head)->next = NULL;
     (*head)->prev = NULL;
} 

Node_t AllocNode () {

    Node_t tmp = (Node_t)malloc(sizeof(*tmp));
    tmp->next = NULL;
    tmp->prev = NULL;
    return tmp;
}

Node_t fetchFreeNode (Node_t head) {
       if (!(head)) {
          return NULL;
       }

       if (!head->next && !head->prev) {
          return NULL;
       }

       Node_t tmp = head->next;
       if (tmp) {
          head->next = tmp->next; 
          if (head->prev == tmp) {
              head->prev = NULL;
          }
          if (head->next == head) {
             head->next = NULL;
          } 
       } else {
          return NULL;
       }   
       return tmp;
}
    
Node_t Insert (Node_t *head, Node_t n, void *item) {
      if (!n) {
         return NULL;
      }

      if (!(*head)->prev) {
         (*head)->prev = n;
      }
      
      if (!(*head)->next) {
         n->next = (*head);
      } else {
         n->next = (*head)->next;
      }
      n->prev = (*head);
      n->item = item;      
      (*head)->next = n;
      return NULL;
}

void InsertEnd (Node_t *head, Node_t n) {

      if (!(*head)->prev && !(*head)->next) {
         (*head)->prev = n;
         (*head)->next = n;
         n->next       = *head;
         return;
      }
            
      n->prev = (*head)->prev;
      n->next = *head; 
      (*head)->prev->next = n;
      (*head)->prev = n;
}

int Delete (Node_t *head, Node_t n) {
    if (!n) {
       return 1;
    }

    Node_t tmp       = n->next;
    n->prev->next    = tmp;
    if (tmp) {
       tmp->prev = n->prev;
    }  
    return 0;
}


