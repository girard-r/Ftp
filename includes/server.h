/*
** server.h for server in /home/girard_r/rendu/PSU_2014_myftp/includes
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Tue Mar 10 19:29:25 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:09:37 2015 Aurélien GIRARDEAU
*/

#ifndef SERVER_MYFTP_H_
# define SERVER_MYFTP_H_

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <errno.h>
# include <dirent.h>

# include "includes.h"

typedef struct protoent		t_protocol;
typedef struct sockaddr_in	t_sockin;

/*
** Errors
*/
typedef enum
  {
    ARG = 1,
    PROT,
    SOCK,
    BIND,
    CLOSE,
    LISTEN,
    ACCEPT,
    FORK,
    READ,
    WRITE,
    MALLOC,
    READDIR,
    OPENDIR,
    OPEN,
    GETCWD
  }		e_error;

typedef struct	s_error
{
  e_error	type;
  const char	what[100];
}		t_error;

typedef struct	s_fd
{
  int		sock_fd;
  int		client_fd;
}		t_fd;

typedef struct	s_action
{
  const char	type[10];
  int		(*ptrf)(char **cmd, int client_fd);
}		t_action;

/*
** errors.c
*/
int		handle_errors(e_error type, int sys);
int		close_fd(int fd);

/*
** init_server.c
*/
t_protocol	*get_protocol(char *prot);
int		bind_socket(t_protocol *pe, int port);
int		listen_clients(int sock_fd);
int		init_server(t_fd *fd, int port);

/*
** connect_clients.c
*/
int		accept_clients(t_fd fd);
int		process_client(t_fd fd, t_sockin *s_in_client);
int		fork_process(t_fd fd, t_sockin *s_in_client);

/*
** process_comunication.c
*/
int		send_response(int client_fd, e_rfc which, char *str);
char		*get_request(int client_fd);
int		get_all_requests(int client_fd);
int		seek_for_builtin(char **cmd, int client_fd);

/*
** builtin_dir.c
*/
int		request_cd(char **cmp, int client_fd);
int		request_pwd(char **cmp, int client_fd);

/*
** builtin_file.c
*/
int		check_access_get(int client_fd, char *arg, struct stat *infos);
int		request_get(char **cmp, int client_fd);
int		request_put(char **cmp, int client_fd);

/*
** parsing.c
*/
void		delete_tab(char **str);
char		**parse_cmdline(char *cmdline);

/*
** user.c
*/
char		*store_user(char *username, char set);
char		*store_password(char *password, char set);
void		free_tab(char **tab);

/*
** acl.c
*/
int		create_acl(int *fd, char *file_acl);
int		parse_acl_line(char ***acl, char *tmp, int cmp);
char		**parse_acl(int *fd);
char		**get_acl(char *file_acl);
char		*acl_path(char *new_path, char set);

/*
** check_access.c
*/
int		check_serv_access(char *path);
int		can_access(char *filename, int mode);

/*
** user_builtin.c
*/
int		user_got_pass();
int		user_exists(char *user);
int		check_user();
int		go_bounce();
int		request_user(char **cmp, int client_fd);

/*
** security.c
*/
char		*get_server_dir(char set, char *tmp);
int		check_root_dir();

/*
** list_builtin.c
*/
char		*proceed_list(DIR *dir);
int		request_list(char **cmp, int client_fd);

/*
** pass_quit.c
*/
int		check_password(char *pass);
int		request_passwd(char **cmp, int client_fd);
int		end_connection(char **cmp, int client_fd);

/*
** utils.c
*/
char		*concat_str(char *s1, char *s2, char *s3);
char		*my_str_replace(char *haystack, char *needle, char *replace);

#endif /* !SERVER_MYFTP_H_ */
