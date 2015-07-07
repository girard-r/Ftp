/*
** list_builtin.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar 22 20:08:28 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:10:04 2015 Aurélien GIRARDEAU
*/

#include "server.h"

char		*proceed_list(DIR *dir)
{
  char		*tmp;
  struct dirent	*dir_infos;
  int		size;

  tmp = NULL;
  while ((dir_infos = readdir(dir)) != NULL)
    {
      size = (tmp == NULL ? 0 : strlen(tmp));
      if (!tmp && !(tmp = calloc(sizeof(char), strlen(dir_infos->d_name) + 2)))
	return (NULL);
      else if (!(tmp = realloc(tmp,
			      (size_t)(strlen(dir_infos->d_name) + size + 2))))
	return (NULL);
      if (*tmp == 0)
	strcpy(tmp, dir_infos->d_name);
      else
	tmp = strcat(tmp, dir_infos->d_name);
      tmp = strcat(tmp, "\n");
    }
  return (tmp);
}

int		request_list(char **cmp, int client_fd)
{
  char		*dir_name;
  DIR		*dir;
  char		*tmp;

  dir_name = (cmp[1] == 0 ? "." : cmp[1]);
  if (can_access(dir_name, R_OK) == -1
      || (dir = opendir(dir_name)) == NULL)
    {
      send_response(client_fd, NOTFOUND, strerror(errno));
      return (0);
    }
  if ((tmp = proceed_list(dir)) == NULL)
    send_response(client_fd, NOTFOUND, "Error, list failed");
  else
    send_response(client_fd, LIST, tmp);
  closedir(dir);
  return (0);
}
