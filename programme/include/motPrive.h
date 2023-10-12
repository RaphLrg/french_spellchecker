/**
 * \file motPrive.h
 * \author Clément OBLED.
 * \brief Fonctions de Mot.
 * \version 1.2
 * \date 2021-12-28
 * 
 * 
 */

#ifndef __MOT_PRIVE__
#define __MOT_PRIVE__

unsigned int M_estUneMaj(char);
char M_majEnMin(char);
char M_passerSansAccent(char);
void M_motFinal(char*);
void M_supprimerIemeLettre(char*,unsigned int);

#endif