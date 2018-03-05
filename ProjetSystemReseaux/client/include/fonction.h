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
#include <stdbool.h>

bool verifHeure(int heureSaisie);

bool verifHeureBis(int heure1, int heureSaisie);

bool verifMinute(int minuteSaisie);

bool verifMinuteBis(int heure1, int heure2 ,int minute1, int minuteSaisie);

#endif