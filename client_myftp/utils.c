/*
** utils.c for myftp_client in /home/girard_r/rendu/PSU_2014_myftp
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar 22 21:25:41 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:26:13 2015 Aurélien GIRARDEAU
*/

#include "client.h"

char		*concat_str(char *s1, char *s2)
{
  char		*s3;

  if ((s3 = malloc(strlen(s1) + strlen(s2) + 1)) == NULL)
    return (NULL);
  strcpy(s3, s1);
  s3[strlen(s1)] = 0;
  strcat(s3, s2);
  return (s3);
}
