/**
 * \file correcteurorthographique.h
 * \author Tristan LOUKIANENKO.
 * \brief Développement de CO_CorrecteurOrthographique
 * \version 1.2
 * \date 2021-12-28
 * 
 * 
*/
#ifndef __CORRECTEUR_ORTHOGRAPHIQUE__
#define __CORRECTEUR_ORTHOGRAPHIQUE__

#include "file.h"
#include "dictionnaire.h"

/**
 *\struct C_Correction
 *\brief structure regroupant toutes les corrections pour un seul mot
 *
*/
typedef struct C_Correction{
    char *motACorriger;         /*! le mot que l'on cherche */
    F_File fileDesMotsCorriges; /*! file contenant les corrections du mot de type *char */
    unsigned int nbCorrections; /*! nombre de corrections stockées dans la file */
}C_Correction;

/**
 *\struct CO_CorrecteurOrthographique
 *\brief structure regroupant un dictionnaire de référence, une file de mots à corriger et une file de corrections pour chaques mots à corriger
 *
*/
typedef struct CO_CorrecteurOrthographique{
    D_Dictionnaire dico;        /*! dictionnaire de référence pour notre correction */
    F_File fileACorriger;       /*! file des mots de carriger de type *char */
    F_File fileDesCorrections;  /*! file des corrections de type C_Correction */
}CO_CorrecteurOrthographique;   /*!  */


//Initialisation
C_Correction *C_correction(char *monMot, unsigned int nbCorrections);
CO_CorrecteurOrthographique *CO_correcteur(D_Dictionnaire dico, F_File fileACorriger);

//Encapsulation
void C_fixerFileDesMotsCorriges(C_Correction *pCorrection, F_File fileSource);
F_File C_obtenirFilesDesMotsCorriges(C_Correction maCorrection);
char *C_obtenirMotACorriger(C_Correction maCorrection);
unsigned int C_obtenirNbCorrections(C_Correction maCorrection);

F_File CO_obtenirFileDesCorrections(CO_CorrecteurOrthographique correcteur);

//Stratégies
F_File CO_strategieRemplacerLettre(D_Dictionnaire dico, char *monMot);
F_File CO_strategieInverserLettre(D_Dictionnaire dico, char *monMot);
F_File CO_strategieDecomposer(D_Dictionnaire dico, char *monMot);
F_File CO_strategieSupprimerLettre(D_Dictionnaire dico, char *monMot);
F_File CO_strategieInsererLettre(D_Dictionnaire dico, char *monMot);
void CO_decomposerMotEnDeux(char *mot, unsigned int p, char *motg, char *motd);

//Correction d'une chaîne de mots
void CO_corrigerUneChaine(CO_CorrecteurOrthographique *pCorrecteur);

//Affichage
void CO_afficherCorrection(D_Dictionnaire dicoSource);
void CO_afficherMot(C_Correction correction, D_Dictionnaire dico, unsigned int numeroDeLACorrection);

F_File CO_entreeStandardVersFile(void);

#endif
