cmake_minimum_required(VERSION 3.24)
project(simple_shell C)

set(CMAKE_C_STANDARD 11)

add_executable(simple_shell main.c shell.h builtins.c builtins_help_2.c builtins_help_1.c divide.c enviro.c enviro_builtins.c errors.c errors_msg_1.c errors_msg_2.c file_commands.c getline.c helper.c helpers_2.c input_helpers.c linkedlist.c locate.c origbuiltin.c str_func1.c str_funct.c)
