/**
 * \file mot.h
 * \author Clément OBLED.
 * \brief Fonctions de Mot.
 * \version 1.2
 * \date 2021-12-28
 * 
 * 
 */

#ifndef __MOT__
#define __MOT__

int M_ord(char c);
char M_chr(int chiffre);
char *M_motVide();
char M_iemeCaractere(char*, unsigned int);
unsigned int M_estUnCaractereValide(char);
unsigned int M_longueur(char*);
unsigned int M_longueurCDC(char*);
unsigned int M_estMot(char*);
unsigned int M_estUnAccent(char);
char *M_creerMot(char*);

#endif
