#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Management of colors

#define TAILLE_MAX 250

int NbLine(FILE * NomFichier);
char * ConverInMinuscule(char Tableau[TAILLE_MAX]);
void ConverInMinuscule1(char Tableau[TAILLE_MAX], char * Tab);
char * ConverInMajuscule(char Tableau[TAILLE_MAX]);
void delete_duplicates(char *Argument);
void RemplirTableau(FILE* NomFichier, char Tableau[][TAILLE_MAX]);
char *strcase(const char *s,const char *find);

int length(char *string);
int optionW(char *string, char *stringRef, char *args);
int str_istr (const char *cs, const char *ct);
char* fctO(char *string, char *stringRef, char *args);
void set_la_color(unsigned short color);
