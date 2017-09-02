#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_TOTAL_BUFFERS 8
#define DATA_LENGTH 40

typedef struct {
  sem_t emptyBuffers;
  sem_t fullBuffers;
  char* buffers;  
} arguments;

static void processData(char data) {
  printf("processing %c\n", data);
}

static char prepareData() {
  return 'S';
}

void* Writer(void *ptr) {
  int i, writePt = 0;
  char data;

  for (i = 0; i < DATA_LENGTH; i++) {
    data = prepareData();
    sem_wait(&((arguments*)ptr)->emptyBuffers);
    (((arguments*)ptr)->buffers)[writePt] = data;
    //buffers[writePt] = data;
    printf("%ld: buffer[%d] = %c\n", pthread_self(), writePt, data);
    writePt = (writePt + 1) % NUM_TOTAL_BUFFERS;
    sem_post(&((arguments*)ptr)->fullBuffers);    
    //sem_post(&fullBuffers);
  }
}

void* Reader(void *ptr) {
  int i, readPt = 0;
  char data;

  for (i = 0; i < DATA_LENGTH; i++) {
    //sem_wait(&fullBuffers);
    sem_wait(&((arguments*)ptr)->fullBuffers);    
    data = (((arguments*)ptr)->buffers)[readPt];    
    printf("\t\t%ld: buffer[%d] = %c\n", pthread_self(), readPt, data);
    readPt = (readPt + 1) % NUM_TOTAL_BUFFERS;
    sem_post(&((arguments*)ptr)->emptyBuffers);        
    //sem_post(&emptyBuffers);
    processData(data);
  }
}

int main() {
  sem_t emptyBuffers;
  sem_t fullBuffers;
  sem_init(&emptyBuffers, 0, NUM_TOTAL_BUFFERS);
  sem_init(&fullBuffers, 0, 0);
  char buffers[NUM_TOTAL_BUFFERS];
  pthread_t reader, writer;
  int rc1, rc2;

  arguments myarg;
  myarg.buffers = buffers;
  myarg.emptyBuffers = emptyBuffers;
  myarg.fullBuffers = fullBuffers;
  arguments* myargp;
  myargp = &myarg;

  pthread_create(&writer, NULL, Writer, (void*)myargp);
  pthread_create(&reader, NULL, Reader, (void*)myargp);  

  pthread_join(writer, NULL);
  pthread_join(reader, NULL);  
  
  sem_destroy(&emptyBuffers);
  sem_destroy(&fullBuffers);  
  printf("All done!\n");
  return 0;
}
