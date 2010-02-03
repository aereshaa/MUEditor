#include "pthread.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"
#include "stdio.h"
#include "stdlib.h"

int serv_socketid;
#define QUEUE_LIM 6 /*this is arbitrary*/

int setup_server(){
	serv_socketid=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);//make a socket
	if(serv_socketid==-1){printf("can't make a socket\n");return 1;}
	struct sockaddr_in serv_sockaddr = (struct sockaddr_in){AF_INET,INADDR_ANY,(short)1001};//accept connexions on port 1001
	bind(serv_socketid,&serv_sockaddr,sizeof(struct sockaddr_in));
	if(listen(serv_socketid,QUEUE_LIM)){printf("The socket's deaf?\n");return 1;}//put it in listening mode
}

int takedown_server(){
	close(serv_socketid);
}

struct connection{
	struct sockaddr_in address;
	int file_descr;
};

void * handle_connection(struct connection * client){
	free(client);
}

void * run_server(void * whatev){
	printf("good\n");
	while(1){
		struct connection * client=malloc(sizeof(struct connection));
		client->file_descr=accept(serv_socketid,&(client->address),sizeof(struct sockaddr_in));
		pthread_create(NULL,NULL,handle_connection,client);
	}
}

int main(){
	if(setup_server())printf("bad\n");
	else printf("good\n");
	pthread_t serv_thid;
	pthread_create(&serv_thid,NULL,run_server,NULL);
	pthread_exit(NULL);
}

