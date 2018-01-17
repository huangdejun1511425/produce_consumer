#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>  
#define MAX 20
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
sem_t empty_sem;
sem_t full_sem;
sem_t mutex;
int buffer = 0;
int count = 1;
int count1 = 1;

void *producer(void *ptr)
{
    while(count <=50){
	sem_wait(&empty_sem);
	sem_wait(&mutex);
        //pthread_mutex_lock(&the_mutex);	
	printf("produce %d: %d ",(int)ptr,count);
	for(int i = 0;i < (count - 1)%10 + 1;i++){
		printf("+");
	}
	printf("\n");
	++count;
	sem_post(&full_sem);
	sem_post(&mutex);
	//pthread_cond_signal(&condc);
	//pthread_mutex_unlock(&the_mutex);
	
    }
    pthread_exit(0);
}

void *consumer(void *ptr)
{
    int i;
    while(count1 <=50){
	sem_wait(&full_sem);
	sem_wait(&mutex);
	//pthread_mutex_lock(&the_mutex);	
	printf("consume %d: %d ", (int)ptr, count1);
	for(int i = 0;i < (50 - count1)%10;i++){
		printf("-");
	}
	printf("\n");
	count1++;
	sem_post(&empty_sem);
	sem_post(&mutex);
	//pthread_cond_signal(&condp);
	//pthread_mutex_unlock(&the_mutex);
	
    }
    pthread_exit(0);
}

int main(int argc,char **argv)
{
	pthread_t tid1,tid2,tid3,tid4,tid5,tid6;
	pthread_mutex_init(&the_mutex,0);
	pthread_cond_init(&condc, 0);
	pthread_cond_init(&condp, 0);
	sem_init(&mutex,1,1);
	sem_init(&empty_sem,0,10);
	sem_init(&full_sem,0,0);
	pthread_create(&tid1,0,consumer,(void*)1);
	pthread_create(&tid2,0,producer,(void*)1);
	pthread_create(&tid3,0,consumer,(void*)2);
	pthread_create(&tid4,0,producer,(void*)2);
	//pthread_create(&tid5,0,consumer,(void*)3);
	pthread_create(&tid6,0,producer,(void*)3);
	pthread_join(tid1,0);
	pthread_join(tid2,0);
	pthread_join(tid3,0);
	pthread_join(tid4,0);
	//pthread_join(tid5,0);
	pthread_join(tid6,0);
	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	pthread_mutex_destroy(&the_mutex);
}
