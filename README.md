<h2 align=center> CSN 232 Assignment 6 </h2>

<h4 align=center> Starve-Free Readers Writers Problem </h4>

SEMAPHORES 
- rw_queue : It is used to maintain the order in which readers and writers arrive.
- r_mutex : It is used to provide mutual exclusion to r_count variable responsible for counting number of readers in the critical section.
- resource : It is used to prevent readers and writers  or multiple wirters to be present in critical section at the same time.

Shared variables
- r_count : It is used to count number of readers present in critical section at any given time.
- data : It is the part of program that is shared among various threads.

Reader function
- Entry section : This section acquires required semaphores to enter critical section.
  - Reader tries to acquires rw_queue SEMAPHORE initially, if it is unavailable, reader is added to queue for the given SEMAPHORE.
  - After aquiring rw_queue, it tries to aquire r_mutex SEMAPHORE to modify r_count.
  - If it is the first reader, it tries to aquire resource SEMAPHORE to confirm there are no writers in the critical section.
  - It releases rw_queue and r_mutex before entering critical section.
- Critical section : Reader reads the shared data in this section.
- Exit section : This section releases the aquired semaphores.
  - Reader tries to aquire r_mutex to modify r_count.
  - If it is the last reader, it releases resource SEMAPHORE.
  - It releases r_mutex at the end.

Writer function
- Entry section : This section acquires required semaphores to enter critical section.
  - Writer tries to acquires rw_queue SEMAPHORE initially, if it is unavailable, writer is added to queue for the given SEMAPHORE.
  - After aquiring rw_queue, it tries to aquire resource SEMAPHORE and enter critical section.
  - It releases rw_queue before entering critical section.
- Critical section : Writer modifies the shared data in this section.
- Exit section : This section releases the aquired semaphores.
  - Writer releases the resource SEMAPHORE.


Main function
- It takes number of readers and writers as input from the user.
- Then it creates required number of threads followed by initialisation of semaphores.
- It then initialises reader threads with reader function and writer threads with writer function.
- Then, all threads are joined back to the parent thread.
- After the execution, all initialized semaphores are destroyed.
