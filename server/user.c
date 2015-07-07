/*
** user.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/server
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Thu Mar 19 15:45:04 2015 Aurélien GIRARDEAU
** Last update Sat Mar 21 20:29:16 2015 Aurélien GIRARDEAU
*/

#include "server.h"

char		*store_user(char *username, char set)
{
  static char	*user = NULL;

  if (set == 1)
    {
      if (user != NULL)
	free(user);
      user = (username == NULL ? NULL : strdup(username));
    }
  return (user);
}

char		*store_password(char *new_pass, char set)
{
  static char	*password = NULL;

  if (set == 1)
    {
      if (password != NULL)
	free(password);
      password = (new_pass == NULL ? NULL : strdup(new_pass));
    }
  return (password);
}

void		free_tab(char **tab)
{
  int		i;

  i = 0;
  while (tab[i])
    {
      if (tab[i])
	free(tab[i]);
      i += 1;
    }
  free(tab);
}
