/**Domain Name Server**/

#include <stdlib.h>
#include <stdio.h>
#include "dnsutil.h"

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
	for(i=2; i<argc;i++){ //i might need to start at 3
		printf("\n argv[%d]: %s \n",i,argv[i]);
	
		//TODO: populate  Struct Addr array size of argc
		addAddrArr(argv[i], &addressArr[j]); //&?
		printAddr(&addressArr[j]);
		j++;
		
	}


return 0;
}
