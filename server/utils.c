/*
** utils.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/server
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar 22 20:12:25 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:13:57 2015 Aurélien GIRARDEAU
*/

#include "server.h"

char		*concat_str(char *s1, char *s2, char *s3)
{
  char		*s4;

  if ((s4 = malloc(strlen(s1) + strlen(s2) + strlen(s3) + 1)) == NULL)
    return (NULL);
  strcpy(s4, s1);
  s4[strlen(s1)] = 0;
  strcat(s4, s2);
  strcat(s4, s3);
  return (s4);
}

char		*my_str_replace(char *haystack, char *needle, char *replace)
{
  char		*ret;
  int		rd_size;

  ret = NULL;
  rd_size = strlen(needle);
  if (strncmp(haystack, needle, rd_size) == 0)
    {
      if ((ret = malloc(strlen(haystack)
			+ strlen(replace) - rd_size + 1)) == NULL)
	return (NULL);
      strcpy(ret, replace);
      strcat(ret, &haystack[rd_size]);
      return (ret);
    }
  return (haystack);
}
