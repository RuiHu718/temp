#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct{
  int agentID;
  int numTicketsToSell;
} arguments;

void* sellTickets(void *ptr);

int main() {
  int numAgents = 10;
  int numTickets = 150;

  int agent;
  pthread_t threads[numAgents];
  void* retvals[numAgents];
  arguments argArray[numAgents];
    
  int count;
  for (count = 0; count < numAgents; ++count) {
    argArray[count].agentID = count + 1;
    argArray[count].numTicketsToSell = numTickets / numAgents;
    arguments* myargsp;
    myargsp = &argArray[count];
    if (pthread_create(&threads[count], NULL, sellTickets, (void*)myargsp) != 0) {
      fprintf(stderr, "error: Can't create thread # %d\n", count);
      break;
    } else {
      //printf("creating thread # %d\n", count);
      //printf("creating thread # %ld\n", pthread_self());      
    }
  }

  int i;
  for (i = 0; i < count; ++i)
    {
      if (pthread_join(threads[i], &retvals[i]) != 0)
        {
          fprintf(stderr, "error: Cannot join thread # %d\n", i);
        }
    }
  
  return 0;
}

void* sellTickets(void *ptr) {
  printf("thread # %ld running\n", pthread_self());        
  int num = ((arguments*)ptr)->numTicketsToSell;
  int id = ((arguments*)ptr)->agentID;
  //printf("this is my agentID: %d", id);
  while (num > 0) {
    printf("Agent %d sells a ticket\n", id);
    num--;
  }
  printf("Agent %d all done\n", id);
}
