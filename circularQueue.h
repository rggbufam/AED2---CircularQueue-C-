#ifndef _XYAH_CIRCULARQUEUE_H_
#define _XYAH_CIRCULARQUEUE_H_

#define desenfileirar(x) pell(x)
#define enfileirar(x,y) insert(x,y)
#define vazia(x) empty(x)

typedef struct typeQueue TQueue;

typedef void(*FInsert)(TQueue*,void*);
typedef void*(*FPell)(TQueue*);
typedef short(*FEmpty)(TQueue*);
typedef void (*FAnalytics)(TQueue*);

typedef struct typeQueue{
  void* data;
  FInsert insert;
  FPell pell;
  FEmpty empty;
  FAnalytics analytics;
}TQueue;

TQueue *new_Queue();

#endif ///_XYAH_CIRCULARQUEUE_H_
