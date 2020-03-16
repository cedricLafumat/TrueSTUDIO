#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include"debug.h"
#include<errno.h> //errno
#include<unistd.h>
#include "client.h"

int main(int argc , char *argv[]){
	int is_connect;
	char *message;

	//Connect to remote server
	is_connect = connect_to_remote_server();
	while (is_connect == -1){
		is_connect = connect_to_remote_server();
		sleep(2);
	}

	//Send some data

	while (1){
		message = "Hello world !\n";
		int myerror;
		if( send(is_connect , message , strlen(message) , 0) < 0)
		{
			myerror = errno;
			error_printf("Send failed // Num error : [%i] // Message_error : [%s]\n", myerror,strerror(myerror));
			close(is_connect);
			is_connect = connect_to_remote_server();
			while (is_connect == -1){
				sleep(2);
				is_connect = connect_to_remote_server();
			}
		}
		else{
			puts("Data Send\n");
		}
		sleep(2);
	}
	return 0;
}
