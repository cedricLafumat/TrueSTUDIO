/*
 * socket.h
 *
 *  Created on: 15 mars 2020
 *      Author: cedric
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#define SRV_IP "127.0.0.1"
#define SRV_PORT 5001

int create_socket();

int connect_to_remote_server();

int send_msg();


#endif /* CLIENT_H_ */
