#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

// run like...
// gcc -o dns dns.c
// ./dns domain.com
int main(int argc, char *argv[]) {

	char ip[INET_ADDRSTRLEN];
	struct hostent *h;
	int i;

	if((h = gethostbyname(argv[1])) == 0) {
		switch(h_errno) {
			case HOST_NOT_FOUND:
				printf("host not found\n");
				break;
			case NO_ADDRESS:
				printf("name valid, but not ip set\n");
				break;
			case NO_RECOVERY:
				printf("dns failure\n");
				break;
			case TRY_AGAIN:
				printf("temporary dns failure\n");
				break;
			default:
				printf("uknown error number %d\n", h_errno);
		}
		return 1;
	}

	printf("h_name\t\t= %s\n", h->h_name);
	printf("h_aliases\t= []\n");
	i = 0;
	while(h->h_aliases[i] != NULL) {
		printf(" [%02d] %s\n", i, h->h_aliases[i]);
		i++;
	}
	printf("h_addrtype\t= %d\n", h->h_addrtype);
	printf("h_length\t= %d\n", h->h_length);
	printf("h_addr_info\t= []\n");
	i = 0;
	while(h->h_addr_list[i] != NULL) {
		inet_ntop(AF_INET, h->h_addr_list[i], ip, INET_ADDRSTRLEN);
		printf(" [%02d] %s\n", i, ip);
		i++;
	}

	return 0;

}