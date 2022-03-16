/**Utilities for DNS Server**/
//NOTE put main in #iftest 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


//TODO : create dnsutil.h file

#define DOMMAX 63
//domain name can be 63 chars max

#define IPMAX 39
//ip address can me 32 chars + colons= 39 max


 struct Address{
	char domain[DOMMAX];
	char ipaddr[IPMAX];

};

//typedef struct address Address;


int main(){



struct  Address a1;
//struct  Address *aptr = &a1;

 char domainin[] = "ics651.uhm/1.2.3.4";

 char *token1, *token2;
 token1 = strtok(domainin,"/"); //returns domain name
 token2 =  strtok(NULL,"/"); //returns IP address


 printf("Token 1, Domain Name: [%s] \n",token1);
 printf("Token 2, IP Address: [%s] \n", token2);


 strcpy(a1.domain, token1); //assign value to struct
 printf("In Stuct domain: [%s] \n", a1.domain);
return 0;
}






