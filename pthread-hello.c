/******************************************************************************
 * FILE: pthread_hello.c
 * DESCRIPTION:
 *   A "hello world" Pthreads program.  Demonstrates thread creation and
 *   termination.
 * AUTHOR: Blaise Barney, Junho Ahn, Andy Sayler
 * LAST REVISED: 02/08/12
 ******************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS	5

/* Function for Each Thread to Run */
void* PrintHello(void* threadid)
{
    /* Setup Local Vars and Handle void* */
    long* tid = threadid;
    long t;
    long numprint = 3;

    /* Print hello numprint times */
    for(t=0; t<numprint; t++)
	{
	    printf("Hello World! It's me, thread #%ld! "
		   "This is printout %ld of %ld\n",
		   *tid, (t+1), numprint);
	    /* Sleep for 1 to 2 Seconds */
	    usleep((rand()%100)*10000+1000000);
	}
    
    /* Exit, Returning NULL*/
    return NULL;
}

int main(int argc, char *argv[])
{
    /* void unused vars */
    (void) argc;
    (void) argv;

    /* Setup Local Vars */
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    long cpyt[NUM_THREADS];
    
    /* Spawn NUM_THREADS threads */
    for(t=0;t<NUM_THREADS;t++){
	printf("In main: creating thread %ld\n", t);
	cpyt[t] = t;
	rc = pthread_create(&(threads[t]), NULL, PrintHello, &(cpyt[t]));
	if (rc){
	    printf("ERROR; return code from pthread_create() is %d\n", rc);
	    exit(EXIT_FAILURE);
	}
    }
    
    /* Wait for All Theads to Finish */
    for(t=0;t<NUM_THREADS;t++){
	pthread_join(threads[t],NULL);
    }
    printf("All of the threads were completed!\n");
    

    /* Last thing that main() should do */
    /* pthread_exit unnecessary due to previous join */ 
    //pthread_exit(NULL);

    return 0;
}
