
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<stdbool.h>

#define PIZZA 5

int pizza = 5;
bool havePizza = false;

pthread_mutex_t mutexx = PTHREAD_MUTEX_INITIALIZER;

void client(){
        pthread_mutex_lock(&mutexx);
            if(pizza > 0){
                printf("Client has eaten Pizza NO. %d\n", pizza);
                pizza--;
                havePizza = true;
            }
        pthread_mutex_unlock(&mutexx);
        printf("Pizzas remaining: %d\n" ,pizza);
}

void chef(){
        pthread_mutex_lock(&mutexx);
            if(pizza < 5){
                pizza++;
                havePizza = true;
                printf("Chef has Cooked Pizza NO. %d\n", pizza);
        }
        pthread_mutex_unlock(&mutexx);
}

 void * start_counting(void *arg)
 {
int test = 10;
while (test > 0)
{
    if (pizza != 5){
        chef();
     }else{
         client();
     }
test--;
}


 }

int main(void)
{
  int i=0;

  pthread_t thread1, thread2;

  pthread_create(&thread1,NULL, start_counting, NULL);
  pthread_create(&thread2,NULL, start_counting, NULL);

  pthread_join(thread1, NULL); // wait for all threads to finish
  pthread_join(thread2, NULL); // wait for all threads to finish

  return EXIT_SUCCESS;

}
