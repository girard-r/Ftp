/*
** check_access.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/server
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar 22 10:12:07 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 18:08:09 2015 Aurélien GIRARDEAU
*/

#include "server.h"

int		check_serv_access(char *path)
{
  char		*user;
  char		*s_dir;
  char		real_path[1024];
  char		*home;

  if ((user = store_user(NULL, 0)) == NULL
      || (s_dir = get_server_dir(0, NULL)) == NULL
      || realpath(path, real_path) == NULL)
    return (-1);
  if ((home = concat_str(get_server_dir(0, NULL),
			 "/", store_user(NULL, 0))) == NULL)
    return (-1);
  if (strstr(real_path, home) == NULL)
    {
      free(home);
      return (-1);
    }
  free(home);
  return (0);
}

int		can_access(char *filename, int mode)
{
  if (access(filename, F_OK) == -1
      || access(filename, mode) == -1
      || check_serv_access(filename) == -1)
    return (-1);
  return (0);
}
