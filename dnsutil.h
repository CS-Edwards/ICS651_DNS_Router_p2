/*dnsutil.h*/
/*dnsutil.h: header file for dnsutil.c */



#define DOMMAX 63   //domain name can be 63 chars max
#define IPMAX 39    //ip address can me 32 chars + colons= 39 max


struct Address; 

typedef struct {
	char domain[DOMMAX];
	char ipaddr[IPMAX];
	int  IPvers;

}Address;



void addAddrArr(char *domAddr, Address *a);
void printAddr(Address *a);
