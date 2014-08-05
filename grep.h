#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define TAILLE_MAX 250

void FunctionGrep(char** Tableau,char * ChaineAChercher,int NombreDeLigne);
void TestArgument(char * Argument,char Tableau[][TAILLE_MAX],int j,int NombreDeCaractere,int nbFichier,char * nomFichier,char * ChaineAChercher);
int FunctionNbOccurence(char Tableau[][TAILLE_MAX],char * ChaineAChercher,int NombreDeLigne,char * Argument);
int FunctionArgA(char Tableau[][TAILLE_MAX],char * ChaineAChercher,int NombreDeLigne);
void TestArgumentA(char * Argument,char Tableau[][TAILLE_MAX],int i,int NombreDeCaractere,int nbFichier,char * nomFichier,char * ChaineAChercher,int NombreDeLigne);
void FunctionGrepWithArguments(char Tableau[][TAILLE_MAX],char * ChaineAChercher,int NombreDeLigne,char * Argument,char * nomFichier,int nbFichier,int NbLineAvantPremiereTrouvee,int * ArgNombre);
void afficherEnCouleur(char * ligne,char * chaineAChercher);

