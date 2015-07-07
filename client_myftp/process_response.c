/*
** process_responce.c for myftp_client in /home/girard_r/rendu/PSU_2014_myftp
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sat Mar 14 03:03:40 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 23:10:33 2015 Aurélien GIRARDEAU
*/

#include <errno.h>
#include "client.h"

static const t_client	g_client[12] =
  {
    {USER, &ask_auth},
    {USER_OK, &need_password},
    {QUIT, &disconnect_client},
    {LIST, &display_response},
    {CWD, &display_response},
    {STOU, &put_into_file},
    {RETR, &send_file},
    {PWD, &display_response},
    {NOTFOUND, &display_response},
    {PASS, &ask_password},
    {PASS_OK, &display_response},
    {0, NULL}
  };

int		process_response(t_response *response)
{
  unsigned int	i;

  i = 0;
  while (g_client[i].ptrf != NULL)
    {
      if (g_client[i].which == response->which)
	return (g_client[i].ptrf(response));
      i += 1;
    }
  return (0);
}

int		disconnect_client(t_response *response)
{
  display_response(response);
  return (1);
}

int		send_auth_request(int sock_fd, char *username)
{
  char		*ret;

  if ((ret = concat_str("user ", username)) == NULL)
    return (0);
  send_request(sock_fd, ret);
  free(ret);
  return (1);
}

int		ask_auth(t_response *response)
{
  char		*username;
  size_t	len;
  t_response	end;
  ssize_t	gl;

  username = NULL;
  len = 0;
  end.sock_fd = response->sock_fd;
  printf("%s\n", response->data);
  while ((gl = getline(&username, &len, stdin)))
    {
      if (*username != 0 || gl == -1)
	break ;
      printf("Please enter a valid username :\n");
    }
  if (gl == -1)
    return (handle_errors(INPUT_FAIL, 0));
  if (!send_auth_request(end.sock_fd, username))
    return (0);
  free(username);
  if (get_response(&end, end.sock_fd) == -1
      || process_response(&end) == -1)
    return (-1);
  free(end.data);
  return (0);
}

int		display_response(t_response *response)
{
  printf("%s\n", response->data);
  return (0);
}
