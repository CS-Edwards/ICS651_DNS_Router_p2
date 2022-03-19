/*dnsutil.h*/
/*dnsutil.h: header file for dnsutil.c */
/**RFC1034, RFC 1035**/



#define DOMMAX 63   //domain name can be 63 chars max
#define IPMAX 39    //ip address can me 32 chars + colons= 39 max
#define SIZE 12     //DNS Header is 12 Bytes (RFC)


struct Address; 
struct dnsPacket;
struct dnsHeader; //12 bytes - RFC1035, 4.1.1
struct dnsQuestion; //- RFC1035, 4.1.2
struct dnsRR; //Resource Record- RFC1035, 4.1.3



typedef struct {
	char domain[DOMMAX];
	char ipaddr[IPMAX];
	int  IPvers;//4(A) or 6(AAAA)

}Address;



typedef struct{
	u_int16_t trans_id:16; //16 bit transaction ID
	u_int16_t qr:1; //query(0) or response(1)
	u_int16_t opcode:4;//query type
	u_int16_t aa:1;//authoritative answer
	u_int16_t tc:1;//truncation
	u_int16_t rd:1;//recursion desired
	u_int16_t ra:1;//recursion available
	u_int16_t z:3; //reserved for future use
	u_int16_t rcode:4;//response code
	u_int16_t qdcount:16; //number of entries in question section (1)
	u_int16_t ancount:16; //number of resources records in answer section
	u_int16_t nscount:16; //number of nameserver resource records
	u_int16_t arcount:16; //number of resources in additional record sectin


}dnsHeader;


//TODO: Question processing


typedef struct{

	char *questname; //domain name
	u_int16_t querytype:16; //query type
	u_int16_t questclass:16 ;//question class - IN for internet
	
}dnsQuestion;


typedef struct{

	dnsHeader pheader;
	char *data;
	u_int16_t dsize;
	dnsQuestion question;


}dnsPacket;




typedef struct{

	char *name; //domain name
	u_int16_t rrtype:16; //RR code type (related to RDATA field: A or AAAA)
	u_int16_t rrclass:16 ;//RR class - (related to RDATA field)
	u_int32_t rrTTL:32 ; //RR TTL - 0 values for uncached RR
	u_int16_t rdlength:16;//length in octets of RDATA field
	char *rdata; //TYPE A && CLASS IN 4 octect ARPA Internet addr(ipV4); TYPE AAAA 16 octet ipV6 addr
	
}dnsRR;


//TODO: **Response** : Header,Question, ANSWER, AUTHORITY (my server), Additional(nothing here)


void addAddrArr(char *domAddr, Address *a);
void printAddr(Address *a);
void printPacket(dnsPacket *dpacketin);
void printHeader(dnsHeader *dheadin);
void printQuestion(dnsQuestion *questin); //TODO: add parameter
void printResourceRecords(); //TODO: add parameter





int processDNS(dnsPacket *packetin, void *datain, u_int16_t size);
int processHDR(dnsHeader *headerin, void *datain);
int processQuest(dnsQuestion *questin, void *datain, u_int16_t size); 
int processRR();//TODO: add param
int recordSearch();//TODO: compare domain name in query to rrecord domain names; return 0 if record not found



/*** GENERATED DNS RESPONSE ****/

struct dns_reply;


typedef struct{

	/**Header**/
	u_int16_t trans_id:16; //16 bit transaction ID
	u_int16_t qr:1; //query(0) or response(1)
	u_int16_t opcode:4;//query type
	u_int16_t aa:1;//authoritative answer
	u_int16_t tc:1;//truncation
	u_int16_t rd:1;//recursion desired
	u_int16_t ra:1;//recursion available
	u_int16_t z:3; //reserved for future use
	u_int16_t rcode:4;//response code
	u_int16_t qdcount:16; //number of entries in question section (1)
	u_int16_t ancount:16; //number of resources records in answer section
	u_int16_t nscount:16; //number of nameserver resource records
	u_int16_t arcount:16; //number of resources in additional record sectin


	/**Question**/
	u_int16_t l1:1; //label bit 1
	u_int16_t l2:1; //label bit 2
	char *questname; //domain name
	u_int16_t querytype:16; //query type
	u_int16_t questclass:16 ;//question class - IN for internet


	/**Answer**/
	//dns_rr *recordlist[]; 
	
	//onerecord
	
	//[offset][1 1 | OFFSET]
	u_int16_t o1:1; //offset bit 1
	u_int16_t o2:1; //offset bit 2
	char **name; //pointer to domain name
	
	
	u_int16_t rrtype:16; //RR code type (related to RDATA field: A or AAAA)
	u_int16_t rrclass:16 ;//RR class - (related to RDATA field)
	u_int32_t rrTTL:32 ; //RR TTL - 0 values for uncached RR
	u_int16_t rdlength:16;//length in octets of RDATA field
	char *rdata; //TYPE A && CLASS IN 4 octect ARPA Internet addr(ipV4); TYPE AAAA 16 octet ipV6 addr

}dnsReply;

int buildreply(dnsPacket *dp, dnsReply *dr);
void printeply();
void to_buff(void* data, char * buffer, int * offset);

