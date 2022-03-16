/**Utilities for DNS Server**/
//NOTE put main in #iftest 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
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




