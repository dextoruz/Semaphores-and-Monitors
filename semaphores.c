#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

int myGlobal = 0;
int S=1;

void Wait(int* s)
{
  while (*s<= 0){
    // printf("%s\n", "waiting");
  }
  *s-=1;
}

void Signal(int* s)
{
  *s+=1;
}

void *threadFunction()
{
  int i, j;
  for (i = 0; i<5; i++){
    Wait(&S);

    j = myGlobal;
    j = j+1;
    myGlobal = j;

    printf("\n My Global Is: %d\n", myGlobal);
    Signal(&S);
  }

}

int main()
{
  pthread_t myThread1,myThread2,myThread3,myThread4;
  int i,k;

  pthread_create(&myThread1, NULL,threadFunction,NULL);
  pthread_create(&myThread2, NULL,threadFunction,NULL);
  pthread_create(&myThread3, NULL,threadFunction,NULL);
  pthread_create(&myThread4, NULL,threadFunction,NULL);


  pthread_join(myThread1, NULL);
  pthread_join(myThread2, NULL);
  pthread_join(myThread3, NULL);
  pthread_join(myThread4, NULL);


  printf("\nMy Global Is: %d\n", myGlobal);
exit(0);
}
