/*
** user_builtin.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/server
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar 22 19:58:11 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:13:37 2015 Aurélien GIRARDEAU
*/

#include "server.h"

int		user_got_pass()
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
	  if (*(acl[i + 1]) != 0)
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

int		user_exists(char *user)
{
  char		**acl;
  int		i;

  i = 0;
  if ((acl = get_acl(acl_path(NULL, 0))) == NULL)
    return (0);
  while (acl[i])
    {
      if (i % 2 == 0
	  && strcmp(acl[i], user) == 0)
	{
	  free_tab(acl);
	  return (1);
	}
      i += 1;
    }
  free_tab(acl);
  return (0);
}

int		check_user()
{
  if (store_user(NULL, 0) == NULL)
    return (0);
  return (1);
}

int		go_bounce()
{
  char		*user;
  char		*path;
  char		*serv_dir;

  if ((serv_dir = get_server_dir(0, NULL)) != NULL)
    {
      chdir(serv_dir);
      chdir("../");
      free(serv_dir);
    }
  if (!check_root_dir())
    return (-1);
  if ((user = store_user(NULL, 0)) != NULL)
    {
      if ((path = concat_str(get_server_dir(1, NULL), "/", user)) == NULL)
	return (-1);
      if (access(path, F_OK) == -1
	  && mkdir(path, S_IRUSR | S_IXUSR | S_IWUSR | S_IWGRP | S_IXGRP
		   | S_IWOTH | S_IXOTH) == -1)
	    return (-1);
      chdir(path);
      return (0);
    }
  return (-1);
}

int		request_user(char **cmp, int client_fd)
{
  if (cmp[1])
    {
      store_user(NULL, 1);
      if (!user_exists(cmp[1]))
	{
	  send_response(client_fd, USER, "User does not exist. Please try again.\
 You can connect with Anonymous for public directory");
	  return (0);
	}
      store_user(cmp[1], 1);
      store_password(NULL, 1);
      if (user_got_pass())
	{
	  send_response(client_fd, USER_OK, "User ok need password");
	  send_response(client_fd, PASS, "Please enter your password");
	}
      else
	{
	  send_response(client_fd, PASS_OK, "User ok, no password needed");
	  go_bounce();
	}
    }
  else
    send_response(client_fd, USER, "Please enter a username.");
  return (0);
}
