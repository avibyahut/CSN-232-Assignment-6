#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t rw_queue,resource,r_mutex;  // semaphore declarations

int r_count = 0;  // readers counter

int data = 1; // critical data to be shared

/*
 * this function have logic to write shared data
 */
void *writer(void *wid)
{   
    // ENTRY section
    sem_wait(&rw_queue);
    sem_wait(&resource);
    sem_post(&rw_queue);
    // ENTRY section end
    
    // CRITICAL section
    data = data*2;
    printf("Writer %d modified data to %d\n",(*((int *)wid)),data);
    // CRITICAL section end
    
    // EXIT section
    sem_post(&resource);
    // EXIT section end
}

/*
 * this function have logic to read shared data
 */
void *reader(void *rid)
{   
    // ENTRY section
    sem_wait(&rw_queue);
    sem_wait(&r_mutex);
    r_count++;
    if(r_count == 1) {
        sem_wait(&resource);
    }
    sem_post(&rw_queue);
    sem_post(&r_mutex);
    // ENTRY section end
    
    // CRITICAL section
    printf("Reader %d: read data as %d\n",*((int *)rid),data);
    // CRITICAL section end

    // EXIT section
    sem_wait(&r_mutex);
    r_count--;
    if(r_count == 0) {
        sem_post(&resource);
    }
    sem_post(&r_mutex);
    // EXIT section end
}

int main()
{   
    int READERS,WRITERS,MAX_ID;
    
    printf("Enter Number of Readers: ");
    scanf("%d", &READERS);
    
    printf("Enter Number of Writers: ");
    scanf("%d", &WRITERS);
    
    MAX_ID = READERS >= WRITERS ? READERS : WRITERS;
    
    int id_arr[MAX_ID];
    for(int i = 0; i < MAX_ID; i++) id_arr[i] = i+1;
    

    pthread_t read[READERS],write[WRITERS]; // tread creation
    
    // semaphore initialisation
    sem_init(&rw_queue,0,1);
    sem_init(&r_mutex,0,1);
    sem_init(&resource,0,1);

    for(int i = 0; i < READERS; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&id_arr[i]);
    }
    for(int i = 0; i < WRITERS; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&id_arr[i]);
    }

    for(int i = 0; i < READERS; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < WRITERS; i++) {
        pthread_join(write[i], NULL);
    }

    //destroying threads at the end of execution
    sem_destroy(&rw_queue);
    sem_destroy(&r_mutex);
    sem_destroy(&resource);

    return 0;
    
}