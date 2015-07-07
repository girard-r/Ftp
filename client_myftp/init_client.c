/*
** init_client.c for myftp_client in /home/girard_r/rendu/PSU_2014_myftp/includes
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Tue Mar 10 19:32:35 2015 Aurélien GIRARDEAU
** Last update Wed Mar 11 17:33:29 2015 Aurélien GIRARDEAU
*/

#include "client.h"

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

int		connect_socket(t_protocol *pe, int port, char *ip)
{
  int		fd;
  t_sockin	s_in;

  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (handle_errors(SOCK, 1));
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = inet_addr(ip);
  if (connect(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      handle_errors(CONNECT, 1);
      close_fd(fd);
      return (-1);
    }
  return (fd);
}

int		init_client(int port, char *ip)
{
  t_protocol	*pe;
  int		sock_fd;

  if ((pe = get_protocol("TCP")) == NULL
      || (sock_fd = connect_socket(pe, port, ip)) == -1)
    return (-1);
  return (sock_fd);
}
