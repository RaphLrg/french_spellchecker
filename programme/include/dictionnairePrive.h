/**
 * \file dictionnairePrive.h
 * \brief Fonctions pour le type Dictionnaire.
 * \author Raphaël LARGEAU.
 * \version 1.3
 * \date 12/12/2021
 *
 * Description des fonctions à utiliser pour manipuler le type Dictionnaire.
 *
 */

#ifndef __DICTIONNAIRE_PRIVE__
#define __DICTIONNAIRE_PRIVE__

//Encapsulation
D_Dictionnaire D_obtenirFrere(D_Dictionnaire dico);
D_Dictionnaire D_obtenirFils(D_Dictionnaire dico);
char D_obtenirLettre(D_Dictionnaire dico);
unsigned int D_obtenirFinDeMotValide(D_Dictionnaire dico);
void D_fixerFils(D_Dictionnaire dico, D_Dictionnaire filsDico);
void D_fixerFrere(D_Dictionnaire dico, D_Dictionnaire frereDico);
void D_fixerLettre(D_Dictionnaire dico, char lettreDico);
void D_fixerFinDeMotValide(D_Dictionnaire dico, unsigned int finDeMotValideDico);

//Initialisation, affectation et libération mémoire
D_Dictionnaire D_creerNoeud(char lettre);

//Remplir le dictionnaire
D_Dictionnaire D_ajouterUneLettre(D_Dictionnaire *pdico, char lettre);

#endif