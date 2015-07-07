/*
** process_comunication.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/server
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Wed Mar 11 19:26:18 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:13:10 2015 Aurélien GIRARDEAU
*/

#include "server.h"

static const t_action	g_cmd[9] =
  {
    {"user", &request_user},
    {"passwd", &request_passwd},
    {"quit", &end_connection},
    {"ls", &request_list},
    {"cd", &request_cd},
    {"get", &request_get},
    {"pwd", &request_pwd},
    {"put", &request_put},
    {"", NULL}
  };

int		send_response(int client_fd, e_rfc which, char *str)
{
  unsigned int	size;

  size = strlen(str);
  if (write(client_fd, (char *)&which, sizeof(e_rfc)) == -1
      || write(client_fd, (char *)&size, sizeof(size)) == -1
      || write(client_fd, str, size) == -1)
    return (handle_errors(WRITE, 1));
  return (0);
}

char		*get_request(int client_fd)
{
  unsigned int	size;
  char		*content;
  int		ret;

  content = NULL;
  if ((ret = read(client_fd, (char *)&size, sizeof(size))) == -1)
    {
      handle_errors(READ, 1);
      return (NULL);
    }
  if (ret != 0)
    {
      if ((content = malloc(sizeof(char) * (size + 1))) == NULL)
	{
	  handle_errors(MALLOC, 1);
	  return (NULL);
	}
      if (read(client_fd, content, size) == -1)
	{
	  handle_errors(READ, 1);
	  return (NULL);
	}
      content[size - 1] = 0;
    }
  return (content);
}

int		seek_for_builtin(char **cmd, int client_fd)
{
  unsigned int	i;

  i = 0;
  while (g_cmd[i].ptrf)
    {
      if (!strcmp(g_cmd[i].type, cmd[0]))
	return (g_cmd[i].ptrf(cmd, client_fd));
      i += 1;
    }
  send_response(client_fd, NOTFOUND, "Command Not Found");
  return (-1);
}

int		get_all_requests(int client_fd)
{
  char		*cmdline;
  char		**split;

  while ((cmdline = get_request(client_fd)))
    {
      if ((split = parse_cmdline(cmdline)) == NULL)
	{
	  send_response(client_fd, NOTFOUND, "No command found");
	  continue ;
	}
      if (seek_for_builtin(split, client_fd) == 1)
	return (1);
    }
  return (0);
}
