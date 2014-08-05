#include "grep.h"
#include <string.h>

#if defined(unix)
#define color_char(param) printf("\033[%sm",param)
#endif

int nbRepetition = 0 ;

void FunctionGrep(char** Array,char * string_to_search,int number_of_line)
{
  int i;
  for(i=0; i<number_of_line; i++)
    {
      if(strstr(Array[i],string_to_search) != NULL)
        {
          printf("%s",Array[i]);
        }
    }
}

void FunctionGrepWithArguments(char Array[][TAILLE_MAX],char * string_to_search,int number_of_line,char * Argument,char * file_name,int file_number,int line_number_before_first_search,int * arg_number)
{
  int i=0,j=0,number_of_caracters = 0,number_of_caracters_argA = 0,nb_passage_enB = 0 ; // Lets not show -- at the beginning
  int nbRepet = 0; // Lets not display the -- in the argument A
  int nbOccurence = FunctionNbOccurence(Array,string_to_search,number_of_line,Argument); // Calculating the number of times a match is found

  if(file_number == 0)
    {
      TestArgument(Argument,Array,j,number_of_caracters,file_number,file_name,string_to_search);
    }

  if(strstr(Argument,"V")) // The argument "V" works alone
    {
      FILE * fichier;
      fichier = fopen("VersionGrep.txt", "r");

      if (fichier != NULL)
        {
          char chaine[TAILLE_MAX];
          while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // It reads the file as you do not get an error (NULL)
            {
              printf("%s",chaine);
            }
        }
      return ;
    }

  if(strstr(Argument,"q")) // The argument "q" works alone
    {
      return ;
    }

  if(strstr(Argument,"L")) // The argument "L" only works with the "-i"
    {
      if(FunctionNbOccurence(Array,string_to_search,number_of_line,Argument) == 0)
        {
          printf("%s",file_name);
        }

      if(nbRepetition < file_number-1 && nbRepetition != 0)
        printf("\n");

      nbRepetition ++;
      return ;
    }


  if(strstr(Argument,"l")) // The argument "l" only works with the "-i"
    {
      if(FunctionNbOccurence(Array,string_to_search,number_of_line,Argument) != 0)
        {
          printf("%s",file_name);
        }

      if(nbRepetition < file_number-1 && nbRepetition != 0)
        printf("\n");

      nbRepetition ++;

      return ;
    }

  if(strstr(Argument,"c")) // The argument "c" only works with the "-i"
    {
      int NbreOccurence = FunctionNbOccurence(Array,string_to_search,number_of_line,Argument); // Number of occurrences for Argument -o

      if(file_number > 1 && !(strstr(Argument,"h")) && !(strstr(Argument,"H"))) // If there are more files displayed on the file name
        {
          if(strstr(Argument,"Z"))
            printf("%s",file_name);

          else
            printf("%s:",file_name);
        }


      if(strstr(Argument,"H") && !(strstr(Argument,"h")))
        {
          if(strstr(Argument,"Z"))
            printf("%s",file_name);

          else
            printf("%s:",file_name);
        }

      printf("%d",NbreOccurence);

      if(nbRepetition < file_number-1 && nbRepetition != 0 )
        printf("\n");

      nbRepetition ++;

      return ;
    }

  for(i=0; i<number_of_line; i++) // Loop over the number of line File (String character)
    {
      /* Process Regular expression */
      if(strstr(Argument,"E") != NULL)
        {
          /* Traitement Expression régulière */
          if(strstr(Argument,"E") != NULL)
            {
              if(strstr(Argument,"i") != NULL || strstr(Argument,"y") != NULL) // If the argument "-i" is present
                {
                  char Test[250];
                  ConverInMinuscule1(string_to_search,Test);
                  char TabMin[2048];
                  ConverInMinuscule1(Array[i],TabMin);
                  if(motifEstOk(Test,TabMin) == 1)
                    {
                      TestArgument(Argument,Array,i,number_of_caracters,file_number,file_name,string_to_search);
                    }
                }
              // Regular expression code
              else
                {
                  if(motifEstOk(string_to_search,Array[i]) == 1)
                    {
                      TestArgument(Argument,Array,i,number_of_caracters,file_number,file_name,string_to_search);
                    }
                }
            }
        }


      else if(strstr(Argument,"i") != NULL || strstr(Argument,"y") != NULL) // If the argument "-i" is present
        {
          if((strcase(Array[i],string_to_search) != NULL) && strstr(Argument,"v") == NULL) // We take no account of case-sensitive and there in no "-v"
            {
              TestArgument(Argument,Array,i,number_of_caracters,file_number,file_name,string_to_search);

              if(strstr(Argument,"A") != NULL && i != number_of_line-1) // A : Display number of lines seized after search
                {
                  int p,k=0;
                  nbRepet ++;
                  k=i+1;
                  p=0;
                  int estUtiliser = 0;
                  int nb = number_of_caracters;
                  nb += strlen(Array[k]) -1 ;

                  while(strcase(Array[k],string_to_search) == NULL)
                    {
                      number_of_caracters_argA = strlen(Array[k]);

                      if(p < arg_number[0])
                        {
                          TestArgument(Argument,Array,k,nb,file_number,file_name,string_to_search);
                        }

                      else if (estUtiliser == 0 && p >= 1)
                        {
                          if(nbRepet != nbOccurence)
                            printf("--\n");

                          estUtiliser = 1;
                        }
                      k++;
                      p++;

                      if(estUtiliser == 1) // Exits the loop to the end of file
                        break;
                    }
                  i = i + p;
                  number_of_caracters += strlen(Array[p-1]);
                }
            }

          else if(strcase(Array[i],string_to_search) == NULL && strstr(Argument,"v") != NULL) // We take no account of case-sensitive and there in "-v"
            {
              TestArgument(Argument,Array,i,number_of_caracters,file_number,file_name,string_to_search);

              if(strstr(Argument,"A") != NULL) // A : Display number of lines seized after search
                {
                  if(strcase(Argument,"A") != NULL && i != number_of_line-1) // A : Display number of lines seized after search
                    {
                      int p,k=0;
                      nbRepet ++;
                      k=i+1;
                      p=0;
                      int estUtiliser = 0;
                      int nb = number_of_caracters;
                      nb += strlen(Array[k]) -1 ;

                      while(strstr(Array[k],string_to_search) == NULL)
                        {
                          number_of_caracters_argA = strlen(Array[k]);

                          if(p < arg_number[0])
                            {
                              TestArgument(Argument,Array,k,nb,file_number,file_name,string_to_search);
                            }

                          else if (estUtiliser == 0 && p >= 1)
                            {
                              if(nbRepet != nbOccurence)
                                printf("--\n");

                              estUtiliser = 1;
                            }
                          k++;
                          p++;

                          if(estUtiliser == 1) // Exits the loop to the end of file
                            break;
                        }
                      i = i + p;
                      number_of_caracters += strlen(Array[p-1]);
                    }
                }
            }
        }

      else // Si l'argument -i ou -y pas présent
        {
          if((strstr(Array[i],string_to_search) != NULL) && strstr(Argument,"v") == NULL) // We take no account of case-sensitive and there in no "-v"
            {
              if(strstr(Argument,"B") != NULL) // A : Display number of lines seized after search
                {
                  int p=arg_number[1],k=0,test=0;;
                  k=i-1;

                  while(strstr(Array[k],string_to_search) == NULL)
                    {
                      test++;
                      k--;

                      if(k<0)
                        break;
                    }

                  if(test > arg_number[1] && nb_passage_enB != 0 && arg_number[1] != 0)
                    printf("--\n");

                  k=i-1;

                  while(strstr(Array[k],string_to_search) == NULL && p != 0)
                    {
                      printf("%s",Array[k]);
                      k--;

                      if(k<0)
                        break;

                      p--;
                    }

                  nb_passage_enB = 1;
                }

              if(strstr(Argument,"C"))
                {
                  int nb,nb1;
                  int indice =0;
                  for(nb=0; nb<number_of_line; nb++)
                    {
                      if(strstr(Array[nb],string_to_search) != NULL)
                        {
                          for(nb1=nb-arg_number[2]; nb1<nb; nb1++)
                            {
                              if(strstr(Array[nb1],string_to_search) != NULL)
                                break;

                              if(nb1 >= indice)
                                printf("%s",Array[nb1]);
                            }

                          printf("%s",Array[nb]);

                          for(nb1=nb+1; nb1<=nb+arg_number[2]; nb1++)
                            {
                              if(strstr(Array[nb1],string_to_search) != NULL)
                                break;

                              if(nb1 < number_of_line)
                                printf("%s",Array[nb1]);

                            }
                          indice = nb1;
                        }
                    }
                  return ;
                }

              if(!strstr(Argument,"C"))
                TestArgument(Argument,Array,i,number_of_caracters,file_number,file_name,string_to_search);

              if(strstr(Argument,"A") != NULL && i != number_of_line-1) // A : Display number of lines seized after search
                {
                  int p,k=0;
                  nbRepet ++;
                  k=i+1;
                  p=0;
                  int estUtiliser = 0;
                  int nb = number_of_caracters;
                  nb += strlen(Array[k]) -1 ;

                  while(strstr(Array[k],string_to_search) == NULL)
                    {
                      number_of_caracters_argA = strlen(Array[k]);

                      if(p < arg_number[0])
                        {
                          TestArgument(Argument,Array,k,nb,file_number,file_name,string_to_search);
                        }

                      else if (estUtiliser == 0 && p >= 1)
                        {
                          if(nbRepet != nbOccurence)
                            printf("--\n");

                          estUtiliser = 1;
                        }
                      k++;
                      p++;

                      if(estUtiliser == 1) // Exits the loop to the end of file
                        break;
                    }
                  i = i + p;
                  number_of_caracters += strlen(Array[p-1]);
                }
            }

          else if(strstr(Array[i],string_to_search) == NULL && strstr(Argument,"v") != NULL) // We take account of case-sensitive and there in "-v"
            {
              TestArgument(Argument,Array,i,number_of_caracters,file_number,file_name,string_to_search);

              if(strstr(Argument,"A"))
                {
                  if(strstr(Argument,"A") != NULL && i != number_of_line-1) // A : Display number of lines seized after search
                    {
                      int p,k=0;
                      nbRepet ++;
                      k=i+1;
                      p=0;
                      int estUtiliser = 0;
                      int nb = number_of_caracters;
                      nb += strlen(Array[k]) -1 ;

                      while(strstr(Array[k],string_to_search) == NULL)
                        {
                          number_of_caracters_argA = strlen(Array[k]);

                          if(p < arg_number[0])
                            {
                              TestArgument(Argument,Array,k,nb,file_number,file_name,string_to_search);
                            }

                          else if (estUtiliser == 0 && p >= 1)
                            {
                              if(nbRepet != nbOccurence)
                                printf("--\n");

                              estUtiliser = 1;
                            }
                          k++;
                          p++;

                          if(estUtiliser == 1) // Exits the loop to the end of file
                            break;
                        }
                      i = i + p;
                      number_of_caracters += strlen(Array[p-1]);
                    }
                }
            }
        }

      number_of_caracters += strlen(Array[i]);
    }
  nbRepetition ++;
}



int FunctionNbOccurence(char Array[][TAILLE_MAX],char * string_to_search,int number_of_line,char * Argument) // Calculating the number of times to repeat the string
{
  int i,j=0;
  for(i=0; i<number_of_line; i++)
    {
      if(strstr(Argument,"i") != NULL || strstr(Argument,"y") != NULL)
        {
          if(strcase(Array[i],string_to_search) != NULL)
            {
              j++;
            }
        }

      else
        {
          if(strstr(Array[i],string_to_search) != NULL)
            {
              j++;
            }
        }
    }
  return j;
}

int FunctionArgA(char Array[][TAILLE_MAX],char * string_to_search,int number_of_line)
{
  int i,j=1;
  int p = 0;
  for(i=0; i<number_of_line; i++)
    {
      if(strstr(Array[i],string_to_search) != NULL)
        {
          j=i+1;
          p=0;
          while(p < 3 && strstr(Array[j],string_to_search) == NULL)
            {
              printf("%s",Array[j]);
              j++;
              p++;
            }

          printf("P : %d\n",p);
          i = i + p;
        }
    }
}

void TestArgumentA(char * Argument,char Array[][TAILLE_MAX],int i,int NombreDeCaractere,int file_number,char * file_name,char * string_to_search,int number_of_line) // CASE: A function for the argument
{
  int j;
  if(strstr(Argument,"A") != NULL) // A : Display number of lines seized after search
    {
      int argA = FunctionArgA(Array,string_to_search,number_of_line);
      if(i == argA)
        {
          for(j=argA+1; j<=argA+2; j++)
            {
              if(strstr(Array[j],string_to_search) == NULL)
                {
                  TestArgument(Argument,Array,j,NombreDeCaractere,file_number,file_name,string_to_search);

                  if(strstr(Array[j+1],string_to_search) != NULL)
                    {
                      break;
                    }
                }
            }
        }
    }
}

void TestArgument(char * Argument,char Array[][TAILLE_MAX],int j,int NombreDeCaractere,int file_number,char * file_name,char * string_to_search) // Used to test the arguments and display values ​​accordingly
{
  if(file_number == 0) // Test without a filename
    {
      int i = 0;
      char ChaineLu[256];

      while(gets(ChaineLu) != NULL)
        {
          i++;

          if(!(strstr(Argument,"i")))
            {
              if(strstr(ChaineLu,string_to_search) != NULL)
                {
                  if(strstr(Argument,"n")) // If the argument contains the character "n"
                    {
#if defined(unix)
                      color_char("32;48");
                      printf("%d",i);
                      color_char("36;48");
                      printf(":");
                      color_char("0");
#elif defined (_WIN32)
                      set_la_color(2);
                      printf("%d",i);
                      set_la_color(3);
                      printf(":");
                      set_la_color(7);
#endif
                    }

                  afficherEnCouleur(ChaineLu,string_to_search);
                }
            }

          if(strstr(Argument,"i") != NULL)
            {
              if(strcase(ChaineLu,string_to_search) != NULL)
                {
                  if(strstr(Argument,"n")) // If the argument contains the character "n"
                    {
#if defined(unix)
                      color_char("32;48");
                      printf("%d",i);
                      color_char("36;48");
                      printf(":");
                      color_char("0");
#elif defined (_WIN32)
                      set_la_color(2);
                      printf("%d",i);
                      set_la_color(3);
                      printf(":");
                      set_la_color(7);
#endif
                    }

                  afficherEnCouleur(ChaineLu,string_to_search);
                }
            }
        }

      return;
    }

  if(strstr(Argument, "x"))
    {
      if((length(Array[j])) == length(string_to_search))
        {
          if(file_number > 1 && !(strstr(Argument,"h")) && !(strstr(Argument,"H"))) // If there are more files displayed on the file name
            {
              if(strstr(Argument,"Z"))
                {
#if defined(unix)
                  color_char("35;48");
                  printf("%s",file_name);
                  color_char("0");
#elif defined (_WIN32)
                  set_la_color(5);
                  printf("%s",file_name);
                  set_la_color(7);
#endif
                }

              else
                {
#if defined(unix)
                  color_char("35;48");
                  printf("%s",file_name);
                  color_char("36;48");
                  printf(":");
                  color_char("0");
#elif defined (_WIN32)
                  set_la_color(5);
                  printf("%s:",file_name);
                  set_la_color(3);
                  printf(":");
                  set_la_color(7);
#endif
                }

            }

          if(strstr(Argument,"H") && !(strstr(Argument,"h")))
            {
              if(strstr(Argument,"Z"))
                {
#if defined(unix)
                  color_char("35;48");
                  printf("%s",file_name);
                  color_char("0");
#elif defined (_WIN32)
                  set_la_color(5);
                  printf("%s",file_name);
                  set_la_color(7);
#endif
                }

              else
                {
#if defined(unix)
                  color_char("35;48");
                  printf("%s",file_name);
                  color_char("36;48");
                  printf(":");
                  color_char("0");
#elif defined (_WIN32)
                  set_la_color(5);
                  printf("%s:",file_name);
                  set_la_color(3);
                  printf(":");
                  set_la_color(7);
#endif
                }

            }

          if(strstr(Argument,"n")) // If the argument contains the character "n"
            {
#if defined(unix)
              color_char("32;48");
              printf("%d",j+1);
              color_char("36;48");
              printf(":");
              color_char("0");
#elif defined (_WIN32)
              set_la_color(2);
              printf("%d",j+1);
              set_la_color(3);
              printf(":");
              set_la_color(7);
#endif
            }

          if(strstr(Argument,"b")) // If the argument contains the character "b"
            {
#if defined(unix)
              color_char("32;48");
              printf("%d",NombreDeCaractere);
              color_char("36;48");
              printf(":");
              color_char("0");
#elif defined (_WIN32)
              set_la_color(2);
              printf("%d",NombreDeCaractere);
              set_la_color(3);
              printf(":");
              set_la_color(7);
#endif
            }


          printf("%s", Array[j]);
        }
      return;
    }

  if(strstr(Argument, "w"))
    {
      int var = 0;
      var = optionW(Array[j], string_to_search, Argument);
      if( var == 1)
        {
          if(file_number > 1 && !(strstr(Argument,"h")) && !(strstr(Argument,"H")))// If there are more files displayed on the file name
            {
              if(strstr(Argument,"Z"))
                {
#if defined(unix)
                  color_char("35;48");
                  printf("%s",file_name);
                  color_char("0");
#elif defined (_WIN32)
                  set_la_color(5);
                  printf("%s",file_name);
                  set_la_color(7);
#endif
                }

              else
                {
#if defined(unix)
                  color_char("35;48");
                  printf("%s",file_name);
                  color_char("36;48");
                  printf(":");
                  color_char("0");
#elif defined (_WIN32)
                  set_la_color(5);
                  printf("%s:",file_name);
                  set_la_color(3);
                  printf(":");
                  set_la_color(7);
#endif
                }
            }

          if(strstr(Argument,"H") && !(strstr(Argument,"h")))
            {
              if(strstr(Argument,"Z"))
                {
#if defined(unix)
                  color_char("35;48");
                  printf("%s",file_name);
                  color_char("0");
#elif defined (_WIN32)
                  set_la_color(2);
                  printf("%s",file_name);
                  set_la_color(7);
#endif
                }

              else
                {
#if defined(unix)
                  color_char("35;48");
                  printf("%s",file_name);
                  color_char("36;48");
                  printf(":");
                  color_char("0");
#elif defined (_WIN32)
                  set_la_color(2);
                  printf("%s:",file_name);
                  set_la_color(3);
                  printf(":");
                  set_la_color(7);
#endif
                }
            }

          if(strstr(Argument,"n")) // If the argument contains the character "n"
            {
#if defined(unix)
              color_char("32;48");
              printf("%d",j+1);
              color_char("36;48");
              printf(":");
              color_char("0");
#elif defined (_WIN32)
              set_la_color(2);
              printf("%d",j+1);
              set_la_color(3);
              printf(":");
              set_la_color(7);
#endif
            }

          if(strstr(Argument,"b")) // If the argument contains the character "b"
            {
#if defined(unix)
              color_char("32;48");
              printf("%d",NombreDeCaractere);
              color_char("36;48");
              printf(":");
              color_char("0");
#elif defined (_WIN32)
              set_la_color(2);
              printf("%d",NombreDeCaractere);
              set_la_color(3);
              printf(":");
              set_la_color(7);
#endif
            }
          afficherEnCouleur(Array[j],string_to_search);
        }

    }

  else
    {
      if(file_number > 1 && !(strstr(Argument,"h")) && !(strstr(Argument,"H"))) // If there are more files displayed on the file name
        {
          if(strstr(Argument,"Z"))
            {
#if defined(unix)
              color_char("35;48");
              printf("%s",file_name);
              color_char("0");
#elif defined (_WIN32)
              set_la_color(5);
              printf("%s",file_name);
              set_la_color(7);
#endif
            }

          else
            {
#if defined(unix)
              color_char("35;48");
              printf("%s",file_name);
              color_char("36;48");
              printf(":");
              color_char("0");
#elif defined (_WIN32)
              set_la_color(5);
              printf("%s:",file_name);
              set_la_color(3);
              printf(":");
              set_la_color(7);
#endif
            }
        }

      if(strstr(Argument,"H") && !(strstr(Argument,"h")))
        {
          if(strstr(Argument,"Z"))
            {
#if defined(unix)
              color_char("35;48");
              printf("%s",file_name);
              color_char("0");
#elif defined (_WIN32)
              set_la_color(5);
              printf("%s",file_name);
              set_la_color(7);
#endif
            }

          else
            {
#if defined(unix)
              color_char("35;48");
              printf("%s",file_name);
              color_char("36;48");
              printf(":");
              color_char("0");
#elif defined (_WIN32)
              set_la_color(5);
              printf("%s:",file_name);
              set_la_color(3);
              printf(":");
              set_la_color(7);
#endif
            }
        }

      if(strstr(Argument,"n")) // If the argument contains the character "n"
        {
#if defined(unix)
          color_char("32;48");
          printf("%d",j+1);
          color_char("36;48");
          printf(":");
          color_char("0");
#elif defined (_WIN32)
          set_la_color(2);
          printf("%d",j+1);
          set_la_color(3);
          printf(":");
          set_la_color(7);
#endif

        }


      if(strstr(Argument,"b")) // If the argument contains the character "b"
        {
#if defined(unix)
          color_char("32;48");
          printf("%d",NombreDeCaractere);
          color_char("36;48");
          printf(":");
          color_char("0");
#elif defined (_WIN32)
          set_la_color(2);
          printf("%d",NombreDeCaractere);
          set_la_color(3);
          printf(":");
          set_la_color(7);
#endif
        }

      if(strstr(Argument,"o"))// If the argument contains the character "o"
        {
          printf("%s\n", fctO(Array[j], string_to_search, Argument));
        }

      if((!(strstr(Argument,"o"))) && !(strstr(Argument, "w")) && !(strstr(Argument, "x")))
        {
          afficherEnCouleur(Array[j],string_to_search);
        }
    }
}

void afficherEnCouleur(char * ligne,char * chaineAChercher)
{
  int i = 0;
  int test = 0;
  for(i; i<strlen(ligne); i++)
    {
      if(ligne[i] == chaineAChercher[0])
        {
          test = 0;
          int estOk = 1;
          int h = i;
          int ok = i;
          int test = 0;
          for(ok+1; ok<strlen(chaineAChercher)+h; ok++)
            {
              if(ligne[ok] != chaineAChercher[test])
                {
                  estOk = 0;
                  test = 1;
                }
              test++;
            }

          if(estOk == 1)
            {
              for(h=i; h<strlen(chaineAChercher)+i; h++)
                {
#if defined(unix)
                  color_char("31;48");
                  printf("%c",ligne[h]);
                  color_char("0");

#elif defined (_WIN32)
                  set_la_color(12);
                  printf("%c",ligne[h]);
                  set_la_color(7);
#endif
                }

              i += strlen(chaineAChercher);
            }
        }
#if defined(unix)
      color_char("31;0");
      printf("%c",ligne[i]);
      color_char("0");
#elif defined (_WIN32)
      set_la_color("7");
      printf("%c",ligne[i]);
#endif

    }
}
