/*
** response_file.c for myftp_client in /home/girard_r/rendu/PSU_2014_myftp
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar 22 21:26:32 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 23:25:17 2015 Aurélien GIRARDEAU
*/

#include "client.h"

int		put_into_file(t_response *response)
{
  int		fd_file;
  int		ret;
  char		buff[PACKAGE_SIZE];
  int		mode;

  read(response->sock_fd, (char *)&mode, sizeof(int));
  if ((fd_file = open(response->data, O_CREAT | O_WRONLY, mode)) == -1)
    return (handle_errors(OPEN, 1));
  while ((ret = read(response->sock_fd, buff, PACKAGE_SIZE)) > 0)
    {
      write(fd_file, buff, ret);
      if (ret < PACKAGE_SIZE)
	break ;
    }
  close_fd(fd_file);
  return (0);
}

int		send_file(t_response *response)
{
  int		fd_file;
  char		buff[PACKAGE_SIZE];
  int		ret;

  if ((fd_file = open(response->data, O_RDONLY,
		      S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) == -1)
    {
      send_request(response->sock_fd, "1");
      handle_errors(OPEN, 1);
      return (0);
    }
  send_request(response->sock_fd, "0");
  while ((ret = read(fd_file, buff, PACKAGE_SIZE)) > 0)
    {
      write(response->sock_fd, buff, ret);
    }
  close_fd(fd_file);
  return (0);
}
