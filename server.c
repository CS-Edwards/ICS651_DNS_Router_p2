/**server test area**/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXINBUFF 67000 //atleast 65536 (defined in project spec)
#define MAXOUTBUFF 512  //512 bytes (defined in RFC)
#define TID 2 //transaction ID - 2 bytes

void printQuery(unsigned char *buffIn);


// Driver code
int main() {
    int sockfd;
    unsigned char buffer[MAXINBUFF]; //byte array
    char *hello = "Hello from server"; //TODO Remove
    struct sockaddr_in servaddr, cliaddr;
       
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
       
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
       
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    int j =0;//CE added iterator for loop
       
    while(1){   
    int len, n;
   
    len = sizeof(cliaddr);  //len is value/resuslt
   
    n = recvfrom(sockfd, (unsigned char *)buffer, MAXINBUFF, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
    //buffer[n] = '\0';
    //printf("Client : %s\n", buffer);
    
    //print data from dig query
    printQuery(buffer);
    
    /******DNS Response Build*******/
    
    //Transaction ID, first two bytes of query
    unsigned char transID[TID]; //= buffer[0:2];
    
    
    
    
    int size = sizeof(transID)/sizeof(transID[0]);
    
    //copy first two bytes from buffer for transaction ID
    for(int i=0;i<size;i++){
      transID[i] = buffer[i];    
    }
    
    printf("\n Transaction ID: ");
    for(int i=0;i<size;i++){
    	printf("%X ",transID[i]);
        }
    printf("\n");
    
    
    
    /**************************/
    //response
    sendto(sockfd, (const char *)hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
            
    printf("Hello message sent.[%d] \n",j);
    j++;
    
    } 
       
    return 0;
}

//TODO: add to dnstil.c and .h
//print data from dig query
void printQuery(unsigned char *buffIn){
 
 for(int i=0;i<MAXINBUFF;i++){
    	printf("%X ",buffIn[i]);
        }
    printf("\n");
}

