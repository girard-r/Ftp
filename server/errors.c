/*
** errors.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/includes
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Tue Mar 10 19:44:55 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:02:55 2015 Aurélien GIRARDEAU
*/

#include "server.h"

static const t_error	g_error[15] =
  {
    {ARG, "[SERVER] UsageError : ./myftp <PORT>, \
PORT must be a postive value"},
    {PROT, "[SERVER] System error: getprotobyname"},
    {SOCK, "[SERVER] System error: socket"},
    {BIND, "[SERVER] System error: bind"},
    {CLOSE, "[SERVER] System error: close"},
    {LISTEN, "[SERVER] System error: listen"},
    {ACCEPT, "[SERVER] System error: accept"},
    {READ, "[SERVER] System error: read"},
    {WRITE, "[SERVER] System error: write"},
    {MALLOC, "[SERVER] System error: malloc"},
    {READDIR, "[SERVER] System error: readdir"},
    {OPENDIR, "[SERVER] System error: opendir"},
    {OPEN, "[SERVER] System error: open"},
    {GETCWD, "[SERVER] System error: getcwd"},
    {0, ""}
  };

int		handle_errors(e_error type, int sys)
{
  int		i;

  i = 0;
  while (g_error[i].what)
    {
      if (g_error[i].type == type)
	{
	  if (sys == 1)
	    perror(g_error[i].what);
	  else
	    {
	      write(2, g_error[i].what, strlen(g_error[i].what));
	      write(2, "\n", 1);
	    }
	  break ;
	}
      i += 1;
    }
  return (-1);
}

int		close_fd(int fd)
{
  if (close(fd) == -1)
    return (handle_errors(CLOSE, 1));
  return (0);
}
