/*
 * server.c
 *
 *  Created on: 22 mars 2020
 *      Author: cedric
 */

#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include"debug.h"
#include<errno.h> //errno
#include<unistd.h>
#include "server.h"
#include <stdlib.h>

int create_socket(void) {
	int socket_desc;
	int error_socket;
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	error_socket = errno;
	if (socket_desc == -1) {
		error_printf(
				"Could not create socket // Num error : [%i] // Message_error : [%s]\n",
				error_socket, strerror(error_socket));
	}
	return socket_desc;
}



int listen_client(int socket_desc){
	int listen_state;
	listen_state = listen(socket_desc , 3);
	return listen_state;
}



int create_server(void) {
	struct sockaddr_in server;
	struct sockaddr_in client;
	int error_create;
	int error_accept;
	int error_listen;
	int error_receive;
	int bind_state = -1;
	int socket_desc = -1;
	int new_socket_desc = -1;
	int read_size = -1;
	char message[SIZE_MESSAGE +1];
	int size_struct_sockaddr;
	while (socket_desc == -1) {
		socket_desc = create_socket();
		if (socket_desc == -1) {
			sleep(2);
		} else {
			server.sin_family = AF_INET;
			server.sin_addr.s_addr = INADDR_ANY;
			server.sin_port = htons(LISTEN_PORT);
			while (bind_state == -1) {
				bind_state = bind(socket_desc, (struct sockaddr *)&server, sizeof(server));
				if (bind_state == -1) {
					error_create = errno;
					error_printf("bind failed // Num error : [%i] // Message_error : [%s]\n\n",
							error_create, strerror(error_create));
					sleep(2);
				} else {
					debug_printf(3, "bind done (fd=%d) \n", socket_desc);
				}
			}
		}
	}

	//listen
	int listen_state = -1;
	while (listen_state == -1){
		listen_state = listen_client(socket_desc);
		if (listen_state == -1){
			error_listen = errno;
			error_printf("listen failed // Num error : [%i] // Message_error : [%s]\n\n",
					error_listen, strerror(error_listen));
			sleep(2);
		}
	}

	while (1){
		//accept and incoming connection
		debug_printf(3, "Waiting for incoming connections\n", socket_desc);
		size_struct_sockaddr = sizeof(struct sockaddr_in);
		new_socket_desc = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&size_struct_sockaddr);
		if (new_socket_desc == -1){
			error_accept = errno;
			error_printf("accept failed // Num error : [%i] // Message_error : [%s]\n\n",
					error_accept, strerror(error_accept));
		}
		debug_printf(3, "Connection accepted\n", socket_desc);
		//Receive a message from client
		while( (read_size = recv(new_socket_desc , message , SIZE_MESSAGE , 0)) > 0 )
		{
			message[read_size] = '\0';
			printf("%s", message);
		}

		if(read_size == 0)
		{
			debug_printf(3, "Client disconnected\n", new_socket_desc);
		}
		else if(read_size == -1)
		{
			error_receive = errno;
			error_printf("listen failed // Num error : [%i] // Message_error : [%s]\n\n",
					error_listen, strerror(error_listen));
			perror("receive failed");
		}
	}
	void *sock = &socket_desc;
	//Free the socket pointer
	free(sock);

	if (new_socket_desc<0){
		error_accept = errno;
		error_printf("accept failed // Num error : [%i] // Message_error : [%s]\n\n", error_accept, strerror(error_accept));
	}

	return 0;
}



