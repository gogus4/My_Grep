#include "utils.h"

void RemplirTableau(FILE* NomFichier, char Tableau[][TAILLE_MAX])
{
  int i=0;
  char Chaine[TAILLE_MAX];

  while (fgets(Chaine, TAILLE_MAX, NomFichier) != NULL)
    {
      strcpy(Tableau[i],Chaine);
      i++;
    }

  rewind(NomFichier); // Move to beginning of file
}

int NbLine(FILE * NomFichier)
{
  int NombreDeLigne = 0;
  char chaine[TAILLE_MAX];
  while (fgets(chaine, TAILLE_MAX, NomFichier) != NULL) // It reads the file as you do not get an error (NULL)
    {
      NombreDeLigne++;
    }

  rewind(NomFichier); // Move to beginning of file

  return NombreDeLigne;
}

char * ConverInMinuscule(char Tableau[TAILLE_MAX])
{
  int i;
  char TabInMin[TAILLE_MAX];
  for(i=0; i<=strlen(Tableau); i++)
    {
      if(Tableau[i] >= 65 && Tableau[i] <= 90)
        TabInMin[i] = tolower(Tableau[i]);

      else
        TabInMin[i] = Tableau[i];
    }
  return TabInMin;
}

void ConverInMinuscule1(char Tableau[TAILLE_MAX], char * Tab)
{
  int i;
  for(i=0; i<=strlen(Tableau); i++)
    {
      if(Tableau[i] >= 65 && Tableau[i] <= 90)
        Tab[i] = tolower(Tableau[i]);

      else
        Tab[i] = Tableau[i];
    }
}

char * ConverInMajuscule(char Tableau[TAILLE_MAX])
{
  int i;
  char TabInMin[TAILLE_MAX];
  for(i=0; i<=strlen(Tableau); i++)
    {
      TabInMin[i] = toupper(Tableau[i]);
    }

  return TabInMin;
}

void delete_duplicates(char *Argument)
{
  int i,j,k=0;
  char TabCopie[strlen(Argument)];
  char permute;

  for(i=0; i<strlen(Argument); i++) // Loop to sort the arguments to facilitate erasing duplicates
    {
      for(j=0; j<strlen(Argument)-1; j++)
        {
          if(Argument[j] > Argument[j+1])
            {
              permute = Argument[j];
              Argument[j] = Argument[j+1];
              Argument[j+1] = permute;
            }
        }
    }

  TabCopie[0] = Argument[0];
  for(i=0; i<=strlen(Argument); i++) // Remove duplicate
    {
      if(TabCopie[k] != Argument[i])
        {
          TabCopie[k+1] = Argument[i];
          k++;
        }
    }
  TabCopie[k] = '\0';

  for(i=0; i<=strlen(TabCopie); i++) // True copy of the array of arguments
    {
      Argument[i] = TabCopie[i];
    }
}

char *strcase(const char *s,const char *find) // Strcasesstr function (Windows + Unix)
{
  char c, sc;
  size_t len;

  if ((c = *find++) != 0)
    {
      c = tolower((unsigned char)c);
      len = strlen(find);
      do
        {
          do
            {
              if ((sc = *s++) == 0)
                return (NULL);
            }
          while ((char)tolower((unsigned char)sc) != c);
        }
      while (strncasecmp(s, find, len) != 0);
      s--;
    }
  return ((char *)s);
}

int length(char *string)
{
  char car;
  int cpt = 0;
  do
    {
      car = string[cpt];
      cpt++;
    }
  while(car != '\0');
  if(string[cpt-2] == '\n')
    cpt--;

  return cpt;
}

int str_istr (const char *cs, const char *ct)
{
  int index = -1;

  if (cs != NULL && ct != NULL)
    {
      char *ptr_pos = NULL;

      ptr_pos = strstr (cs, ct);
      if (ptr_pos != NULL)
        {
          index = ptr_pos - cs;
        }
    }
  return index;
}

int optionW(char *string, char *stringRef, char *args) // function necessary to obtain the result with the w option
{
  int isW = 0, result = 0;

  if (strstr(args, "i"))
    {
      strcpy(string, ConverInMinuscule(string));
      strcpy(stringRef, ConverInMinuscule(stringRef));
      result = str_istr(string, stringRef);

      if(result == 0)
        {
          if (string[result + strlen(stringRef)] == ' ')
            isW = 1;
          if ((string[result + strlen(stringRef)] == '\0') || (string[result + strlen(stringRef)] == '\n'))
            isW = 1;
        }
      else
        {
          if ((string[result + strlen(stringRef)] == ' ') && (string[result -1] == ' '))
            isW = 1;
          if (((string[result + strlen(stringRef)] == '\0') || (string[result + strlen(stringRef)] == '\n')) && (string[result -1] == ' '))
            isW = 1;
        }
    }

  else
    {
      result = str_istr(string, stringRef);

      if(result == 0)
        {
          if (string[result + strlen(stringRef)] == ' ')
            isW = 1;
          if ((string[result + strlen(stringRef)] == '\0') || (string[result + strlen(stringRef)] == '\n'))
            isW = 1;
        }
      else
        {
          if ((string[result + strlen(stringRef)] == ' ') && (string[result -1] == ' '))
            isW = 1;
          if (((string[result + strlen(stringRef)] == '\0') || (string[result + strlen(stringRef)] == '\n')) && (string[result -1] == ' '))
            isW = 1;
        }
    }
  return isW;
}

char* fctO(char *string, char *stringRef, char *args)
{
  int result = 0, i = 0, j = 0;
  if (strstr(args, "i"))
    {
      strcpy(string, ConverInMinuscule(string));
      strcpy(stringRef, ConverInMinuscule(stringRef));
    }
  result = str_istr(string, stringRef);
  char stringToReturn[strlen(stringRef)];
  for (i = result; i < (result + strlen(stringRef)); i++)
    {
      stringToReturn[j] = string[i];
      j++;
    }

  return stringToReturn;
}

void set_la_color(unsigned short color)
{
  HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hcon,color);
}
