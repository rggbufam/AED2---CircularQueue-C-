#include "circularQueue.h"
#include "stdlib.h"
#include "comparable.h"
#include "stdio.h"

typedef struct{
  int inseriu;
  int removeu;
  int movimentou;
  int sobrecarregou;
} TStatsFila;

typedef struct{
  void **array;
  int last;
  int first;
  int size;
  TStatsFila stats;
}TQueueData;

static int GetBreadth(TQueue* queue){
  TQueueData *data = queue->data;
  if(data->first <= data->last){
    if(data->first + data->last >= 0){
      return (data->last - data->first)+1;
    }else{
      return 0;
    }
  }else{
    return (data->size-(data->first - data->last))+1;
  }
}

static void resizeQueue(TQueue *queue){
  TQueueData *queueData = (TQueueData*)queue->data;
  int newSize = queueData->size*2;
  int oldSize = queueData->size;
  void **oldArray = queueData->array;
  void **newArray = malloc(sizeof(void*)*(newSize));
  int i,k;

  if(queueData->first > queueData->last){

    for(i=queueData->first,k=0;i<queueData->size;i++,k++){
      newArray[k] = oldArray[i];
      queueData->stats.movimentou++;
    }

    for(i=0;i<queueData->first;i++,k++){
      newArray[k] = oldArray[i];
      queueData->stats.movimentou++;
    }

  }else{

    for(i=queueData->first,k=0;i<=queueData->last;i++,k++){
      newArray[k] = oldArray[i];
      queueData->stats.movimentou++;
    }

  }

  queueData->first=0;
  queueData->last=oldSize-1;

  free(oldArray);

  queueData->array = newArray;
  queueData->size = newSize;
}
static void Insert(TQueue *queue,void* obj){
  TQueueData *data = (TQueueData*) queue->data;
  int i,inb4;
  void *aux;
  int newLast;

  if(data->size <= GetBreadth(queue)){
    //printf("{resize %d, %d}",data->size,queue->getBreadth(queue));
    resizeQueue(queue);
    data->stats.sobrecarregou++;
  }

  newLast = (data->last + 1)  % data->size;

  if(data->first>=0){

    data->array[newLast] = obj;
    i = newLast;
    inb4 = i>0 ? (i-1) : (data->size-1);

    while(i != data->first ? (compare(data->array[i], data->array[inb4]) < EQUALS) : (0)){
      data->stats.movimentou++;
      aux = data->array[i];
      data->array[i] = data->array[inb4];
      data->array[inb4] = aux;
      i=inb4;
      inb4 = i>0 ? (i-1) : (data->size-1);
    }

    data->last = newLast;

  }else{
    data->array[++data->last] = obj;
    data->first = data->last;
  }
  data->stats.inseriu++;

}


static void* Pell(TQueue *queue){
  TQueueData *data = queue->data;
  int newFirst;
  void *retorno;
  int breadth = GetBreadth(queue);
  if(breadth>0){
    if(breadth==1){
      retorno = data->array[data->first];
      data->first = data->last = -1;
    }else{
      retorno = data->array[data->first];
      newFirst = (data->first+1) % data->size;
      data->first = newFirst;
    }
    data->stats.removeu++;
    return retorno;
  }else{
    return NULL;
  }
}

static void Analytics(TQueue *f){
  TQueueData *d = f->data;
  printf("inserções:%d\n", d->stats.inseriu);
  printf("removeu:%d\n", d->stats.removeu);
  printf("movimentou:%d\n", d->stats.movimentou);
  printf("sobrecarga:%d\n", d->stats.sobrecarregou);
}

static short Empty(TQueue *q){
  return GetBreadth(q)<=0;
}

TQueue *new_Queue(){
  TQueue* queueP = (TQueue*)malloc(sizeof(TQueue));
  TQueueData *queueD =(TQueueData*)malloc(sizeof(TQueueData));
  queueP->data = queueD;
  queueD->array = malloc(sizeof(void*)*10);
  queueD->first = queueD->last = -1;
  queueD->size=10;
  queueP->insert=Insert;
  queueP->pell = Pell;
  queueP->analytics = Analytics;
  queueP->empty = Empty;
  queueD->stats.inseriu=0;
  queueD->stats.movimentou=0;
  queueD->stats.removeu=0;
  queueD->stats.sobrecarregou=0;
  return queueP;
}
