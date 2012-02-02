/* Basic Non-Threaded Solution */
/* By Andy Sayler */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "util.h"

#define DEBUG 1

#define MINARGS 3
#define USAGE "<inputFilePath> <outputFilePath>"
#define SBUFSIZE 1025
#define INPUTFS "%1024s"

int main(int argc, char* argv[]){

    /* Local Vars */
    FILE* inputfp = NULL;
    FILE* outputfp = NULL;
    char hostname[SBUFSIZE];
    char firstipstr[INET6_ADDRSTRLEN];
        
    /* Check Arguments */
    if(argc < MINARGS){
	fprintf(stderr, "Not enough arguments: %d\n", (argc - 1));
	fprintf(stderr, "Usage:\n %s %s\n", argv[0], USAGE);
	return EXIT_FAILURE;
    }

    /* Open Files */
    inputfp = fopen(argv[1], "r");
    if(!inputfp){
	perror("Error Opening Input File");
	return EXIT_FAILURE;
    }
    
    outputfp = fopen(argv[2], "w");
    if(!outputfp){
	perror("Error Opening Output File");
	return EXIT_FAILURE;
    }

    /* Read File and Process*/
    while(fscanf(inputfp, INPUTFS, hostname) > 0){
	
	/* Lookup hostname and get IP string */
	if(dnslookup(hostname, firstipstr, sizeof(firstipstr))
	   == UTIL_FAILURE){
	    fprintf(stderr, "dnslookup error\n");
	    return EXIT_FAILURE;
   	}
	
	/* Write to Output File */
	fprintf(outputfp, "%s,%s\n", hostname, firstipstr);

    }

    /* Close Files */
    fclose(inputfp);
    fclose(outputfp);

    return EXIT_SUCCESS;
}
