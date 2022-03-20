/**Domain Name Server**/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
   

#define MAXLINE 1024
#include "dnsutil.h"
#include "rr_linkedlist.h"



int main(int argc, char* argv[]){

	//Command Line Processing
	int i,j,portnum =0;
	Address addressArr[argc];
	
	char *domainip; //TODO: update later to array accept multiple entries; 

	if(argc==1){
		printf("No arguments passed into main \n program terminating\n ");
		return -1; //TODO: Time permitting change to  perrer and define error
	}
	
	portnum=atoi(argv[1]);
	printf("\n Port number set to: %d \n",portnum);

	printf("\n This DNS Server handles requests for  the following domain.name/ip.address(es) \n");
	
	
	/*head of resource rec list*/
	char *testname ="www.candace.com";
	char *ip= "1:2:3:4";
	
	dnsRR* ptr = new_record(testname, ip,col_search(ip) );
	
	for(i=2; i<argc;i++){ 
		printf("\n argv[%d]: %s \n",i,argv[i]);
		char *in;
		strcpy(in,argv[i]);
		
		
		char *domainset, *ipset;
 		domainset = strtok(in,"/"); //returns domain name
 		ipset =  strtok(NULL,"/"); //returns IP address 
 		
 		ptr = add_record(ptr, domainset, ipset, col_search(ipset));
       	//print_rr(ptr);
		
	}//close for loop
	
	print_rr(ptr);
	printf("\n *** argc: [%d]",argc);
	//set size of rr array to argc
	
	printf("\n *** argc-2: [%d]",argc-2); //length of struct arr
	//SERVER TODO: update code
	
	/**R. Record Test**/
	
	
	
	//char *testname2 ="www.jane.com";
	//char *ip2= "1.2.3.4";
	
	
	
		
	//dnsRR* ptr = new_record(testname, ip,col_search(ip) );
	//ptr = add_record(ptr, testname2, ip2, col_search(ip2));
       //print_rr(ptr);
       
       //populate records with entries from command line
	
	
	free(ptr);
	

return 0;
}





