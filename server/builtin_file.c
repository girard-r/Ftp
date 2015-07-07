/*
** builtin_file.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/server
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar 22 20:18:42 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 23:25:58 2015 Aurélien GIRARDEAU
*/

#include "server.h"

int		check_access_get(int client_fd, char *arg, struct stat *infos)
{
  if (can_access(arg, R_OK) == -1
      || stat(arg, infos) == -1)
    {
      if (errno)
	send_response(client_fd, NOTFOUND, strerror(errno));
      else
	send_response(client_fd, NOTFOUND, "Permission denied");
      return (0);
    }
  if (infos->st_mode & S_IFDIR)
    {
      send_response(client_fd, NOTFOUND, "Error : is a directory");
      return (0);
    }
  return (1);
}

int		request_get(char **cmp, int client_fd)
{
  int		fd_file;
  char		buff[PACKAGE_SIZE];
  int		ret;
  struct stat	infos;

  if (cmp[1])
    {
      if (!check_access_get(client_fd, cmp[1], &infos))
	return (0);
      if ((fd_file = open(cmp[1], O_RDONLY, infos.st_mode)) == -1)
	{
	  send_response(client_fd, NOTFOUND, strerror(errno));
	  return (0);
	}
      send_response(client_fd, STOU, cmp[1]);
      write(client_fd, (char *)&infos.st_mode, sizeof(int));
      while ((ret = read(fd_file, buff, PACKAGE_SIZE)) > 0)
	write(client_fd, buff, ret);
      close_fd(fd_file);
      return (0);
    }
  send_response(client_fd, NOTFOUND, "Usage : get <filename>");
  return (0);
}

int		request_put(char **cmp, int client_fd)
{
  char		*request;
  int		file_fd;
  char		buff[PACKAGE_SIZE];
  int		ret;

  if (cmp[1])
    {
      send_response(client_fd, RETR, cmp[1]);
      request = get_request(client_fd);
      if (strcmp(request, "0") == 0)
	{
	  file_fd = open(cmp[1], O_CREAT | O_WRONLY | O_TRUNC,
			 S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	  while ((ret = read(client_fd, buff, PACKAGE_SIZE)) > 0)
	    {
	      write(file_fd, buff, ret);
	      if (ret < PACKAGE_SIZE)
		break ;
	    }
	  close_fd(file_fd);
	}
      return (0);
    }
  send_response(client_fd, NOTFOUND, "Usage : put <filename>");
  return (0);
}
