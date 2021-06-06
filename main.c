#include <stdio.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <string.h>

#include "connect.h"
#include "config_control.h"
#include "config_implement.h"
#include "not_config.h"

#define SERVER_ADDR "192.168.1.217"
#define SERVER_PORT 5000

#define JSON_INCORRECT_FORMAT 2
#define JSON_INCORRECT_COMMAND 3
#define JSON_PARAMS_NOT_FOUND 4

unsigned int process_json(char *buf) {
	struct json_object *obj;
	struct json_object *command_obj;
	struct json_object *params_obj;
	struct json_object *current_param;
	struct json_object *current_name;
	struct json_object *current_value;

	unsigned int params_len;
	int i;

	// здесь надо, безусловно, переделать на динамическое выделение
	// но пока идет отладка прототипа -
	// лучше исключить ошибки, связанные с утечками памяти
	char command_str[128];
	char param1_str[128];
	char param2_str[128];
	char param3_str[128];

	char tmp_str[128];

	obj = json_tokener_parse(buf);

	// пока опускаем проверки случаев, когда что-то идет не так
	
	json_object_object_get_ex(obj,"command",&command_obj);
	
	strcpy(command_str,json_object_get_string(command_obj));

	printf("command: %s\r\n",command_str);
	
	json_object_object_get_ex(obj,"params",&params_obj);

	printf("Get params - done\r\n");

	params_len = json_object_array_length(params_obj);

	printf("Params len: %d\r\n",params_len);

	// чтение параметров
	if (!strcmp(command_str,"read")) {
		json_object_object_get_ex(obj,"params",&params_obj);
		params_len = json_object_array_length(params_obj);
		for (i=0;i<params_len;i++) {
			current_param = json_object_array_get_idx(params_obj,i);
			json_object_object_get_ex(current_param,"name",&current_name);
			read_option(json_object_get_string(current_name),tmp_str);
		}
	}

	// запись параметров
	if (!strcmp(command_str,"write")) {
		json_object_object_get_ex(obj,"params",&params_obj);
		params_len = json_object_array_length(params_obj);
		for (i=0;i<params_len;i++) {
			current_param = json_object_array_get_idx(params_obj,i);
			json_object_object_get_ex(current_param,"name",&current_name);
			json_object_object_get_ex(current_value,"value",&current_value);
			write_option(json_object_get_string(current_name),json_object_get_string(current_value));
		}
	}

	// не конфигурационная команда
	if (!strcmp(command_str,"get_binary")) {
		get_binary(command_str);
	}
}

int main() {
	unsigned int result;
	char message[MAX_MESSAGE_LEN];

	printf("Welcome to configuration server\r\n");
	printf("Connecting to the server:\r\n");
	printf("IP addr: %s\r\nPort:%d\r\n",SERVER_ADDR,SERVER_PORT);
	
	result = connect_server(SERVER_ADDR,SERVER_PORT);

	if (result != CONNECT_OK) {
		printf("Connecting failed\r\n");
		return 1;
	}

	while (1) {
		if (get_json_message(message)==IS_JSON) {
			process_json(message);
		}
	}
return 0;
}
