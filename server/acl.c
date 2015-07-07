/*
** acl.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/server
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sat Mar 21 17:39:52 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 23:20:08 2015 Aurélien GIRARDEAU
*/

#include "server.h"

char		*acl_path(char *new_path, char set)
{
  char		buff[1024];
  static char	*path = NULL;

  if (set == 1 && new_path != NULL
      && realpath(new_path, buff) != NULL)
    {
      if (path != NULL)
	free(path);
      path = strdup(buff);
    }
  if (path == NULL
      && realpath("myftp.acl", buff) != NULL)
    path = strdup(buff);
  return (path);
}

int		create_acl(int *fd, char *file_acl)
{
  acl_path(file_acl, 1);
  if ((*fd = open(file_acl, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR
		  | S_IWGRP | S_IRGRP | S_IROTH)) == -1)
    return (-1);
  write(*fd, "Anonymous\n", 10);
  close(*fd);
  if ((*fd = open(file_acl, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR
		 | S_IWGRP | S_IRGRP | S_IROTH)) == -1)
    return (-1);
  return (0);
}

int		parse_acl_line(char ***acl, char *tmp, int cmp)
{
  char		*cpy;

  cpy = NULL;
  tmp[strlen(tmp) - 1] = 0;
  if ((cpy = strtok(tmp, " ")) == NULL)
    return (-1);
  else
    if (((*acl)[cmp] = strdup(cpy)) == NULL)
      return (-1);
  if ((cpy = strtok(NULL, " ")) != NULL)
    {
      if (((*acl)[cmp + 1] = strdup(cpy)) == NULL)
	return (-1);
    }
  else
    {
      if (((*acl)[cmp + 1] = strdup("")) == NULL)
	return (-1);
    }
  (*acl)[cmp + 2] = NULL;
  return (0);
}

char		**parse_acl(int *fd)
{
  char		**acl;
  FILE		*fstream;
  size_t	len;
  char		*tmp;
  int		cmp;

  len = 0;
  tmp = NULL;
  cmp = 0;
  if ((fstream = fdopen(*fd, "r")) == NULL
      || (acl = malloc(sizeof(char *) * 3)) == NULL)
    return (NULL);
  while (getline(&tmp, &len, fstream) > 0)
    {
      if (cmp != 0)
	{
	  if ((acl = realloc(acl, sizeof(char *) * (cmp + 3))) == NULL)
	    return (NULL);
	}
      if (parse_acl_line(&acl, tmp, cmp) == -1)
	return (NULL);
      cmp += 2;
    }
  free(tmp);
  return (acl);
}

char		**get_acl(char *file_acl)
{
  int		fd;
  char		**acl;
  char		*tmp;

  fd = -1;
  tmp = NULL;
  if (file_acl == NULL)
    tmp = strdup("myftp.acl");
  else
    tmp = file_acl;
  if ((fd = open(tmp, O_RDWR, S_IWUSR | S_IRUSR
		 | S_IWGRP | S_IRGRP | S_IROTH)) == -1)
    {
      if (create_acl(&fd, tmp) == -1)
	return (NULL);
    }
  if (file_acl == NULL)
    free(tmp);
  if ((acl = parse_acl(&fd)) == NULL)
    return (NULL);
  close_fd(fd);
  return (acl);
}
