#!/bin/sh

gcc main.c connect.c config_implement.c config_control.c not_config.c -o config_server -ljson-c -luci

