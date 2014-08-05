#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

int isWrong(char* currentArgs, int argc)
{
  char *autorizedArgs = "ABbCcEeHhiLlnoqRsVvwxyZ"; // will contain all the arguments developed in this project 23
  int j = 0, i = 0, fail = 0;

  if(currentArgs[0]) // if the user input arguments
    {
      for (i = 0; i < strlen(currentArgs); i++)
        {
          fail = 0;
          for (j = 0; j < strlen(autorizedArgs); j++)
            {
              if (currentArgs[i] == autorizedArgs[j])
                {
                  fail = 1;

                }
            }
          if (fail == 0)
            {
              printf("grep: invalid option -- '%c'\n", currentArgs[i]);
              printf("Usage: grep [OPTION]... PATTERN [FILE]...\nTry `grep --help' for more information.");
              return 1;
            }

        }
      return 0;

    }

  else if (argc < 2) // if the user just wrote "grep"
    {
      printf("Usage: grep [OPTION]... PATTERN [FILE]...\nTry `grep --help' for more information.");
      return 1;
    }

  else
    return 0;
}
