#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_DINERS 5
#define EAT_TIMES 3

#define LEFT(philNum) (philNum)
#define RIGHT(philNum) (((philNum)+1) % NUM_DINERS)

typedef struct {
  sem_t numEating;
  sem_t leftFork;
  sem_t rightFork;
} arguments;

void* Think() {
  printf("%ld thinking\n", pthread_self());
}

void* Eat(void* ptr) {
  sem_wait(&((arguments*)ptr)->numEating);
  sem_wait(&((arguments*)ptr)->leftFork);
  sem_wait(&((arguments*)ptr)->rightFork);

  printf("%ld eating\n", pthread_self());
  sem_post(&((arguments*)ptr)->leftFork);
  sem_post(&((arguments*)ptr)->rightFork);
  sem_post(&((arguments*)ptr)->numEating);            
}

void* Philosopher(void* ptr) {
  int i;
  for (i = 0; i < EAT_TIMES; i++) {
    Think();
    //Eat(((arguments *)ptr)->numEating, ((arguments *)ptr)->leftFork,
    //	((arguments *)ptr)->rightFork);
    Eat(ptr);
  }
}


int main() {
  int i;
  char name[32];
  sem_t fork[NUM_DINERS];
  sem_t numEating;
  pthread_t threads[NUM_DINERS];
  void* retvals[NUM_DINERS];
  arguments argArray[NUM_DINERS];

  for(i = 0; i < NUM_DINERS; i++) {
    sem_init(&fork[i], 0, 1);
  }
  sem_init(&numEating, 0, NUM_DINERS - 1);

  int count;
  for (count = 0; count < NUM_DINERS; ++count) {
    argArray[count].numEating = numEating;
    argArray[count].leftFork = fork[LEFT(count)];
    argArray[count].rightFork = fork[RIGHT(count)];
    arguments* myargsp;
    myargsp = &argArray[count];
    if (pthread_create(&threads[count], NULL, Philosopher, (void*)myargsp) != 0) {
      fprintf(stderr, "error: Can't create thread # %d\n", count);
      break;
    }
  }

  int j;
  for (j = 0; j < count; ++j){
    if (pthread_join(threads[j], &retvals[j]) != 0){
      fprintf(stderr, "error: Cannot join thread # %d\n", j);
    }
  }
  
  printf("All done!\n");
  sem_destroy(&numEating);
  for(i = 0; i < NUM_DINERS; i++) {
    sem_destroy(&fork[i]);
  }
  
  return 0;
}
