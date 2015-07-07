/*
** errors.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/includes
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Tue Mar 10 19:44:55 2015 Aurélien GIRARDEAU
** Last update Thu Mar 19 16:45:26 2015 Aurélien GIRARDEAU
*/

#include "client.h"

static const t_error	g_error[12] =
  {
    {ARG, "[CLIENT] Usage: ./client <IP> <PORT>"},
    {SOCK, "[CLIENT] System error: sock"},
    {PROT, "[CLIENT] System error: getprotobyname"},
    {CONNECT, "[CLIENT] System error: connect"},
    {CLOSE, "[CLIENT] System error: close"},
    {READ, "[CLIENT] System error: read"},
    {MALLOC, "[CLIENT] System error: malloc"},
    {WRITE, "[CLIENT] System error: write"},
    {OPEN, "[CLIENT] System error: open"},
    {SCANF, "[CLIENT] System error: scanf"},
    {INPUT_FAIL, "[CLIENT] read from input failed"},
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
