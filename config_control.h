// config_control.h
// 

#define CONFIG_OK 0
#define CONFIG_OPTION_NOT_FOUND 1
#define CONFIG_WRITE_ERROR 2

// ищет опцию с именем name
// значение кладет в value
unsigned int read_option(char *name,char *value);

// ищет опцию с именем name
// записывает в нее значение value
unsigned int write_option(char *name,char *value);

