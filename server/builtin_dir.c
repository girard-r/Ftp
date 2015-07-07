/*
** builtin.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Thu Mar 12 00:21:57 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 20:48:59 2015 Aurélien GIRARDEAU
*/

#include "server.h"

int		request_pwd(char **cmp, int client_fd)
{
  char		*current_dir;

  (void)cmp;
  if (!(current_dir = getcwd(NULL, 0)))
    {
      handle_errors(GETCWD, 1);
      send_response(client_fd, PWD, strerror(errno));
      return (0);
    }
  if ((current_dir = my_str_replace(current_dir, get_server_dir(0, NULL),
				    "/root")) == NULL)
    {
      handle_errors(MALLOC, 1);
      send_response(client_fd, PWD, strerror(errno));
      return (0);
    }
  send_response(client_fd, PWD, current_dir);
  free(current_dir);
  return (0);
}

int		request_cd(char **cmp, int client_fd)
{
  char		*dir_name;
  char		*home;

  if (cmp[1])
    cmp[1] = my_str_replace(cmp[1], "/root", get_server_dir(0, NULL));
  if ((home = concat_str(get_server_dir(0, NULL),
			 "/", store_user(NULL, 0))) == NULL)
    {
      send_response(client_fd, CWD, strerror(errno));
      return (0);
    }
  dir_name = (cmp[1] == 0 ? home : cmp[1]);
  if (can_access(dir_name, X_OK) != -1)
    {
      chdir(dir_name);
      send_response(client_fd, CWD, "Success");
      free(home);
      return (0);
    }
  if (errno)
    send_response(client_fd, CWD, strerror(errno));
  else
    send_response(client_fd, CWD, "Permission denied");
  return (0);
}
