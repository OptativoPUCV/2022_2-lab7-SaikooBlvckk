#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
  if (pq->size == 0) return NULL;
  return (void*) pq->heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority){
  if (pq->size == pq->capac){
    pq->capac = (pq->capac * 2) + 1;
    pq->heapArray = realloc(pq->heapArray, pq->capac*sizeof(heapElem));
  }
  pq->heapArray[pq->size].data = data;
  pq->heapArray[pq->size].priority = priority;
  int size = pq->size; int dadsize = ((pq->size-1)/2);
  heapElem *aux = (heapElem *)malloc(sizeof(heapElem));
  while (size > 0){
    if(pq->heapArray[size].priority > pq->heapArray[dadsize].priority){
      *aux = pq->heapArray[dadsize];
      pq->heapArray[dadsize] = pq->heapArray[size];
      pq->heapArray[size] = *aux;
    }
    size = dadsize;
    dadsize = (size - 1) / 2; 
  }
  pq->size++;
}


void heap_pop(Heap* pq){
  int size = pq->size; int pt = pq->heapArray[size-1].priority;
  void *data = pq->heapArray[size-1].data;

  pq->heapArray[size].priority = pq->heapArray[0].priority;
  pq->heapArray[size].data = pq->heapArray[0].data;
  pq->heapArray[0].priority = pt;
  pq->heapArray[0].data = data;
  pq->size = pq->size - 1;

  int i = 0;

  while(i < pq->size){
    int index1 = (i * 2) + 1; int index2 = (i * 2) + 2; int pt2 = pq->heapArray[i].priority;
    void *data2 = pq->heapArray[i].data;

    if (index1 > pq->size) pq->heapArray[index1].priority = 0;
    if (index2 > pq->size) pq->heapArray[index2].priority = 0;
    if (pq->heapArray[index1].priority > pq->heapArray[index2].priority){
      if (pq->heapArray[index1].priority > pq->heapArray[i].priority){
        pq->heapArray[i].priority = pq->heapArray[index1].priority;
        pq->heapArray[i].data = pq->heapArray[index1].data;
        pq->heapArray[index1].priority = pt2;
        pq->heapArray[index1].data = data2;
        i= index1; 
      }else break;
    }
    else if (pq->heapArray[index2].priority > pq->heapArray[index1].priority){
      if (pq->heapArray[index2].priority > pq->heapArray[i].priority){
        pq->heapArray[i].priority = pq->heapArray[index2].priority;
        pq->heapArray[i].data = pq->heapArray[index2].data;

        pq->heapArray[index2].priority = pt2;
        pq->heapArray[index2].data = data;
        i = index2;
      }else break;
    }else break;
  }
}

Heap* createHeap(){
  Heap* new = (Heap *)malloc(sizeof(Heap));
  new->size = 0;
  new->capac = 3;
  new->heapArray = (heapElem *)malloc(5*sizeof(heapElem));
  return new;
}
