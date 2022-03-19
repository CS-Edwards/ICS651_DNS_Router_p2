/**server test area**/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "dnsutil.h"

#define PORT     12345   //changed from 8080
#define MAXINBUFF 65536 //atleast 65536 (defined in project spec)
#define MAXOUTBUFF 512  //512 bytes (defined in RFC)
#define TID 2 //transaction ID - 2 bytes


void printQuery(unsigned char *buffIn);


// Driver code
int main() {
    int sockfd;
    char buffer[MAXINBUFF]; 
    char buffout[MAXOUTBUFF];
    char *hello = "Hello from server"; //TODO Remove
    struct sockaddr_in servaddr, reqaddr;
    dnsPacket *packet;
    dnsReply  *reply_packet;
    
    //offset for buffer
    int *offset = calloc(1,sizeof(int));
    int o_init=0;
    
    memcpy(offset,&o_init,sizeof(int));
    
       
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&reqaddr, 0, sizeof(reqaddr));
       
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
    int len, r; 
   
    len = sizeof(reqaddr);  //len is value/resuslt
   
    r = recvfrom(sockfd,buffer, MAXINBUFF, 
                0, ( struct sockaddr *) &reqaddr,
                &len); //r is request size
     
     
     packet=calloc(1,sizeof(dnsPacket)); //allocate memory for one dnsPacket; set allocated memory to 0           
     processDNS(packet, buffer, r); 
     printPacket(packet);          
                
    
    //buffer[n] = '\0';
    //printf("Client : %s\n", buffer);
    
    //print data from dig query
    //printQuery(buffer);
    
    /******DNS Response Build*******/
    
    //Transaction ID, first two bytes of query
    unsigned char transID[TID]; //
    
    
    
    
    int size = sizeof(transID)/sizeof(transID[0]);
    
    //copy first two bytes from buffer for transaction ID
    for(int i=0;i<size;i++){
      transID[i] = buffer[i];    
    }
    
    printf("\n Transaction ID: ");
    for(int i=0;i<size;i++){
    	printf("%X ",transID[i]);
    	to_buff(&transID[i],buffout,offset);
        }
    printf("\n");
    
    //FLAGS: Response
    u_int8_t flags=10000100 & 0xFF; //QR response bit on (1), AA on (1)
    u_int8_t flags2=00000000 & 0xFF;
    
    //u_int8_t flags=0xE4;
    //u_int8_t flags2=0x00; 
    //u_int16_t flags = 0x8400;
        
    //printf("\n u_int8_t response= [%u] \n",flags);
    to_buff(&flags,buffout,offset);
    
    //printf("\n u_int8_t response= [%u] \n",flags2);
    to_buff(&flags2,buffout,offset);
    
    //QDCOUNT
    
    
    //ANCOUNT
    
    
    //NSCOUNT
    
    
    //ARCOUNT
    
    
    /**************************/
    //response
    
    reply_packet=calloc(1,sizeof(dnsReply));
    
    
    //sendto(sockfd, (const char *)hello, strlen(hello), 
     //   MSG_CONFIRM, (const struct sockaddr *) &reqaddr,
      //      len);
    
    
    sendto(sockfd, buffout, sizeof(buffout)/sizeof(buffout[0]), 
        MSG_CONFIRM, (const struct sockaddr *) &reqaddr,
            len);
            
            
    printf("Hello message sent.[%d] \n",j);
    j++;
    
    } 
    
    free(packet); //free allocated memory   
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

