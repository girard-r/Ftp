#!/bin/sh
## test.sh for myftp in /home/girard_r/rendu/PSU_2014_myftp
## 
## Made by Aurélien GIRARDEAU
## Login   <girard_r@epitech.net>
## 
## Started on  Sun Mar 22 18:10:25 2015 Aurélien GIRARDEAU
## Last update Sun Mar 22 23:32:21 2015 Aurélien GIRARDEAU
##

make re
make clean
mkdir -p "./local"
mv "client" "./local"
mkdir -p "./home"
mkdir -p "./home/Anonymous"
mkdir -p "./home/Anonymous/Documents"
mkdir -p "./home/Anonymous/Downloads"
mkdir -p "./home/Anonymous/Movies"
cp "./test/myftp.acl" "."
