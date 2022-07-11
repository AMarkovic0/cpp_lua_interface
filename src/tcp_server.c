#include "tcp_server.h"

static int sockfd;
static struct sockaddr_in server_addr;

static int new_sockets[NUM_OF_DEVICES];
static struct sockaddr_in new_addresses[NUM_OF_DEVICES];

uint8_t tcp_server_init(unsigned int port, _logs log)
{
	char ip[MAX_IP_SIZE];
	uint8_t check_var = 0;

	signal(SIGPIPE , SIG_IGN); // block SIGPIPE signal in case client disconnect

	getIP(ip, log);

	sockfd = socket(PF_INET , SOCK_STREAM , 0);
	if(log && (-1 == sockfd))
	{
		printf("Socket creation failed. \r\n");
		return -1;
	}
	else if(!log && (-1 == sockfd))
	{
		return -1;
	}
	else if( log )
		printf( "Socket creation sucessfull. \r\n");

	memset(&server_addr, '\0', sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip);

	check_var = bind(sockfd, (struct sockaddr*)&server_addr , sizeof(server_addr));
	if(check_var && log)
	{
		printf("Bind failed %d. \r\n", errno);
		return -1;
	}
	else if(check_var && !log)
	{
		return -1;
	}
	else if(!check_var && log)
		printf("Bind sucessfull \r\n");

	return -1;
}

uint8_t tcp_server_listen(_logs log)
{
	uint8_t check = listen(sockfd, NUM_OF_DEVICES);
	if(check && log)
	{
		printf("Listen failed. \r\n");
		return -1;
	}
	else if(check && !log)
	{
		return -1;
	}
	else if(!check && log)
		printf("Server listening... \r\n");

	return 1;
}

uint8_t tcp_server_accept(_logs log)
{
	static uint8_t cnt = 0;
	int* new_socket = &new_sockets[cnt];
	struct sockaddr_in *new_addr = &new_addresses[cnt];
	socklen_t addr_size = sizeof(new_addr);

	*new_socket = accept(sockfd, (struct sockaddr*)new_addr, &addr_size);
	if((*new_socket < 0) && log)
	{
		printf("Acception failed. \r\n");
		return -1;
	}
	else if((*new_socket < 0) && !log)
	{
		return -1;
	}
	else if(log)
		printf("Client sucessfully accepted. \r\n");

	return 1;
}

uint8_t tcp_server_send(char* w_buf)
{
	return send(sockfd, w_buf, strlen(w_buf), 0);
}

uint8_t tcp_server_recv(char* r_buf)
{
	return recv(sockfd, r_buf, BUF_SIZE, MSG_DONTWAIT);
}

void getIP(char* IPaddr, _logs log)
{
	int fd;
	struct ifreq ifr;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	ifr.ifr_addr.sa_family = AF_INET;
	memcpy(ifr.ifr_name, WIFI_INTERFACE, IFNAMSIZ-1);
	ioctl(fd, SIOCGIFADDR, &ifr);

	close(fd);

	strcpy(IPaddr, inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr));

	if(log)
		printf("Host IP Address is: %s\n", IPaddr);

	return;
}

