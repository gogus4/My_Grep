#include "recursivite.h"

int nbOccurence = 0;

int list_recursively(char *path,FILE * fichier)
{
  struct dirent *reading;
  struct stat sb;
  DIR *rep;

  //printf("path : %s\n",path);
  nbOccurence++;
  if(stat(path, &sb) == -1)
    {
      /*printf("TEST");
      return;*/
    }

  switch (sb.st_mode & S_IFMT) // Not only display the files in a text file
    {
    case S_IFDIR:
      break;

    default:
      fprintf(fichier,"%s\n",path);
      break;

    }

  if(opendir(path) == NULL)
    {
      /*printf("Erreur Open path\n");
      printf("path : %s\n",path);
      return;*/
    }

  rep = opendir(path);

#if defined(unix)
  if(rep == NULL)
    return 0;
#endif

  while((reading = readdir(rep)))
    {
      if(strcmp(reading->d_name,".") != NULL && strcmp(reading->d_name,"..") != NULL)
        {
          char Tab[256];

          strcpy(Tab,path);

#if defined(unix)
          strcat(Tab,"/"); // If we are on linux
#elif defined (_WIN32)
          strcat(Tab,"\\");
#endif
          strcat(Tab,reading->d_name);

          switch (sb.st_mode & S_IFMT)
            {
            case S_IFDIR:
              list_recursively(Tab,fichier);
              break;
            }
        }
    }

  return nbOccurence;
}
