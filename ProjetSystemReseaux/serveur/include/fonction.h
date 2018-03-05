#ifndef FONCTION_H
#define FONCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

#include <ctype.h>

int ouvertureFile(char* localisation);

int lireLigne(int fd, char *ligne);

void strtokBis(char buffer[],char* tok, char* tmpVal[]);

void chaineEnMajuscule(char*chaine);

void retireEspace(char* chaine);

#endif