#ifndef CHAT
#define CHAT

#include"../include/include.h"

int handle_server();
void initialize_port(UINT *pPORT);
int test_WSAStartup(WSADATA wsadata);
int test_server_socket(SOCKET server_socket);
int test_bind(SOCKET server_socket, struct sockaddr_in server_info);
int test_listen_port(SOCKET server_socket, int MAXCONN);
int test_client_socket(SOCKET client_socket);
int test_client_connect(SOCKET client_socket, struct sockaddr_in client_info);
int handle_client(SOCKET client_socket);

int recive_send_message(SOCKET server_socket);
void *recive_message(void* client_socket);


#endif