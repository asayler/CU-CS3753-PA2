/*
 * File: queueTest.c
 * Author: Andy Sayler
 * Project: CSCI 3753 Programming Assignment 2
 * Create Date: 2012/02/05
 * Modify Date: 2012/02/05
 * Description:
 * 	This file contains test code for the included
 *      queue.
 *  
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "queue.h"

#define TEST_SIZE 10

int main(int argc, char* argv[]){

    /* Void Unused Variables */
    (void) argc;
    (void) argv;

    /* Setup local vars */
    queue q;
    int i;
    const int qSize = TEST_SIZE;
    int* payload_in[TEST_SIZE];
    int* payload_out[TEST_SIZE];

    /* Setup payload_in as int* array from
     * 0 to TEST_SIZE-1 */
    for(i=0; i<TEST_SIZE; i++){
	payload_in[i] = 
	    malloc(sizeof(*(payload_in[i])));
	*(payload_in[i]) = i;
    }

    /* Setup payload_out as int* array of NULL */
    for(i=0; i<TEST_SIZE; i++){
	payload_out[i] = NULL;
    }

    /* Initialize Queue */
    if(queue_init(&q, qSize) == QUEUE_FAILURE){
	fprintf(stderr,
		"error: queue_init failed!\n");
    }

    /* Test for empty queue when empty */
    if(!queue_is_empty(&q)){
	fprintf(stderr,
		"error: queue should report empty\n");
	fprintf(stderr,
		"queue_is_empty reports that"
		"the queue is not empty\n");
    }

    /* Test for full queue when empty */
    if(queue_is_full(&q)){
	fprintf(stderr,
		"error: queue should report empty\n");
	fprintf(stderr,
		"queue_is_full reports that"
		"the queue is full\n");
    }

    /* Test queue push */
    for(i=0; i<TEST_SIZE; i++){
	if(queue_push(&q, payload_in[i])
	   == QUEUE_FAILURE){
	    fprintf(stderr,
		    "error: queue_push failed!\n"
		    "Payload Index: %d, Value: %d\n",
		    i, *(payload_in[i]));
	}
    }

    /* Test for empty queue when full */
    if(queue_is_empty(&q)){
	fprintf(stderr,
		"error: queue should report full\n");
	fprintf(stderr,
		"queue_is_empty reports that"
		"the queue is empty\n");
    }

    /* Test for full queue when full */
    if(!queue_is_full(&q)){
	fprintf(stderr,
		"error: queue should report full\n");
	fprintf(stderr,
		"queue_is_full reports that"
		"the queue is not full\n");
    }

    /* Test that push fails when full */
    if(!queue_push(&q, payload_in[0])
       == QUEUE_FAILURE){
	fprintf(stderr,
		"error: queue_push did not fail"
		" when full!\n");
    }
    
    /* Test queue pop */
    for(i=0; i<TEST_SIZE; i++){
	if((payload_out[i] = queue_pop(&q)) == NULL){
	    fprintf(stderr,
		    "error: queue_pop failed!\n"
		    "Payload Index: %d, Value: %d\n",
		    i, *(payload_in[i]));
	}
    }

    /* Compare */
    for(i=0; i<TEST_SIZE; i++){
	if(payload_in[i] != payload_out[i]){
	    fprintf(stderr,
		    "error: push/pop mismatch!\n"
		    "Payload Index: %d, "
		    "Input Value: %d, "
		    "Output Value: %d\n",
		    i, *(payload_in[i]),
		    *(payload_out[i]));
	}
    }

    /* Test for empty queue when empty */
    if(!queue_is_empty(&q)){
	fprintf(stderr,
		"error: queue should report empty\n");
	fprintf(stderr,
		"queue_is_empty reports that"
		"the queue is not empty\n");
    }

    /* Test for full queue when empty */
    if(queue_is_full(&q)){
	fprintf(stderr,
		"error: queue should report empty\n");
	fprintf(stderr,
		"queue_is_full reports that"
		"the queue is full\n");
    }

    /* Test that pop fails when empty */
    if(queue_pop(&q)){
	fprintf(stderr,
		"error: queue_pop did not return"
		" NULL when empty!\n");
    }

    /* Cleanup Queue */
    queue_cleanup(&q);

    /* Cleanup payload_in */
    for(i=0; i<TEST_SIZE; i++){
	free(payload_in[i]);
    }

    return 0;
}
