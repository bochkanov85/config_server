// settings for connect

#define CONNECT_OK 0
#define CONNECT_FAIL_CREATE_SOCKET 1
#define CONNECT_FAIL_INET_PTON 2
#define CONNECT_FAIL_CONNECT 3

#define IS_JSON 0
#define NON_JSON 1

#define MAX_MESSAGE_LEN 1024

unsigned int connect_server(char *ip_addr,unsigned int port);
unsigned int get_json_message(char *buf);
