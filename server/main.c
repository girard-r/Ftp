/*
** main.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp/includes
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Tue Mar 10 19:42:10 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:11:46 2015 Aurélien GIRARDEAU
*/

#include "server.h"

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
  if (ac == 2)
    return (is_num(av[1]));
  return (handle_errors(ARG, 0));
}

int	main(int ac, char **av)
{
  t_fd	fd;

  if (check_arguments(ac, av) == -1
      || init_server(&fd, atoi(av[1])) == -1
      || accept_clients(fd) == -1)
    return (1);
  return (0);
}
