// connect.c

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#include "connect.h"

int sockfd = 0;

void dummy() {
}

unsigned int connect_server(char *ip_addr,unsigned int port) {
	struct sockaddr_in serv_addr;
	int result;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd<0) {
		return CONNECT_FAIL_CREATE_SOCKET;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	result = inet_pton(AF_INET,ip_addr,&serv_addr.sin_addr);
	if (result<0) {
		return CONNECT_FAIL_INET_PTON;
	}

	result = connect(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr));

	if (result<0) {
		return CONNECT_FAIL_CONNECT;
	}

	return CONNECT_OK;
}

// в зависимости от требований, можно проработать
// то ли верить, что по умолчанию JSON придет одним пакетом
// то ли перестраховываться и парсить весь поток на предмет поиска JSON
// выбрал компромиссный вариант - считаю, что JSON должен прийти одним пакетом
// но проверяю, что это он - смотрю на наличие фигурных скобок
// первым и последним символом
unsigned int get_json_message(char *buf) {
	char received[MAX_MESSAGE_LEN];
	int received_len;

	while (1) {
		received_len = recv(sockfd,received,MAX_MESSAGE_LEN,0);
		if (received!=0) {
			if ((received[0]=='{')&&(received[received_len-1]=='}')) {
				received[received_len] = 0;
				strcpy(buf,received);
				return IS_JSON;
			}
			else {
				return NON_JSON;
			}

		}
	}
}
