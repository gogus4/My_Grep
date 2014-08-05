#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arg_help(int argc, char** argv)
{
  FILE* fichier = NULL;
  int j;
  int temp=0;

  for(j=1; j<argc; j++)
    {
      if (strstr(argv[j], "--help") != 0)
        {
          char caract = "";
          fichier = fopen("grep_help.txt", "r");
          do
            {
              caract = fgetc(fichier);
              printf("%c", caract);
            }
          while (caract != EOF);

          return temp = -1;
        }
      else
        temp = 0 ;
    }
  return temp;
}

int arg_long(int argc, char** argv)
{
  int j;
  for(j=1; j<argc; j++)
    {
      if (argv[j][0]== '-' && argv[j][1]== '-')
        {
          if ( strcmp(argv[j], "--text") == 0)
            argv[j]="-a";
          else if ( strcmp(argv[j], "--byte-offset") == 0)
            argv[j]="-b";
          else if ( strcmp(argv[j], "--count") == 0)
            argv[j]="-c";
          else if ( strcmp(argv[j], "--extended-regexp") == 0)
            argv[j]="-E";
          else if ( strcmp(argv[j], "--fixed-strings") == 0)
            argv[j]="-F";
          else if ( strcmp(argv[j], "--perl-regexp") == 0)
            argv[j]="-P";
          else if ( strcmp(argv[j], "---basic-regexp") == 0)
            argv[j]="-G";
          else if ( strcmp(argv[j], "--with-filename") == 0)
            argv[j]="-H";
          else if ( strcmp(argv[j], "--no-filename") == 0)
            argv[j]="-h";
          else if ( strcmp(argv[j], "--ignore-case") == 0)
            argv[j]="-i";
          else if ( strcmp(argv[j], "--files-without-match") == 0)
            argv[j]="-L";
          else if ( strcmp(argv[j], "--files-with-matches") == 0)
            argv[j]="-l";
          else if ( strcmp(argv[j], "--line-number") == 0)
            argv[j]="-n";
          else if ( strcmp(argv[j], "--only-matching") == 0)
            argv[j]="-o";
          else if ( strcmp(argv[j], "--quiet") == 0)
            argv[j]="-q";
          else if ( strcmp(argv[j], "--silent") == 0)
            argv[j]="-q";
          else if ( strcmp(argv[j], "--recursive") == 0)
            argv[j]="-R";
          else if ( strcmp(argv[j], "--no-messages") == 0)
            argv[j]="-s";
          else if ( strcmp(argv[j], "--binary") == 0)
            argv[j]="-U";
          else if ( strcmp(argv[j], "--unix-byte-offsets") == 0)
            argv[j]="-u";
          else if ( strcmp(argv[j], "--version") == 0)
            argv[j]="-V";
          else if ( strcmp(argv[j], "--invert-match") == 0)
            argv[j]="-v";
          else if ( strcmp(argv[j], "--word-regexp") == 0)
            argv[j]="-w";
          else if ( strcmp(argv[j], "--line-regexp") == 0)
            argv[j]="-x";
          else if ( strcmp(argv[j], "--null") == 0)
            argv[j]="-Z";
          else if ( strcmp(argv[j], "--null-data") == 0)
            argv[j]="-z";
          else
            {
              printf("grep: invalid option '%s'\n",argv[j]);
              printf("Usage: grep [OPTION]... PATTERN [FILE]...\nTry `grep --help' for more information.");
              return -1;
            }
        }
    }
  return 0;
}
