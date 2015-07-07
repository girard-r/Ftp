##
## Makefile for myftp in /home/girard_r/rendu/PSU_2014_myftp
## 
## Made by Aurélien GIRARDEAU
## Login   <girard_r@epitech.net>
## 
## Started on  Tue Mar 10 19:19:52 2015 Aurélien GIRARDEAU
## Last update Sun Mar 22 21:40:44 2015 Aurélien GIRARDEAU
##

SERVER		=		serveur

CLIENT		=		client

CC		=		gcc

RM		=		rm -f

INCL_DIR	=		includes/

SERVER_DIR	=		server

CLIENT_DIR	=		client_myftp

CFLAGS		=		-Wall -Wextra -Werror -I./$(INCL_DIR)

SRCS_S		=		$(SERVER_DIR)/init_server.c \
				$(SERVER_DIR)/errors.c \
				$(SERVER_DIR)/connect_clients.c \
				$(SERVER_DIR)/builtin_dir.c \
				$(SERVER_DIR)/builtin_file.c \
				$(SERVER_DIR)/list_builtin.c \
				$(SERVER_DIR)/user_builtin.c \
				$(SERVER_DIR)/pass_quit.c \
				$(SERVER_DIR)/security.c \
				$(SERVER_DIR)/utils.c \
				$(SERVER_DIR)/process_comunication.c \
				$(SERVER_DIR)/parsing.c \
				$(SERVER_DIR)/user.c \
				$(SERVER_DIR)/acl.c \
				$(SERVER_DIR)/check_access.c \
				$(SERVER_DIR)/main.c

OBJS_S		=		$(SRCS_S:.c=.o)

SRCS_C		=		$(CLIENT_DIR)/init_client.c \
				$(CLIENT_DIR)/errors.c \
				$(CLIENT_DIR)/process_client.c \
				$(CLIENT_DIR)/process_response.c \
				$(CLIENT_DIR)/response_file.c \
				$(CLIENT_DIR)/response_password.c \
				$(CLIENT_DIR)/utils.c \
				$(CLIENT_DIR)/main.c

OBJS_C		=		$(SRCS_C:.c=.o)

all:				$(SERVER) $(CLIENT)

$(SERVER):			$(OBJS_S)
				$(CC) -o $(SERVER) $(OBJS_S)

$(CLIENT):			$(OBJS_C)
				$(CC) -o $(CLIENT) $(OBJS_C)

clean:
				$(RM) $(OBJS_S) $(OBJS_C)

fclean:				clean
				$(RM) $(SERVER) $(CLIENT)

re:				fclean all

.PHONY:				all clean fclean re
