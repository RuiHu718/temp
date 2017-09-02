#include "myGenericStack.h"

void myGenericStackNew(myGenericStack *s, int elemSize, void (*freefn)(void *)) {
  s->elemSize = elemSize;
  s->loglength = 0;
  s->alloclength = 4;
  s->elems = malloc(4*elemSize);
  assert(s->elems != NULL);
}

void myGenericStackDispose(myGenericStack *s) {
  if (s->freefn != NULL) {
    for (int i = 0; i < s->loglength; i++) {
      s->freefn((char *)s->elems + i * s->elemSize);
    }
  }
  free(s->elems);
}

/* static means this is a private function not advertised outside of this file (internal linkage) */
static void myGenericStackGrow(myGenericStack *s) {
  s->alloclength *= 2;
  s->elems = realloc(s->elems, s->alloclength * s->elemSize);
  assert(s->elems != NULL);
}

void myGenericStackPush(myGenericStack *s, void* elemAddr) {
  if (s->loglength == s->alloclength) {
    myGenericStackGrow(s);
  }
  void* target = (char *) s->elems + s->loglength * s->elemSize; // find the address
  memcpy(target, elemAddr, s->elemSize);
  (s->loglength)++;
}

/* why not return the element directly? 42' of lecture explains this
 * the function which alloate memory should be the one to deallocate it 
 */
void myGenericStackPop(myGenericStack *s, void* elemAddr) {
  (s->loglength)--;
  void* source = (char *) s->elems + s->loglength * s->elemSize;
  memcpy(elemAddr, source, s->elemSize);
}
