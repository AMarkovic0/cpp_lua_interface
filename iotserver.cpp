#include "tcp_server.h"
#include "luaclass.hpp"

#define PORT 54321u

void* connection_handler(void *vargp);

int main(int argc, char *argv[])
{
	pthread_t thread_id;

	tcp_server_init(PORT, LOG_ON);
	tcp_server_listen(LOG_ON);

	pthread_create(&thread_id, NULL, &connection_handler, NULL);

	pthread_join(thread_id, NULL);

	tcp_server_close(LOG_ON);

	return 0;
}

void read_callback(char* r_buf, int fd, _logs log)
{
	printf("AAAAAAAAAAAAAAAAAAAAAAAAA");
}

void* connection_handler(void *vargp)
{
	char r_buf[BUF_SIZE];
	tcp_server_poll(r_buf, LOG_ON);
}
