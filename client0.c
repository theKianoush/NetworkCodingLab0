#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>


// Created by Dave Ogle
// Edited by Kianoush Ranjbar
/**********************************************************************/
/* This is a sample client file. You can use it to make sure you know */
/* how to compile code, learn more about sockets, etc.                */
/* make this code your own. Comment it, understand it, restructure it */
/* I expect to see your create functions and NOT submit this as one   */
/* large main() function                                              */
/**********************************************************************/
							       

int main(int argc, char *argv[])
{

  int sd; /* the socket descriptor */
  struct sockaddr_in server_address;  /* structures for addresses */
  struct sockaddr_in inaddr;  /* structures for checking addresses */
  int rc;
  int i; /* loop variable */
  char bufferOut [100];
  char serverIP[20]; // provided by the user on the command line */
  int portNumber = 0; // provided by the user on the command line
  /* check to see if the right number of parameters was entered */
  if (argc < 3){
    printf ("Error: enter <IP Address> first then <Port Number> as parameters\n");
    exit(1); /* just leave if wrong number entered */
  }

  /* this code checks to see if the ip address is a valid ip address */
  /* meaning it is in dotted notation and has valid numbers          */
  if (!inet_pton(AF_INET, argv[1], &inaddr)){
    printf ("Error: enter a valid IP Address (with dotted notation and valid numbers)\n");
    exit (1); /* just leave if is incorrect */
  }
  
//------------------------------------------------------------------------
  /* first create a socket */
  sd = socket(AF_INET, SOCK_DGRAM, 0); /* create a socket */
  /* what should you do if the socket descriptor is not valid */

  /* check that the port number is a number..... */

  for (i=0;i<strlen(argv[2]); i++){
    if (!isdigit(argv[2][i]))
      {
	printf ("Error: the port number must be a numerical integer\n");
	exit(1);
      }
  }
//------------------------------------------------------------------------
// Create ip address

  portNumber = strtol(argv[2], NULL, 10); /* many ways to do this */
  /* exit if a portnumber too big or too small  */
  if ((portNumber > 65535) || (portNumber < 0)){
    printf ("Error: you entered an invalid port number out of the range of 0-65535\n");
    exit (1);
  }
  
  strcpy(serverIP, argv[1]); /* copy the ip address */

  server_address.sin_family = AF_INET; /* use AF_INET addresses */
  server_address.sin_port = htons(portNumber); /* convert port number */
  server_address.sin_addr.s_addr = inet_addr(serverIP); /* convert IP addr */
  
//------------------------------------------------------------------------
// send message
	
  memset (bufferOut, 0, 100); // ALWAYS null out buffers in C before using them
  sprintf (bufferOut, "hello world");

  rc = sendto(sd, bufferOut, strlen(bufferOut), 0,
	      (struct sockaddr *) &server_address, sizeof(server_address));
  
  /* Check the RC and figure out what to do if it is 'bad' */
  /* what is a bad RC from sendto?                         */
	// if the buffer out is overflowed, or if the socket descriptor is invalid
  if (rc < strlen(bufferOut)){
    perror ("Error: there was an error when trying to send the message");
    // do i exit?
	exit (1);
	// yes, so we can fix the error
  }
  


}
