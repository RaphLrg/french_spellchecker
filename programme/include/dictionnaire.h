/**
 * \file dictionnaire.h
 * \brief Fonctions pour le type Dictionnaire.
 * \author Raphaël LARGEAU.
 * \version 1.3
 * \date 12/12/2021
 *
 * Description des fonctions à utiliser pour manipuler le type Dictionnaire.
 *
 */

#ifndef __DICTIONNAIRE__
#define __DICTIONNAIRE__


/**
 * \struct D_Dictionnaire
 * \brief Objet chaine de caractères.
 *
 * Dictionnaire représente un arbre n-aire sous forme d'un arbre binaire.
 * Cet arbre n-aire contient a chaque noeud un caractère et un booléen,
 * cela permet de caractériser un ensemble de mots.
 * 
 */ 
typedef struct D_Noeud *D_Dictionnaire;

/**
 * \struct D_Noeud
 * \brief Noeud d'un dictionnaire.
 *
 */ 
typedef struct D_Noeud
{
    D_Dictionnaire frere;     /*! L'attribut frere représente un objet d'un même noeud. */
    D_Dictionnaire fils;      /*! L'attribut fils représente un objet d'une branche. */
    char lettre;            /*! L'attribut lettre représente le caractère contenu dans le noeud. */
    int finDeMotValide;     /*! L'attribut finDeMotValide représente le booléen contenu dans le noeud (0=FALSE et 1=TRUE). */
}D_Noeud;

//Initialisation, affectation et libération mémoire
void D_liberer(D_Dictionnaire *dico);
D_Dictionnaire D_dictionnaire(void);

//Remplir le dictionnaire
void D_ajouterUnMot(D_Dictionnaire *pdico, char *monMot);

//Affichage dans le terminal d'un dictionnaire
//void D_afficher(D_Dictionnaire dico);

//Recherche dans le dictionnaire
unsigned int D_motPresent(D_Dictionnaire dico, char *mot);

//Sérialisation et dé-sérialisation
void D_serialiser(D_Dictionnaire dico, char *nomFichier);
D_Dictionnaire D_deserialiser(char *nomFichier);

//Procedure finale
void D_entrerUnDictionnaire(char *nomDico, char *nomFichier);

#endif