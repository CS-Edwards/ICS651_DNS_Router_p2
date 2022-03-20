/**linkedlist for resource records**/
/**replaces address struct **/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "dnsutil.h"
#include "rr_linkedlist.h"


//new_record: first resouces record;initialize rr linked list ret: dnsRR ptr
dnsRR* new_record(char *r_name, char *r_ipaddr, int type){

	dnsRR* rr=malloc(sizeof(dnsRR));
	
	if(NULL != rr){
		rr->name=r_name;
		
		switch(type){
			case(1): rr->rrtype = AAAA;
			break;
		default: rr->rrtype = A;	
		}
		
		
		//printf("\n PRINT rrtype: [%d] \n",rr->rrtype);
		
		rr->rrclass = IN; //hardcoded
		rr->rrTTL = TTL;
		rr->rdlength = sizeof(r_ipaddr);
		rr->rdata = r_ipaddr;	
		
		printf("\n DNS RECORD SET FOR: [%s] \n",rr->name);
		return rr;
		}
	else{ 
		printf("\n ERROR: DID NOT ADD RESOURCE RECORD");
		return NULL;
		}
				
}

//add_record : add additional rrecords to linked list
//TODO: BUG FIX : replaces previously added add_records
dnsRR* add_record(dnsRR* next, char *r_name, char *r_ipaddr, int type){
	
	dnsRR* rr= new_record(r_name,r_ipaddr,type);
	
	if(NULL != rr){
		rr->next = next;
	}
	return rr;
}

//print all resource records
void print_rr(dnsRR* head){
	
	dnsRR* i;
	int rnum=1;
		
	for(i = head; NULL !=i;i=i->next){
		printf("\n RESOURCE RECORD: [%d]",rnum);
		printf("\n rname: [%s]", i->name);
		printf("\n rtype: [%d] [%s]", i->rrtype,((i->rrtype)==1)?"A":"AAAA");
		printf("\n rclass: [%d] [IN]", i->rrclass);
		printf("\n rttl: [%u]", i->rrTTL);
		printf("\n rlength: [%u]", i->rdlength);
		printf("\n rname: [%s]", i->rdata);
		printf("\n");	
	   rnum++;
	}
	
}

//dns_match search rrecord linked list for ipname/record from query
//ret: first record, NULL if none found
//TODO: return ptr to list of matching records
dnsRR* dns_rr_query_match(char* q, dnsRR* head){
	
	dnsRR* i;
	//dnsRR* mrl; //matching record list 
	char *p = {"."};
	int rnum=1;
	int nmatch=0;//if != 0, no match 
	
	
	for(i = head; NULL !=i;i=i->next){ //itr though rrecord list
	  	printf("\n RESOURCE RECORD: [%d]",rnum);
		for(int j=0; j<strlen(q)-1;j++){ //char by char comparison
			
			if(i->name[j]== p[0]){
				j++;	//ignore '.',skip  [funtions]
			}
			
			/**
			printf("q:%c ",q[j+1]);//query char
			printf("rr:%c ",i->name[j]); //resouce record char
			printf("\n");
			**/
			
			if(i->name[j] !=q [j+1] ){
			  nmatch++;			
			}
						
			
		};
		
		//returns first matching record
		if(nmatch==0) {
		print_rr(i);
		return i;
		}
		
		nmatch=0; //reset for next record
		rnum++;
		
		}
	
	
return NULL; //no match
}



