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

int connect_to_remote_server(void) {
	struct sockaddr_in server;
	int error_connect;
	int is_connect = -1;
	int socket_desc = -1;
	int nb_connection_attemps = 0;
	while (socket_desc == -1) {
		socket_desc = create_socket();
		if (socket_desc == -1) {
			sleep(2);
		} else {
			server.sin_addr.s_addr = inet_addr(SRV_IP);
			server.sin_family = AF_INET;
			server.sin_port = htons( SRV_PORT);
			while (is_connect == -1) {
				is_connect = connect(socket_desc, (struct sockaddr *) &server,
						sizeof(server));
				if (is_connect == -1) {
					error_connect = errno;
					error_printf(
							"Connect error // Num error : [%i] // Message_error : [%s]\n\n",
							error_connect, strerror(error_connect));
					nb_connection_attemps += 1;
					sleep(2);
				} else {
					debug_printf(3, "Connected (fd=%d) \n", socket_desc);
					return socket_desc;
				}
				if (nb_connection_attemps == 3) {
					close(socket_desc);
					socket_desc = create_socket();
				}
			}
		}
	}
	return socket_desc;
}

int send_msg(int socket_desc, char* message) {
	int error_send_message = -1;
	int actually_send = 0;
	int already_send = 0;
	int lenght_msg = strlen(message);
	while (already_send != lenght_msg) {
		int actually_send = send(socket_desc, &(message[already_send]),
				(lenght_msg - already_send), 0);
		if (actually_send == -1) {
			error_send_message = errno;
			error_printf(
					"Send failed // Num error : [%i] // Message_error : [%s]\n\n",
					error_send_message, strerror(error_send_message));
			close(socket_desc);
			return actually_send;
		} else {
			already_send += actually_send;
		}
	}
	debug_printf(3, "Data send\n");
	return actually_send;
}
