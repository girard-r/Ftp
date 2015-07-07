/*
** process_client.c for myftp_client in /home/girard_r/rendu/PSU_2014_myftp
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Wed Mar 11 17:57:31 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:17:47 2015 Aurélien GIRARDEAU
*/

#include <string.h>
#include "client.h"

int		get_response(t_response *response, int sock_fd)
{
  unsigned int	size;

  if (read(sock_fd, (char *)&(response->which), sizeof(e_rfc)) == -1
      || read(sock_fd, (char *)&size, sizeof(size)) == -1)
    return (handle_errors(READ, 1));
  if ((response->data = malloc(sizeof(char) * (size + 1))) == NULL)
    return (handle_errors(MALLOC, 1));
  if (read(sock_fd, response->data, size) == -1)
    return (handle_errors(READ, 1));
  response->data[size] = 0;
  return (0);
}

char		*add_carriage_return(char *str)
{
  int		size;
  char		*ret;

  size = strlen(str);
  if (!(ret = malloc(sizeof(char) * (size + 2))))
    {
      handle_errors(MALLOC, 1);
      return NULL;
    }
  strcpy(ret, str);
  ret[size] = '\n';
  ret[size + 1] = 0;
  return (ret);
}

int		send_request(int sock_fd, char *str)
{
  unsigned int	size;
  char		*tmp;
  char		to_free;

  tmp = NULL;
  to_free = 0;
  if (str[strlen(str) - 1] != '\n')
    {
      if (!(tmp = add_carriage_return(str)))
	return (-1);
      to_free = 1;
    }
  else
    tmp = str;
  size = strlen(tmp);
  if (write(sock_fd, (char *)&size, sizeof(size)) == -1
      || write(sock_fd, tmp, size) == -1)
    return (handle_errors(WRITE, 1));
  if (to_free)
    free(tmp);
  return (0);
}

int		process_com(char *line, int sock_fd)
{
  t_response	response;
  int		ret;

  response.sock_fd = sock_fd;
  if (send_request(sock_fd, line) == -1
      || get_response(&response, sock_fd) == -1
      || (ret = process_response(&response)) == -1)
    return (-1);
  if (ret == 1)
    {
      free(response.data);
      return (1);
    }
  free(response.data);
  return (0);
}

int		process_client(int sock_fd)
{
  char		*s;
  int		ret;
  size_t	len;
  t_response	response;

  len = 0;
  s = NULL;
  response.sock_fd = sock_fd;
  if (get_response(&response, sock_fd) == -1
      || (ret = process_response(&response)) == -1)
    return (-1);
  write(1, "$> ", 3);
  while (getline(&s, &len, stdin) > 0)
    {
      if ((ret = process_com(s, sock_fd)) == -1
	  || ret == 1)
	break ;
      write(1, "$> ", 3);
    }
  free(s);
  return (ret);
}
