/*
** pass_quit.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/server
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar 22 20:10:36 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 23:18:43 2015 Aurélien GIRARDEAU
*/

#include "server.h"

int		check_password(char *pass)
{
  char		**acl;
  int		i;
  char		*user;
  int		ret;

  i = 0;
  user = store_user(NULL, 0);
  if ((acl = get_acl(acl_path(NULL, 0))) == NULL)
    return (0);
  while (acl[i])
    {
      if (i % 2 == 0
	  && strcmp(acl[i], user) == 0)
	{
	  if (strcmp(acl[i + 1], pass) == 0)
	    ret = 1;
	  else
	    ret = 0;
	  free_tab(acl);
	  return (ret);
	}
      i += 1;
    }
  free_tab(acl);
  return (0);
}

int		request_passwd(char **cmp, int client_fd)
{
  if (store_password(NULL, 0) != NULL || !user_got_pass())
    {
      send_response(client_fd, PASS_OK, "User already connected.");
      return (0);
    }
  if (cmp[1])
    {
      if (!check_password(cmp[1]))
	send_response(client_fd, PASS, "Please enter a valid password.");
      else
	{
	  go_bounce();
	  send_response(client_fd, PASS_OK, "User connected.");
	  store_password(cmp[1], 1);
	}
    }
  else
    send_response(client_fd, PASS, "Usage : passwd <pass>. Try again :");
  return (0);
}

int		end_connection(char **cmp, int client_fd)
{
  (void)cmp;
  send_response(client_fd, QUIT, "Logout");
  return (1);
}
