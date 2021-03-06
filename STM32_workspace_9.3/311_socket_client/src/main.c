#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include"debug.h"
#include<errno.h> //errno
#include<unistd.h>
#include"client.h"

int main(int argc, char *argv[]) {
	debug_setlevel(0);
	int socket_desc;
	char *message;
	int message_send = -1;

	socket_desc = connect_to_remote_server();
	//connection good
	message = "Hello world !\n";
	while (1) {
		message_send = send_msg(socket_desc, message);
		if (message_send == -1) {
			//message not send, need to reconnect
			socket_desc = connect_to_remote_server();
		}
		else{
			sleep(2);
		}
	}
	return 0;
}
