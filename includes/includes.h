/*
** includes.h for includes in /home/girard_r/rendu/PSU_2014_myftp/includes
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Tue Mar 10 19:47:39 2015 Aurélien GIRARDEAU
** Last update Wed Mar 18 20:28:36 2015 Aurélien GIRARDEAU
*/

#ifndef INCLUDES_H_
# define INCLUDES_H_

# define PACKAGE_SIZE 1024

typedef enum
  {
    USER = 1,
    USER_OK,
    QUIT,
    LIST,
    CWD,
    RETR,
    STOU,
    PWD,
    PASS,
    PASS_OK,
    NOTFOUND
  }	e_rfc;

#endif
