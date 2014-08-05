#include "reguliere.h"

int motifEstOk(char * motif,char * ligneAChercher) // Only works under linux
{
  int err;
  regex_t preg;

  err = regcomp (&preg, motif, REG_NOSUB | REG_EXTENDED);
  if (err == 0)
    {
      int match;

      match = regexec (&preg, ligneAChercher, 0, NULL, 0);

      regfree (&preg);

      if (match == 0)
        {
          return 1;
        }

      else if (match == REG_NOMATCH)
        {
          return 0;
        }
    }
}
