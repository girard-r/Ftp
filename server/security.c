/*
** security.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/server
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar 22 20:02:44 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 20:07:04 2015 Aurélien GIRARDEAU
*/

#include "server.h"

int		check_root_dir()
{
  if (access("./home", F_OK) == 0
      && access("./home", X_OK) == 0)
    {
      chdir("./home");
      return (1);
    }
  if (mkdir("./home", S_IRUSR | S_IXUSR | S_IWUSR | S_IWGRP | S_IXGRP
	    | S_IWOTH | S_IXOTH) == -1)
    return (0);
  chdir("./home");
  return (1);
}

char		*get_server_dir(char set, char *tmp)
{
  static char	*serv_dir = NULL;

  if (set != 1)
    return (serv_dir);
  if (tmp == NULL && !(serv_dir = getcwd(NULL, 0)))
    {
      handle_errors(GETCWD, 1);
      return (NULL);
    }
  else if (tmp != NULL)
    serv_dir = tmp;
  return (serv_dir);
}
