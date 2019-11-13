#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 

#define N 5 
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
#define LEFT (philnum + 4) % N 
#define RIGHT (philnum + 1) % N 

int state[N]; 
int phil[N] = { 0, 1, 2, 3, 4 }; 

sem_t mutex; 
sem_t S[N]; 

void test(int philnum) 
{ 
	if (state[philnum] == HUNGRY 
		&& state[LEFT] != EATING 
		&& state[RIGHT] != EATING) { 
		// state that eating 
		state[philnum] = EATING; 

		sleep(2); 

		printf("Philosopher %d takes chopstick %d and %d\n", 
					philnum + 1, LEFT + 1, philnum + 1); 

		printf("Philosopher %d eats\n", philnum + 1); 


		sem_post(&S[philnum]); 
	} 
} 

void take_fork(int philnum) 
{ 

	sem_wait(&mutex); 

	state[philnum] = HUNGRY; 

	printf("Philosopher %d feels hungry\n", philnum + 1); 

	test(philnum); 

	sem_post(&mutex); 

	sem_wait(&S[philnum]); 

	sleep(1); 
} 

void put_fork(int philnum) 
{ 

	sem_wait(&mutex); 

	state[philnum] = THINKING; 

	printf("Philosopher %d puts chopstick %d and %d down\n", 
		philnum + 1, LEFT + 1, philnum + 1); 
	printf("Philosopher %d thinks\n", philnum + 1); 

	test(LEFT); 
	test(RIGHT); 

	sem_post(&mutex); 
} 


void* philospher(void* num) 
{ 
  
    while (1) { 
  
        int* i = num; 
  
        sleep(1); 
  
        take_fork(*i); 
  
        sleep(0); 
  
        put_fork(*i); 
    } 
} 

int main() 
{ 

	int i; 
	pthread_t thread_id[N]; 

	sem_init(&mutex, 0, 1); 

	for (i = 0; i < N; i++) 

		sem_init(&S[i], 0, 0); 

	for (i = 0; i < N; i++) { 

		pthread_create(&thread_id[i], NULL, 
					philospher, &phil[i]); 

		printf("Philosopher %d thinks\n", i + 1); 
	} 

	for (i = 0; i < N; i++) 

		pthread_join(thread_id[i], NULL); 
} 
