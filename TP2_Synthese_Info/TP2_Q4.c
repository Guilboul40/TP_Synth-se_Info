#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFSIZE 128
#define fd 1
#define ERROR_INPUT "Erreur dans la commande !\nUsage: <program> <host> <file>\n"
#define ERROR_ADRESS "Erreur lors de la résolution de l'adresse.\n"
#define ERROR_SOCKET "Erreur lors de la création du socket.\n"
#define ERROR_CONNECT "Erreur lors de l'établissement de la connexion.\n"
#define CONNECT_SUCCESS "Connecté au réseau.\n"
#define ACKSIZE 4
#define READSIZE 1500


struct addrinfo hints, *result, *rp;
int status;
void *addr;
char adress[BUFSIZE];
char adress_str[BUFSIZE];

void * RRQpacket(char * filename, char * mode) {
	int filename_size = strlen(filename);
	int mode_size = strlen(mode);
	int opcode_size = 2;
	
	int size = opcode_size + filename_size + 1 + mode_size + 1;
	
	char * paquet=malloc(size);
	
	//Opcode RRQ
	paquet[0]=0;
    paquet[1]=1;
	//filename RRQ
	strcpy(&paquet[2],filename);
	paquet[opcode_size+filename_size]=0;
	//mode RRQ
	strcpy(&paquet[opcode_size+filename_size+1],mode);
	paquet[opcode_size+filename_size+1+mode_size]=0;
	
	return paquet;
}

void * ACKpacket(char * data_recv){
	char * paquet=malloc(ACKSIZE);
	
	//Opcode ACK
	paquet[0]=0;
	paquet[1]=4;
	//Block #
	paquet[2]=data_recv[2];
	paquet[3]=data_recv[3];
	
	return paquet;
}

void prompt(char *message){
    write(fd, message, strlen(message));
}

void return_adress(char *host){

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    // Host information
    status = getaddrinfo(host, "tftp", &hints, &result);
    if (status != 0) {
        prompt(ERROR_ADRESS);
        exit(EXIT_FAILURE);
    }
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        if (rp->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
            addr = &(ipv4->sin_addr);
        }else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
            addr = &(ipv6->sin6_addr);
        }
        // Convert adress to string
        inet_ntop(rp->ai_family, addr, adress_str, sizeof(adress_str));
        sprintf(adress,"Address: %s\n", adress_str);
        prompt(adress);
    }
}
void create_socket(){

    int client_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (client_socket == -1) {
        prompt(ERROR_SOCKET);
        exit(EXIT_FAILURE);
    }
    // Connection
    status = connect(client_socket, result->ai_addr, result->ai_addrlen);
    if (status == -1) {
        prompt(ERROR_CONNECT);
        close(client_socket);
        exit(EXIT_FAILURE);
    } else {
        //Send message
        prompt(CONNECT_SUCCESS);
        send(client_socket,CONNECT_SUCCESS,strlen(CONNECT_SUCCESS),0);
    }
}

int main(int argc, char* argv[]){

    char *host = argv[1]; //adresse du serveur
    char *file = argv[2];

    // Command verification
    if(argc != 3){
        write(fd, ERROR_INPUT, strlen(ERROR_INPUT));
        exit(EXIT_FAILURE);
    }

    return_adress(host);
    create_socket();

    //envoie d'une requête RRQ
	char * mode ="octet";
	char * request=RRQpacket(filename,mode);
	int size_request=2+strlen(filename)+1+strlen(mode)+1;
	int is_send=sendto(sfd,request,size_request,0,res->ai_addr,res->ai_addrlen);
	if (is_send==-1){
		fprintf(stderr, "Error : %s n'a pas réussi à senvoyer une demande RRQ au serveur %s\n",argv[0],argv[1]);
		exit(EXIT_FAILURE);
	}

    //récupération de la data
	char data_recv[READSIZE];
	struct sockaddr src_addr;
	socklen_t src_addrlen = sizeof(src_addr);
	
	freeaddrinfo(result);

    return 0;
}
