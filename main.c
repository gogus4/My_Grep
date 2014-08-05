#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grep.h"
#include "utils.h"
#include "errors.h"
#include "arg_exception.h"

#define TAILLE_MAX 250

int main(int argc,char ** argv)
{
  char string_to_search[100] = "";
  char Argument[100] = "";
  char File_Name[50][50];
  int Arg_Number[10] = { -1 }; // Table for storing the number-A-B-C etc. ... Arg_Number [0] = Number-A ...
  int Number_of_line = 0;
  int i = 0, j = 0, size_name_file = 0, nb_line = 0, nb_file = 0;
  FILE* file = NULL;
  FILE * file_recursive;
  file_recursive = fopen("File_list.txt","w+");

  if(arg_help(argc,argv) != 0) return -1; // Management -- help

  if(arg_long(argc,argv) != 0) return -1; // Management of -- and convertion

  for(j=1; j<argc; j++) // Loop to retrieve the data parameters sent (argument + string to search + file(s))
    {
      if(argv[j][0]== '-')
        {
          strcat(Argument,argv[j]);

          if(argv[j][1] == 'A')
            {
              j++;
              Arg_Number[0] = atoi(argv[j]);
              j++;
            }
          else if(argv[j][1] == 'B')
            {
              j++;
              Arg_Number[1] = atoi(argv[j]);
              j++;
            }
          else if(argv[j][1] == 'C')
            {
              j++;
              Arg_Number[2] = atoi(argv[j]);
              j++;
            }

          else if(argv[j][1] == 'e')
            {
              j++;
              strcpy(string_to_search,argv[j]);
            }

          else if(argv[j][1] == 'm')
            {
              j++;
              Arg_Number[3] = atoi(argv[j]);
              j++;
            }
        }

      else // Recover the rest ( String to search + File list )
        {
          strcpy(File_Name[size_name_file],argv[j]);
          if(size_name_file != 0)
            fprintf(file_recursive,"%s\n",argv[j]);
          size_name_file++;
        }
    }
  if(strcmp(string_to_search,"") == 0)
    {
      strcpy(string_to_search,File_Name[0]); //String to search
      i = 1; // Change the value for i to browse for the name of the files
    }
  else
    {
      i = 0;
    }

  delete_duplicates(Argument); // To delete duplicates

  for(j=0; j<=strlen(Argument); j++) // To delete the "-" at the beginning
    {
      Argument[j] = Argument[j+1];
    }

  nb_file = size_name_file; // Knowing the number of file

  if(i == 1) // If accomodation File_Name[0] = string_to_search
    {
      nb_file = size_name_file - 1;
    }

  if(nb_file == 0)
    {
      char ** array1 = NULL;
      FunctionGrepWithArguments(array1,string_to_search,0,Argument,"",nb_file,Number_of_line,Arg_Number);
    }

  if(isWrong(Argument, argc) == 1) // Management of error
    return 0;

  if(strstr(Argument,"R")) // Recording in a text file
    {
      for(i; i<size_name_file; i++)
        {
          fclose(file_recursive);
          file_recursive = fopen("File_list.txt","w+");
          list_recursively(File_Name[i],file_recursive);
        }
      nb_file = 2;
    }

  rewind(file_recursive);
  char chaine[TAILLE_MAX];

  while(fgets(chaine, TAILLE_MAX, file_recursive) != NULL)
    {
      char chaine1[TAILLE_MAX];
      int h;
      for(h = 0 ; h < strlen(chaine)-1; h++)
        {
          chaine1[h] = chaine[h];
        }
      chaine1[h] = '\0';

      file = fopen(chaine1, "r"); // Open file

      if (file != NULL)
        {
          nb_line = NbLine(file);
          char tableau[nb_line][TAILLE_MAX]; // Initializing a 2 dimension table containing the file
          RemplirTableau(file,tableau); // Fills the table
          FunctionGrepWithArguments(tableau,string_to_search,nb_line,Argument,chaine1,nb_file,Number_of_line,Arg_Number);
        }
      else
        {
          if(!strstr(Argument,"s"))
            printf("grep: %s: No such file or directory\n",chaine1);
        }
    }
  return 0;
}


