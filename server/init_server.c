/*
** init_server.c for init_server in /home/girard_r/rendu/PSU_2014_myftp/includes
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Tue Mar 10 19:32:35 2015 Aurélien GIRARDEAU
** Last update Wed Mar 11 17:30:01 2015 Aurélien GIRARDEAU
*/

#include "server.h"

t_protocol	*get_protocol(char *prot)
{
  t_protocol	*pe;

  if (!(pe = getprotobyname(prot)))
    {
      handle_errors(PROT, 1);
      return (NULL);
    }
  return (pe);
}

int		bind_socket(t_protocol *pe, int port)
{
  int		fd;
  t_sockin	s_in;

  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (handle_errors(SOCK, 1));
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      handle_errors(BIND, 1);
      close_fd(fd);
      return (-1);
    }
  return (fd);
}

int		listen_clients(int sock_fd)
{
  if (listen(sock_fd, SOMAXCONN) == -1)
    {
      handle_errors(LISTEN, 1);
      close_fd(sock_fd);
      return (-1);
    }
  return (0);
}

int		init_server(t_fd *fd, int port)
{
  t_protocol	*pe;

  if ((pe = get_protocol("TCP")) == NULL
      || (fd->sock_fd = bind_socket(pe, port)) == -1
      || listen_clients(fd->sock_fd) == -1)
    return (-1);
  return (0);
}
