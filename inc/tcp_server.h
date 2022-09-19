/******************************************************************************
*
* tcp_server.h this is a file which contains necesarry function declarations,
* definitions of macros and preprocessing instructions for tcp server program execution.
* This file implements TCP server library undepndetly.
*
* This code uses POSIX libraries.
*
* Created by: Aleksa Markovic
******************************************************************************/

#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<errno.h>
#include<unistd.h>
#include<signal.h>

//Networking headers:
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<net/if.h>
#include<sys/ioctl.h>
#include<netdb.h>

#define MAX_IP_SIZE 15		// Size of the IPv4 address
#define BUF_SIZE 255		// Buffer size
#define WIFI_INTERFACE "wlp2s0" // Network interface
#define NUM_OF_DEVICES 10	// Max clients


// Enum that allows or restricts logging on stdout
typedef enum logging { LOG_ON = 1 , LOG_OFF = 0 } _logs;

/*
* This function initializes and binds a TCP server
* In:
*	char* ip		-> server IP address
*	unsigned int port 	-> Port number
*	_logs log		-> stdout log
* Out:
*	uint8_t check		-> success notification
*/
uint8_t tcp_server_init( char* ip , unsigned int port , _logs log );

/*
* Starts server listening
* Before this function call, please initialize the server
* In:
*	_logs log		-> stdout log
* Out:
*	uint8_t check		-> success notification
*/
uint8_t tcp_server_listen( _logs log );

/*
* Accept clinet connection and assign socket file destriptor
* In:
*	int* newSocket_			-> Address for the client connection file destriptor
*	struct sockaddr_in* newAddr	-> Address of the inet
*	_logs log			-> stdout log
* Out:
*	uint8_t check		-> success notification
*/
uint8_t tcp_server_accept( int* newSocket_ , struct sockaddr_in* newAddr , _logs log );

/*
* Send message to the client. Assumes connection has been established.
* In:
*	int sockfd	-> Clients socket file descriptor
*	char* w_buf	-> Message buffer pointer
* Out:
*	uint8_t check	-> success notification
*/
uint8_t tcp_server_send( int sockfd , char* w_buf );

/*
* Reads client message and puts the message in the buffer.
* Assumes connection has been established.
* In:
*	int sockfd	-> Clients socket file descriptor
*	char* r_buf	-> Message buffer pointer
* Out:
*	uint8_t check	-> success notification
*/
uint8_t tcp_server_recv( int sockfd , char* r_buf );

/*
* Gets and writes server IP address in the IPaddr buffer
* In:
*	char* IPaddr	-> Address buffer
*	_logs log	-> stdout log
*/
void getIP( char* IPaddr , _logs log );

#endif // _TCP_SERVER_H_
