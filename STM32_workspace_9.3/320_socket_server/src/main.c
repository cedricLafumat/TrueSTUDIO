#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include"debug.h"
#include<errno.h> //errno
#include<unistd.h>
#include"server.h"


int main(int argc, char* argv[]) {
	debug_setlevel(3);

	create_server();

	return 0;
}
