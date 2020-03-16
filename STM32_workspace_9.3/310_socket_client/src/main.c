#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include"debug.h"
#include"socket.h"
#include<errno.h>
#include<unistd.h>

int create_socket(){
	int socket_desc;
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1){
		error_printf("Could not create socket // Num error : [%i] // Message_error : [%s]\n", errno,strerror(errno));
	}
	return socket_desc;
}

int connect_to_remote_server(int socket_desc){
	struct sockaddr_in server;
	int is_connect;

	server.sin_addr.s_addr = inet_addr(SRV_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons( SRV_PORT );
	is_connect = connect(socket_desc , (struct sockaddr *)&server , sizeof(server));
	if (is_connect < 0){
		error_printf("Connect error // Num error : [%i] // Message_error : [%s]\n\n", errno,strerror(errno));
	}
	else{
		puts("Connected");
	}
	return is_connect;
}


int main(int argc , char *argv[]){
	int socket_desc;
	int is_connect;
	char *message;

	//Create socket
	socket_desc = create_socket();
	while (socket_desc == -1){
		socket_desc = create_socket();
		sleep(2);
	}

	//Connect to remote server
	is_connect = connect_to_remote_server(socket_desc);
	while (is_connect == -1){
		is_connect = connect_to_remote_server(socket_desc);
		sleep(2);
	}

	//Send some data

	while (1){
		message = "Hello world !\n";
		if( send(socket_desc , message , strlen(message) , 0) < 0)
		{
			error_printf("Send failed // Num error : [%i] // Message_error : [%s]\n", errno,strerror(errno));
			socket_desc = create_socket();
			while (socket_desc == -1){
				sleep(2);
				socket_desc = create_socket();
			}
			is_connect = connect_to_remote_server(socket_desc);
			while (is_connect == -1){
				sleep(2);
				is_connect = connect_to_remote_server(socket_desc);
			}
		}
		else{
			puts("Data Send\n");
		}
		sleep(2);
	}
	return 0;
}
