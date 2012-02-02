/*
 * File: queue.c
 * Author: Chris Wailes <chris.wailes@gmail.com>
 * Author: Wei-Te Chen <weite.chen@colorado.edu>
 * Author: Andy Sayler <andy.sayler@gmail.com>
 * Project: CSCI 3753 Programming Assignment 2
 * Create Date: 2010/02/12
 * Modify Date: 2011/02/04
 * Modify Date: 2012/02/01
 * Description:
 * 	This file contains an implementation of a simple FIFO queue.
 *  
 */

#include <stdlib.h>

#include "queue.h"

/*
 * void queue_init(queue* q, int size)
 * 
 * This function must be called on any queue before it is used.
 * 
 */
int queue_init(queue* q, int size) {
    /* malloc array */
    int i;

    if(size>0) {
	q->maxSize = size;
    }
    else {
	q->maxSize = QUEUEMAXSIZE;
    }

    q->array = malloc(sizeof(queue_node) * (q->maxSize));
    if(!(q->array)){	
	perror("Error on queue Malloc");
	return QUEUE_FAILURE;
    }

    for(i=0; i < q->maxSize; ++i){
	q->array[i].payload = NULL;
    }

    // setup other value
    q->front = 0;
    q->rear = 0;

    return q->maxSize;
}

/*
 * int queue_is_empty(queue* q)
 * 
 * Returns 1 if the queue is empty, 0 otherwise.
 * 
 */
int queue_is_empty(queue* q) {
    if((q->front == q->rear) && (q->array[q->front].payload == NULL)) {
	return 1;
    } else {
	return 0;
    }
}

/*
 * int queue_is_full(queue *q)
 *
 * Return 1 if the queue is full, 0 otherwise.
 *
 */
int queue_is_full(queue* q) {
    if((q->front == q->rear) && (q->array[q->front].payload != NULL)) {
	return 1;
    } else {
	return 0;
    }
}

/*
 * void* queue_pop(queue* q)
 * 
 * Returns an element from the queue in FIFO order.
 * 
 */
void* queue_pop(queue* q) {
    void* ret_payload;
	
    if(queue_is_empty(q)) {
	//This is an empty queue.  Return NULL.
	return NULL;
    }
	
    ret_payload = q->array[q->front].payload;
    q->array[q->front].payload = NULL;
    q->front = ((q->front + 1) % q->maxSize);

    //Return the pyload.
    return ret_payload;
}

/*
 * void queue_push(queue* q, void* new_payload)
 * 
 * Puts an item onto the end of the FIFO queue.
 * Returns QUEUE_SUCCESS if the push successeds.
 * Returns QUEUE_FAILURE if the push fails
 * 
 */
int queue_push(queue* q, void* new_payload) {
    
    if(queue_is_full(q)){
	return QUEUE_FAILURE;
    }

    q->array[q->rear].payload = new_payload;

    q->rear = ((q->rear+1) % q->maxSize);

    return QUEUE_SUCCESS;
}

void queue_cleanup(queue* q)
{
    while(!queue_is_empty(q)) {
	queue_pop(q);
    }

    free(q->array);
}
