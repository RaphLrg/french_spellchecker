/**
 * \file testcorrecteur.h
 * \author Ijlal ROCHAIDA.
 * \brief Tests unitaires de CO_CorrecteurOrthographique et de C_Correction. 
 * \version 1.0
 * \date 2021-12-28
 * 
 */

#ifndef __TEST_CORRECTEUR__
#define __TEST_CORRECTEUR__
void test_CO_insererLettre (void);
void test_CO_inverserDeuxLettresConsecutives(void);
void test_CO_remplacerLettre(void);
void test_CO_supprimerLettre(void);
void test_CO_decomposerMotEnDeux(void);
void test_C_correction(void);
void test_C_fixerNbCorrections(void);
void test_C_obtenirNbCorrections(void);
void test_C_fixerFileDesMotsCorriges(void);
void test_C_obtenirFilesDesMotsCorriges(void);
void test_C_fixerMotACorriger(void);
void test_C_obtenirMotACorriger(void);
void test_CO_fixerDico(void);
void test_CO_obtenirDico(void);
void test_CO_fixerFileACorriger(void);
void test_CO_obtenirFileACorriger(void);
void test_CO_fixerFileDesCorrections(void);
void test_CO_obtenirFileDesCorrections(void);
void test_CO_correcteur(void);
void test_CO_strategieRemplacerLettre(void);
void test_CO_strategieInverserLettre(void);
void test_CO_strategieDecomposer(void);
void test_CO_strategieSupprimerLettre(void);
void test_CO_strategieInsererLettre(void);
void test_CO_corrigerUnMot(void);
void test_CO_corrigerUneChaine(void);

#endif