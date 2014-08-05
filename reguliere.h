#include <stdio.h>
#include <stdlib.h>

#if defined(unix)
#include <regex.h> // Si l'on est sur linux
#elif defined (_WIN32)
#include "regex.h"
#endif

int motifEstOk(char * motif,char * ligneAChercher);
