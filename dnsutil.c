/**Utilities for DNS Server**/
//NOTE put main in #iftest 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <netinet/in.h>
#include "dnsutil.h"
#include "rr_linkedlist.h"




void printPacket(dnsPacket *dpacketin){
 printf("print DNS Packet - to be implemented \n");
 printHeader(&dpacketin->pheader);

}

void printHeader(dnsHeader *dheadin){
 printf("PACKET HEADER: \n");
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

//processDNS: ret ip in query
//TODO: FIX does not proccess full query
char* processDNS(dnsPacket *packetin, void *datain, u_int16_t size){
 printf("print DNS Processing - to be implemented \n");
 processHDR(&packetin->pheader,datain);
 packetin->data=malloc(size-12);  //allocate mem (data - 12 byte header)
 
 memcpy(packetin->data,datain+SIZE,size-SIZE);
 packetin->dsize = size-SIZE;
 
 //process question 
 return processQuest(&packetin->question, packetin->data, packetin->dsize);
}

//processHDR set members of header struct
//TODO: FIX flag settings/ not setting correctly
int processHDR(dnsHeader *headerin, void *datain){
 //printf("print DNS HEADER - to be implemented \n");
 memcpy(headerin,datain,SIZE);
 
 headerin->trans_id = ntohs(headerin->trans_id);
 headerin->qdcount = ntohs(headerin->trans_id);
 headerin->ancount = ntohs(headerin->trans_id);
 headerin->nscount = ntohs(headerin->trans_id);
 headerin->arcount = ntohs(headerin->trans_id);
}

//processQuest: sets members in dnsQuestion stuct, ret: url from query
//TODO: FIX hardcoded class and type; read from query/quest
char* processQuest(dnsQuestion *questin, void *datain, u_int16_t size){
	printf("\n PROCESS QUESTION \n");
	
	questin->questname=malloc(size);//allocate mem (ip name)
 	char* url= malloc(sizeof(questin->questname));//return
	
	
 	memcpy(questin->questname,datain,size);//copy in data
 	
 	//set struct members
 	questin->questclass = IN; //1= IN ; Internet (R.F.C. 1035, 3.2.4)
 	questin->querytype = A;//hard coded
 	 	
        printf("\n ***URL***: [%s] ", url);//blank
	
	strcpy(url,questin->questname);
	printf("\n ***URL***: [%s] ", url);//set
	
	//for(int i=1;i<strlen(questin->questname);i++){
	//printf("[%d]u:%c ",i,url[i]);}
	
	printQuestion(questin);
	return url;
}

//print_question
void printQuestion(dnsQuestion *questin){
 printf("PRINT QUESTION  \n");
 printf("domain: [%s] \n",questin->questname);
 printf("type: [%u] \n",questin->querytype); //0
 printf("class: [%u] \n",questin->questclass); //0
}



//col_search: identify ipv6 addr with ':', ret 1 ipv6
int col_search(char *ip_addr){

	char *col = {":"};
	for (int i =0; i<strlen(ip_addr);i++){
		if (ip_addr[i] == col[0]){
		//printf("\n COL_SEARCH: FOUND : -- BREAKING OUT OF LOOP");
		return 1;
		}	
	}
//printf("\n COL_SEARCH: LOOP COMPLETE no : found");
return 0;}

//to_buff: sent pieces of DNS reply to send buffer
void to_buff(void* data, char * buffer, int * offset){
       	
	memcpy(buffer+= *offset, data, sizeof(data));
	
	//printf("\n buffer: [%s] \n",buffer);
	//printf("\n offset: [%d] \n",*offset);
	*offset+=sizeof(data); //increase offset for next to_buff call
	//printf("\n updated offset: [%d] \n",*offset);
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


//unused functions





/**DNU: did not use **/
void addAddrArr(char *domAddr, Address *a){
  
 char *domainset, *ipset;
 domainset = strtok(domAddr,"/"); //returns domain name
 ipset =  strtok(NULL,"/"); //returns IP address

 strcpy(a->domain, domainset); //assign value to struct
 strcpy(a->ipaddr, ipset); //assign value to struct
}

/**DNU: did not use **/
void printAddr(Address *a){

 printf("\n Domain: [%s] \n",a->domain);
 printf("\n IP Address: [%s] \n",a->ipaddr);
 
}

/**DNU: did not use **/
void printQuery(unsigned char *buffIn){
 
 for(int i=0;i<MAXINBUFF;i++){
    	printf("%X ",buffIn[i]);
        }
    printf("\n");
}
