/*
 * File: util.h
 * Author: Andy Sayler
 * Project: CSCI 3753 Programming Assignment 2
 * Create Date: 2012/02/01
 * Modify Date: 2012/02/01
 * Description:
 * 	This file contains declarations of utility functions for
 *      Programming Assignment 2.
 *  
 */

#ifndef UTIL_H
#define UTIL_H

/* Define the following to enable debug statments */
// #define UTIL_DEBUG

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define UTIL_FAILURE -1
#define UTIL_SUCCESS 0

/* Fuction to return the first IP address found
 * for hostname. IP address returned as string
 * firstIPstr of size maxsize
 */
int dnslookup(const char* hostname,
	      char* firstIPstr,
	      int maxSize);

#endif
