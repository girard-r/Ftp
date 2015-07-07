/*
** connect_clients.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/server
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Wed Mar 11 14:56:24 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:02:31 2015 Aurélien GIRARDEAU
*/

#include "server.h"

int		accept_clients(t_fd fd)
{
  t_sockin	s_in_client;
  socklen_t	sock_len;

  sock_len = sizeof(t_sockin);
  while ((fd.client_fd = accept(fd.sock_fd,
				(struct sockaddr *)&s_in_client,
				&sock_len)) != -1)
    {
      if (fork_process(fd, &s_in_client) == -1)
	{
	  close_fd(fd.sock_fd);
	  return (-1);
	}
    }
  if (fd.client_fd == -1)
    {
      handle_errors(ACCEPT, 1);
      close_fd(fd.sock_fd);
      return (-1);
    }
  return (0);
}

int				process_client(t_fd fd, t_sockin *s_in_client)
{
  char				*client_ip;

  client_ip = inet_ntoa(s_in_client->sin_addr);
  (void)client_ip;
  send_response(fd.client_fd, USER, "Service ready for new user.\n\
Please login - username :");
  if (get_all_requests(fd.client_fd) == 1)
    return (1);
  return (0);
}

int		fork_process(t_fd fd, t_sockin *s_in_client)
{
  pid_t		pid_client;

  if ((pid_client = fork()) == -1)
    return (handle_errors(FORK, 1));
  if (pid_client == 0)
    {
      if (process_client(fd, s_in_client))
	return (1);
      close_fd(fd.client_fd);
      return (0);
    }
  else
    if (close(fd.client_fd) == -1)
      return (-1);
  return (0);
}
