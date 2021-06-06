// config_implement.h
#define MY_UCI_OK 0
#define MY_UCI_NOT_FOUND 1

unsigned int read_uci_option(char *name,char *value);
unsigned int write_uci_option(char *name,char *value);

