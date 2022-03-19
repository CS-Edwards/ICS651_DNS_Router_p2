/**Utilities for DNS Server**/
//NOTE put main in #iftest 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <netinet/in.h>
#include "dnsutil.h"



/**addAddrArr() 
parses domainAddr string; adds domain name 
and address to respective fields in Address struct
status: completed and tested**/ 

void addAddrArr(char *domAddr, Address *a){
  
 char *domainset, *ipset;
 domainset = strtok(domAddr,"/"); //returns domain name
 ipset =  strtok(NULL,"/"); //returns IP address

 strcpy(a->domain, domainset); //assign value to struct
 strcpy(a->ipaddr, ipset); //assign value to struct
}

void printAddr(Address *a){

 printf("\n Domain: [%s] \n",a->domain);
 printf("\n IP Address: [%s] \n",a->ipaddr);
 
}

void printPacket(dnsPacket *dpacketin){
 printf("print DNS Packet - to be implemented \n");
 printHeader(&dpacketin->pheader);

}
void printHeader(dnsHeader *dheadin){
 printf("print DNS Header - to be implemented \n");
 printf("TID: [%X] \n",dheadin->trans_id);
 printf("QR: [%u] \n",dheadin->qr); //0
 printf("OPCODE: [%u] \n",dheadin->opcode); //0
 printf("AA: [%u] \n",dheadin->aa); //0
 printf("TC: [%u] \n",dheadin->tc); //0
 printf("RD: [%u] \n",dheadin->rd); //0
 printf("RA: [%u] \n",dheadin->ra); //0
 printf("Z: [%u] \n",dheadin->z);   //0
 printf("RCODE: [%u] \n",dheadin->rcode);
 printf("QDCOUNT: [%o] \n",dheadin->qdcount);//1
 printf("ANCOUNT: [%u] \n",dheadin->ancount);
 printf("NSCOUNT: [%u] \n",dheadin->nscount);
 printf("ARCOUNT: [%u] \n",dheadin->arcount);
 

}

int processDNS(dnsPacket *packetin, void *datain, u_int16_t size){
 printf("print DNS Processing - to be implemented \n");
 processHDR(&packetin->pheader,datain);
 
 //allocate mem (data - 12 byte header)
 packetin->data=malloc(size-12);
 
 //copy in data
 memcpy(packetin->data,datain+SIZE,size-SIZE);
 
 //set size
 packetin->dsize = size-SIZE;
 
 //process question
 processQuest(&packetin->question, packetin->data, packetin->dsize);
 
 return 1;

}

int processHDR(dnsHeader *headerin, void *datain){
 printf("print DNS HEADER - to be implemented \n");
 memcpy(headerin,datain,SIZE);
 
 headerin->trans_id = ntohs(headerin->trans_id);
 headerin->qdcount = ntohs(headerin->trans_id);
 headerin->ancount = ntohs(headerin->trans_id);
 headerin->nscount = ntohs(headerin->trans_id);
 headerin->arcount = ntohs(headerin->trans_id);
 
 
}

//set ip address string to dnsQuesion->question
int processQuest(dnsQuestion *questin, void *datain, u_int16_t size){
	printf("\n Process Questio: to be implemented \n");
	
	//allocate mem (ip name)
 	questin->questname=malloc(size);
	
	//copy in data
 	memcpy(questin->questname,datain,size);
 	
 	u_int16_t one = 1; //IN class and type A IPv4 
 	u_int16_t twentyeight = 28; //type AAAA IPv6
 	//questin->querytype = one;  //1= A; Host Name  (R.F.C. 1035, 3.2.2)
 	questin->questclass = one; //1= IN ; Internet (R.F.C. 1035, 3.2.4)
 	
 	
 	//questin->querytype = ntohs(questin->querytype); =0 did not work
 	
 	
 	//print what is after strlen
 	char* c = malloc(sizeof(c)*2);
 	memcpy(c,datain+strlen(questin->questname),sizeof(c)*2);
 	printf("\n ***** printing C **** \n");
 	printf("\n C: [%s] \n",c);
 	
	//print ip address
	int domsize = sizeof(datain)/sizeof(datain[0]);
	
	
	printf("\n ***** QUESTION PRINT TEST **** \n");
	//print datain minus 4 bytes for qtype and qclass
	for(int i=0;i<strlen(questin->questname);i++){
    	printf("%c ",questin->questname[i]); //cast void to char
        }
    	printf("\n");
	
	
	
	printQuestion(questin);
	return 1;

}

void printQuestion(dnsQuestion *questin){
 printf("print Question - to be implemented \n");
 printf("domain: [%s] \n",questin->questname);
 printf("type: [%u] \n",questin->querytype); //0
 printf("class: [%u] \n",questin->questclass); //0


};


int buildreply(dnsPacket *dp, dnsReply *dr){

   //memcpy(questin->questname,datain,size);
   
   	//TOSET: Header
   	//memcpy(&(dr->trans_id), &(dp->pheader.trans_id),16);
   	
   	//printf("dr->trans_id: [%u] \n",dr->trans_id);
   	
   	/**
	u_int16_t trans_id:16; //16 bit transaction ID
	u_int16_t qr:1; //query(0) or response(1)
	u_int16_t qdcount:16; //number of entries in question section (1)
	u_int16_t ancount:16; //number of resources records in answer section
	u_int16_t nscount:16; //number of nameserver resource records
	u_int16_t arcount:16; //number of resources in additional record sectin
	
	//TOSET: Question
	char *questname; //domain name
	u_int16_t querytype:16; //query type
	u_int16_t questclass:16 ;//question class - IN for internet

	//TOSET


        **/


return 1;};



void to_buff(void* data, char * buffer, int * offset){

	
	memcpy(buffer+= *offset, data, sizeof(data));
	
	printf("\n buffer: [%s] \n",buffer);
	printf("\n offset: [%d] \n",*offset);
	
	
	//might need mem cpy
	*offset+=sizeof(data); //increase offset for next to_buff call
	printf("\n updated offset: [%d] \n",*offset);

}




#ifdef RUN_UTIL_TEST
int main(){

 printf("\n ::Begin RUN_UTIL_TEST:: \n");

 //Funtion Test for addAddrArr
 Address a1;
 char domainin[] = "test.uhm/T.3.5.T";
 addAddrArr(domainin,&a1);
 printf("In stuct domain: [%s] \n", a1.domain);
 printf("In stuct IP address: [%s] \n", a1.ipaddr);
 
 //Funtion Test for printArr
 printAddr(&a1);
 
 //no code below this line
 printf("\n ::END RUN_UTIL_TEST:: \n");
return 0;
}

#endif /* RUN_UTIL_TEST */


/****************************************	
		//TODO: populate  Struct Addr array size of argc
		
		//FIX: core dump -- idea copy domAddr stinrg to variable char *copy w. str copy (or memcopy idk) ; also copy pointer to address array? ::TEST IN UTIL FILE
		
		//addAddrArr(argv[i], &addressArr[j]); //&?
		//printAddr(&addressArr[j]);
		//j++;

******************************************************/


