/*
 * server.h
 *
 *  Created on: 22 mars 2020
 *      Author: cedric
 */

#ifndef SERVER_H_
#define SERVER_H_
#define LISTEN_PORT 5001

int create_socket();

int create_server();

int listen_client(int socket_desc);

int accept_connection();


#endif /* SERVER_H_ */
