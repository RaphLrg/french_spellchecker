/**
 * \file correcteurorthographiquePrive.h
 * \author Tristan LOUKIANENKO.
 * \brief Développement de CO_CorrecteurOrthographique
 * \version 1.2
 * \date 2021-12-28
 * 
 * 
*/
#ifndef __CORRECTEUR_ORTHOGRAPHIQUE_PRIVE__
#define __CORRECTEUR_ORTHOGRAPHIQUE_PRIVE__

//Transformations des mots
void CO_insererLettre(char *mot, unsigned int p, char e);
void CO_inverserDeuxLettresConsecutives(char *mot, unsigned int p);
void CO_remplacerLettre(char *mot, unsigned int p, char e);
void CO_supprimerLettre(char *mot, unsigned int p);

//Correction d'un mot
F_File CO_corrigerUnMot(D_Dictionnaire dico, char *monMot);

//Encapsulation
void C_fixerNbCorrections(C_Correction *pCorrection, unsigned int nbSource);
void C_fixerMotACorriger(C_Correction *pCorrection, char *motSource);

void CO_fixerDico(CO_CorrecteurOrthographique *pCorrecteur, D_Dictionnaire dicoSource);
void CO_fixerFileACorriger(CO_CorrecteurOrthographique *pCorrecteur, F_File fileSource);
F_File CO_obtenirFileACorriger(CO_CorrecteurOrthographique correcteur);
void CO_fixerFileDesCorrections(CO_CorrecteurOrthographique *pCorrecteur, F_File fileSource);
D_Dictionnaire CO_obtenirDico(CO_CorrecteurOrthographique correcteur);

#endif