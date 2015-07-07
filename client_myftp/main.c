/*
** main.c for myftp_client in /home/girard_r/rendu/PSU_2014_myftp/includes
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Tue Mar 10 19:42:10 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:17:10 2015 Aurélien GIRARDEAU
*/

#include "client.h"

int		is_num(char *str)
{
  unsigned int	i;

  i = 0;
  while (str[i])
    {
      if (!isdigit(str[i]))
	return (handle_errors(ARG, 0));
      i += 1;
    }
  return (0);
}

int		check_arguments(int ac, char **av)
{
  if (ac == 3)
    return (is_num(av[2]));
  return (handle_errors(ARG, 0));
}

int		main(int ac, char **av)
{
  int		sock_fd;

  if (check_arguments(ac, av) == -1
      || (sock_fd = init_client(atoi(av[2]), av[1])) == - 1
      || process_client(sock_fd) == -1
      || close_fd(sock_fd) == -1)
    return (1);
  return (0);
}
