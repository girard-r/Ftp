/*
** response_password.c for myftp_client in /home/girard_r/rendu/PSU_2014_myftp
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar 22 21:21:44 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:38:55 2015 Aurélien GIRARDEAU
*/

#include "client.h"

int		need_password(t_response *response)
{
  t_response	end;

  end.sock_fd = response->sock_fd;
  printf("%s\n", response->data);
  if (get_response(&end, end.sock_fd) == -1
      || process_response(&end) == -1)
    return (-1);
  free(end.data);
  return (0);
}

int		ask_password(t_response *response)
{
  char		*passwd;
  char		*ret;
  size_t	len;
  t_response	end;

  passwd = NULL;
  len = 0;
  end.sock_fd = response->sock_fd;
  printf("%s\n", response->data);
  while (getline(&passwd, &len, stdin))
    {
      if (*passwd != 0)
	break ;
      printf("Please enter a valid password :\n");
    }
  if ((ret = concat_str("passwd ", passwd)) == NULL)
    return (0);
  free(passwd);
  send_request(end.sock_fd, ret);
  free(ret);
  if (get_response(&end, end.sock_fd) == -1
      || process_response(&end) == -1)
    return (-1);
  free(end.data);
  return (0);
}
