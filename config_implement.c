#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uci.h>

#include "config_implement.h"

// спорный вопрос - надо ли каждый раз открывать-закрывать контекст
// или это сделать один раз при инициализации
// пока выбрал первый вариант
// здесь же вопрос, 
unsigned int write_uci_option(char *name,char *value) {
	return MY_UCI_OK;
}

unsigned int read_uci_option(char *name,char *value) {
	struct uci_context *ctx;
	struct uci_package *pkg;
	struct uci_element *elem;

	ctx = uci_alloc_context();

	uci_set_confdir(ctx,"/etc/config");

	printf("UCI context allocated\r\n");

	uci_load(ctx,"system",&pkg);

	printf("UCI loaded\r\n");

	uci_foreach_element(&pkg->sections,elem) {
		
		printf("uci_to_section()\r\n");

		struct uci_section *sect = uci_to_section(elem);
		char *pValue = NULL;

		printf("looking up option string");

		pValue = uci_lookup_option_string(ctx,sect,name);

		if (pValue!=NULL) {
			strcpy(value,pValue);
			//free(pValue);
			return MY_UCI_OK;
		}
		
	}

	strcpy(value,"option not found");

	uci_free_context(ctx);
	return MY_UCI_NOT_FOUND;
}

