/* my generic stack header file*/

#include <stdlib.h>
#include <iostream>
#include <assert.h>

typedef struct {
  void *elems;
  int elemSize;
  int loglength;
  int alloclength;
  void (*freefn)(void *);
} myGenericStack;

void myGenericStackNew(myGenericStack *s, int elemSize, void (*freefn)(void *));
void myGenericStackDispose(myGenericStack *s);
void myGenericStackPush(myGenericStack *s, void* elemAddr);
void myGenericStackPop(myGenericStack *s, void* elemAddr); /* note this signature is different from the int implementation */
