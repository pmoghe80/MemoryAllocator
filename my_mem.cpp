#include "my_list.h"

#define MEM_POOL_SZ     256 * 1048576
#define CHUNK_SZ        4096
#define NUM_MEM_CHUNKS  65536

#define myoffsetof(member, type) ((size_t) &((type *)0)->member)

//#define memberOf(var, type, member) (type *)((char *)var - myoffsetof(member, type))
#define memberOf(ptr, type, member) ({                                                  \
                                    (type *)( (char *)&ptr - offsetof(type, member) );})

struct Chunk {
     int  id; 
     void *start_addr;
     void *end_addr;
     int  status;
     Node_t list; 
};

struct MyMem {
    int id;
    void *pool;
    Node_t chunk_free_list;
    Node_t chunk_alloc_list;
    struct Chunk *my_chunks[NUM_MEM_CHUNKS];
    int free_chunk_index;
};

struct MyMem * initAlloc() {

    int i=0;
    struct MyMem *m = (struct MyMem *)malloc(sizeof(struct MyMem));
    m->pool = malloc(MEM_POOL_SZ);
    if (!m->pool) {
       free(m);
       return NULL;
    }

    InitList(&m->chunk_alloc_list);
    InitList(&m->chunk_free_list);
    
    while (i < NUM_MEM_CHUNKS) {
       /*struct Chunk *c = (struct Chunk *) malloc(sizeof(struct Chunk));
        c->id           = m->id++; 
        m->my_chunks[i] = c;
        c->start_addr   = m->pool + CHUNK_SZ*i;
        c->end_addr     = c->start_addr + 4096;
        c->status       = 0;
        c->list         = AllocNode();*/
        Insert(&m->chunk_alloc_list, AllocNode(), (void *)(m->pool + CHUNK_SZ*i));
        i++; 
    }
    return m;
}      
     
void * getMemory(struct MyMem *m) {
       int i=0;
       
       Node_t mem_node = fetchFreeNode(m->chunk_alloc_list);
       if (!mem_node) {
          return NULL;
       } 

       //Delete(mem_node);
       //Insert(&m->chunk_alloc_list, mem_node, mem_node->item);
       /*while (i < NUM_MEM_CHUNKS) {
             if (!m->my_chunks[i]->status) {
                 m->my_chunks[i]->status = 1;
                 return m->my_chunks[i]->start_addr;
             }
             i++;
       }*/
      
       /*struct Chunk *c = (struct Chunk *)mem_node->item; 
       if (!c) {
          return NULL;
       }*/

       void *addr = mem_node->item;
       mem_node->item = NULL;
       //free(c);
       //unsigned long x = (unsigned long)c->start_addr; 
       //unsigned long y = (unsigned long)c;
       //chunk_hash.insert(make_pair(x, y));   
       InsertEnd(&m->chunk_free_list, mem_node);
       return mem_node->item;
}

void freeMemory (struct MyMem *m, void *addr) {
     int i=0;
     Node_t mem_node = fetchFreeNode(m->chunk_free_list);
     /*while (i<NUM_MEM_CHUNKS) {
          if (m->my_chunks[i]->start_addr == addr) {
              m->my_chunks[i]->status = 0;
              break;
          }
          i++;
     }*/

     //printf("Freeing memory\n");
     //auto chunk_iter = chunk_hash.find((unsigned long)addr); 
     //struct Chunk *c = (struct Chunk *)chunk_iter->second;
     //struct Chunk *c = memberOf(addr, struct Chunk, start_addr);
     
     //Delete(c->list); 
     /*struct Chunk *c = (struct Chunk *) malloc(sizeof(struct Chunk));
     c->start_addr   = addr;
     c->end_addr     = c->start_addr + 4096;
     c->status       = 0;
     c->list         = AllocNode();*/
     Insert(&m->chunk_alloc_list, mem_node, addr);
     //Insert(&m->chunk_free_list, c->list, c);  
     return;
}


int main() {

   struct MyMem  *m = initAlloc();
   if (!m) {
     printf("Could not init allocator\n");
     return 1;
   }


 int i=0;
 int j=0;
 unsigned long alloc_addr[6];
 for (i=0; i<10000000; i++) {
   void *addr = getMemory(m);
   alloc_addr[j++] = (unsigned long)addr;
   if (i && i%5 == 0) { 
      for (j=0; j < 6; j++) {
         freeMemory(m,(void *)alloc_addr[j]);
      }
      j = 0;
   }
   /*void *addr = malloc(4096);
   alloc_addr[j++] = (unsigned long)addr;
   //cout << j << endl;
   if (i && i%5 == 0) {
      for (j=0; j < 6; j++) {
          free((void *)alloc_addr[j]);
          alloc_addr[j] = NULL; 
      }
      j=0;
   }*/
 }
   return 0;
}
       
