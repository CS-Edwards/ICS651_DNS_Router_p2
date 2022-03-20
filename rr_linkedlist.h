/**rr_linkedlist.h for rr_linkedlist.c **/

#ifndef _RR_LIST
#define _RR_LIST

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
  




struct dnsRR;  

typedef struct dnsRR{

	char *name; 
	u_int16_t rrtype; 
	u_int16_t rrclass ;
	u_int32_t rrTTL; 
	u_int16_t rdlength;
	char *rdata; 
	
	struct dnsRR* next; 
	
}dnsRR;

dnsRR* new_record(char *r_name, char *r_ipaddr, int type);
dnsRR* add_record(dnsRR* next, char *r_name, char *r_ipaddr, int type);
void print_rr(dnsRR* head);
dnsRR* dns_rr_query_match(char* q, dnsRR* head);



#endif //_RR_LIST
