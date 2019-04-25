#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<semaphore.h>


int myGlobal = 0;
sem_t m;

void *threadFunction(void* t){
  int i, j;
  for (i = 0; i<5; i++){
    sem_wait(&m);

    j = myGlobal;
    j = j+1;
    myGlobal = j;
    printf("\n My Global Is: %d ---- threadNo: %d \n", myGlobal,t);

    sem_post(&m);

  }
}

int main()
{
  pthread_t myThread1,myThread2,myThread3,myThread4;
  if (sem_init(&m, 0, 1) == -1) {
    perror("Could not initialize mylock semaphore");
    exit(2);
  }
  int i = 1,k =2;

  pthread_create(&myThread1, NULL,threadFunction,(void*)i);
  pthread_create(&myThread2, NULL,threadFunction,(void*)k);
  i = 3; k = 4;
  pthread_create(&myThread3, NULL,threadFunction,(void*)i);
  pthread_create(&myThread4, NULL,threadFunction,(void*)k);


  pthread_join(myThread1, NULL);
  pthread_join(myThread2, NULL);
  pthread_join(myThread3, NULL);
  pthread_join(myThread4, NULL);

  printf("\nMy Global Is: %d\n", myGlobal);
exit(0);
}
