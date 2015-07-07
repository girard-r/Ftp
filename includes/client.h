/*
** client.h for client in /home/girard_r/rendu/PSU_2014_myftp/includes
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Tue Mar 10 19:29:25 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:39:45 2015 Aurélien GIRARDEAU
*/

#ifndef CLIENT_MYFTP_H_
# define CLIENT_MYFTP_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <netdb.h>
# include <unistd.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include "includes.h"

typedef struct protoent		t_protocol;
typedef struct sockaddr_in	t_sockin;

/*
** Errors
*/
typedef enum
  {
    ARG = 1,
    SOCK,
    PROT,
    CONNECT,
    CLOSE,
    READ,
    MALLOC,
    WRITE,
    OPEN,
    SCANF,
    INPUT_FAIL
  }		e_error;

typedef struct	s_error
{
  e_error	type;
  const char	what[100];
}		t_error;

typedef struct	s_response
{
  int		sock_fd;
  e_rfc		which;
  char		*data;
}		t_response;

typedef struct	s_client
{
  e_rfc		which;
  int		(*ptrf)(t_response *reponse);
}		t_client;

/*
** errors.c
*/
int		handle_errors(e_error type, int sys);
int		close_fd(int fd);

/*
** init_client.c
*/
t_protocol	*get_protocol(char *prot);
int		connect_socket(t_protocol *pe, int port, char *ip);
int		init_client(int port, char *ip);

/*
** process_client.c
*/
int		get_response(t_response *response, int sock_fd);
int		process_client(int sock_fd);
char		*add_carriage_return(char *str);
int		send_request(int sock_fd, char *str);
int		process_com(char *line, int sock_fd);

/*
** process_response.c
*/
int		process_response(t_response *response);
int		display_response(t_response *response);
int		disconnect_client(t_response *response);
int		ask_auth(t_response *response);

/*
** utils.c
*/
char		*concat_str(char *s1, char *s2);

/*
** response_file.c
*/
int		put_into_file(t_response *response);
int		send_file(t_response *response);

/*
** response_password.c
*/
int		need_password(t_response *response);
int		ask_password(t_response *response);

#endif /* !CLIENT_MYFTP_H_ */
