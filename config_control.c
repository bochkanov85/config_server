#include <stdio.h>

#include "config_implement.h"
#include "config_control.h"

unsigned int read_option(char *name, char *value) {
	read_uci_option(name,value);
	printf("option name: %s\r\noption value: %s\r\n",name,value);
	return CONFIG_OK;
}

unsigned int write_option(char *name, char *value) {
	return CONFIG_OK;
}

