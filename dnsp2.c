/**Domain Name Server**/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "dnsutil.h"
#include "rr_linkedlist.h"






int main(int argc, char* argv[]){

	//****Command Line Processing****//
	int i,j,portnum =0;
	Address addressArr[argc];
	
	

	if(argc==1){
		printf("No arguments passed into main \n program terminating\n ");
		return -1; 
	}
	
	portnum=atoi(argv[1]);
	printf("\n Port number set to: %d \n",portnum);
	printf("\n This DNS Server handles requests for  the following domain.name/ip.address(es) \n");
	
	
	/*head of resource rec list*/
	char *testname ="www.default.com";
	char *ip= "0:0:0:0";
	dnsRR* ptr = new_record(testname, ip,col_search(ip) );
	
	for(i=2; i<argc;i++){ 
		printf("\n argv[%d]: %s \n",i,argv[i]);
		char *in,*domainset,*ipset;
		in=(char *)malloc(sizeof(argv[i]));
		strcpy(in,argv[i]);
		
		domainset = strtok(in,"/"); //returns domain name
 		ipset =  strtok(NULL,"/"); //returns IP address 
 		
 		ptr = add_record(ptr, domainset, ipset, col_search(ipset));
       	//print_rr(ptr);
		
	}//close for loop
	
	print_rr(ptr);// print rr list
	
	//*****SERVER: SETUP***//
	int sockfd,k; //k server loop count
    	int *offset = calloc(1,sizeof(int));
    	int o_init=0;
	
	char buffer[MAXINBUFF]; 
    	char buffout[MAXOUTBUFF];
    	
    	struct sockaddr_in servaddr, reqaddr;
    	dnsPacket *packet;
    	
    	
	
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("SOCKET CREATION ERROR");
        exit(EXIT_FAILURE);
    	}
	
	memcpy(offset,&o_init,sizeof(int));
	memset(&servaddr, 0, sizeof(servaddr));
    	memset(&reqaddr, 0, sizeof(reqaddr));
    	
    	servaddr.sin_family    = AF_INET; // IPv4
    	servaddr.sin_addr.s_addr = INADDR_ANY;
    	servaddr.sin_port = htons(portnum);//set by main args
    	
    	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
       k =0;//server loop counter
       
       
       //*****SERVER: RUN***//
       printf("\n Server initialized... \n");
       while(1){ 
       	int len, r; //r = requestsize
   		len = sizeof(reqaddr);  //len is value/resuslt
   		printf("\n Awaiting [DIG] initialized... \n");
    		//recv DIG query
    		r = recvfrom(sockfd,buffer, MAXINBUFF, 
                0, ( struct sockaddr *) &reqaddr,
                &len); //r is request size
     
     
     		packet=calloc(1,sizeof(dnsPacket)); 
     
              
     		char* qname = processDNS(packet, buffer, r); 
     		printPacket(packet); 
     		
     		//Check query agains rrecords
     		printf("\n ...searching for matching resource records...\n");
		printf("\n ...result: [%s] \n",(NULL==dns_rr_query_match(qname, ptr))?"NO MATCH FOUND":"MATCH FOUND"); 
		
		//DNS REPLY
		unsigned char transID[TID]; //
    		int size = sizeof(transID)/sizeof(transID[0]);
    
    		//copy first two bytes from buffer for transaction ID
    		for(int i=0;i<size;i++){
      			transID[i] = buffer[i];    
    		}
    
   		printf("\n Transaction ID: ");
    		for(int i=0;i<size;i++){
    			printf("%X",transID[i]);
    			to_buff(&transID[i],buffout,offset); //send to buffer
        	}
        	
    		//printf("%X %X ",transID[0],transID[1]);
    		printf("\n");
    		
    		//FLAGS: Response [TODO: FIX -malformed packet error in wireshark]
    		u_int8_t flags=10000100 & 0xFF; //QR response bit on (1), AA on (1)
    		u_int8_t flags2=00000000 & 0xFF;
    		to_buff(&flags,buffout,offset);
    		to_buff(&flags2,buffout,offset);
    		
    		//**[TODO:FULL DNS REPLY DOES NOT FUNCTION YET]**//
    		
    		
    		//sends malformed reply for DIG Query
    		sendto(sockfd, buffout, sizeof(buffout)/sizeof(buffout[0]), 
        MSG_CONFIRM, (const struct sockaddr *) &reqaddr,
            len);
            
            printf("\n DNS Reply Sent// Query terminated.[%d] \n",k);
    	    k++;
    	    printf("\n Server listening...\n");
		
       	
       }
       
       free(ptr);
	
	
	printf("\n Server terminated\n");

return 0;
}





