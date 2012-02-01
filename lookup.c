/* Basic Non-Threaded Solution */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define DEBUG 1

#define MINARGS 3
#define USAGE "<inputFilePath> <outputFilePath>"
#define SBUFSIZE 1025
#define INPUTFS "%1024s"

void getipaddress(const char* url, char* ipstr) {
	void *addr;
	int status;

	struct addrinfo hints, *servinfo;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
 
	if ((status = (getaddrinfo(url, NULL, &hints, &servinfo) != 0))) {
		printf("error! - %s\n", url);
		ipstr[0] = '\0';
	}
	else
	{
		struct sockaddr_in *ipv4 = (struct sockaddr_in *)servinfo->ai_addr;
		addr = &(ipv4->sin_addr);
		inet_ntop(servinfo->ai_family, addr, ipstr, INET_ADDRSTRLEN);
	}
}

int main(int argc, char* argv[]){

    /* Local Vars */
    FILE* inputfp = NULL;
    FILE* outputfp = NULL;
    char hostname[SBUFSIZE];
    struct addrinfo* headresult = NULL;
    struct addrinfo* result = NULL;
    struct sockaddr_in* ipv4sock = NULL;
    struct in_addr* ipv4addr = NULL;
    char ipv4str[INET_ADDRSTRLEN];
    char ipstr[INET6_ADDRSTRLEN];
    char firstipstr[sizeof(ipstr)];
    int addrError = 0;
    
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
	fprintf(stdout, "%s\n", hostname);

	/* Lookup Hostname */
	addrError = getaddrinfo(hostname, NULL, NULL, &headresult);
	if(addrError){
	    fprintf(stderr, "Error looking up Address: %s\n",
		    gai_strerror(addrError));
	    return EXIT_FAILURE;
	}
	/* Loop Through result Linked List */
	for(result=headresult; result != NULL; result = result->ai_next){
	    /* Extract IP Address and Convert to String */
	    if(result->ai_addr->sa_family == AF_INET){
		ipv4sock = (struct sockaddr_in*)(result->ai_addr);
		ipv4addr = &(ipv4sock->sin_addr);
		if(!inet_ntop(result->ai_family, ipv4addr, ipv4str, sizeof(ipv4str))){
		    perror("Error Converting IP to String");
		    return EXIT_FAILURE;
		}
		fprintf(stdout, "%s\n", ipv4str);
		strncpy(ipstr, ipv4str, sizeof(ipstr));
	    }
	    else{
		fprintf(stdout, "IPv6 Address: Not Handled\n");
		strncpy(ipstr, "UNHANDELED", sizeof(ipstr));
	    }
	    /* Save First IP Address */
	    if(result==headresult){
		strncpy(firstipstr, ipstr, sizeof(firstipstr));
	    }
	}
	/* Write to Output File */
	fprintf(outputfp, "%s,%s\n", hostname, firstipstr);

	/* Cleanup */
	freeaddrinfo(result);
    }

    /* Close Files */
    fclose(inputfp);
    fclose(outputfp);

    return EXIT_SUCCESS;
}
