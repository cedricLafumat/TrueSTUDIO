/*
 * client.c
 *
 *  Created on: 16 mars 2020
 *      Author: cedric
 */




#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include"debug.h"
#include<errno.h> //errno
#include<unistd.h>
#include "client.h"

int create_socket(){
	int socket_desc;
	int myerror;
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1){
		myerror = errno;
		error_printf("Could not create socket // Num error : [%i] // Message_error : [%s]\n", myerror,strerror(myerror));
	}
	return socket_desc;
}

int connect_to_remote_server(){
	struct sockaddr_in server;
	int myerror;
	int is_connect;
	int socket_desc = create_socket();
	server.sin_addr.s_addr = inet_addr(SRV_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons( SRV_PORT );
	is_connect = connect(socket_desc , (struct sockaddr *)&server , sizeof(server));
	if (is_connect < 0){
		myerror = errno;
		error_printf("Connect error // Num error : [%i] // Message_error : [%s]\n\n", myerror,strerror(myerror));
	}
	else{
		puts("Connected");
	}
	return socket_desc;
}
