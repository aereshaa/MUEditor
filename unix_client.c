#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"
#include "stdio.h"
#include "stdlib.h"

connect_to_server(char* ip, short port){
	int id = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);//make a socket, but over here lol
	if(id==-1){printf("can't make a socket\n");return 1;}
	struct sockaddr_in server_addr;
	inet_aton(ip,&(server_addr.sin_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	return connect(id,&server_addr,sizeof(struct sockaddr_in));
}

int main(){
	if(connect_to_server("127.0.0.1",1001))printf("woohoo!\n");
}
