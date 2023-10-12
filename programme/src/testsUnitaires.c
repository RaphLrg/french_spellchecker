/**
 * \file testsUnitaires.c
 * \author Raphaël LARGEAU.
 * \brief Fichier principal des tests unitaires. 
 * \version 3.2
 * \date 2021-12-28
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "testfile.h"
#include "testmot.h"
#include "testDictionnaire.h"
#include "testcorrecteur.h"

static int init_suite_success(void)
{
	return 0;
}

static int clean_suite_success(void)
{
	return 0;
}

/**
 * \fn int main(int argc , char** argv)
 * \brief Effectue tous les tests unitaires.
 * 
 * \param argc 
 * \param argv 
 * \return int 
 */
int main(int argc , char** argv)
{
	CU_pSuite pSuiteMot = NULL;
	CU_pSuite pSuiteCorrecteur = NULL;
	CU_pSuite pSuiteDictionnaire = NULL;
	/* initialisation du registre de tests */
	if (CUE_SUCCESS != CU_initialize_registry())
	return CU_get_error();

	/* ajout d’une suite de test */
	pSuiteMot = CU_add_suite("Tests boite noire de Mot", init_suite_success , clean_suite_success );
	if (NULL == pSuiteMot) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	pSuiteDictionnaire = CU_add_suite("Tests boite noire de Dictionnaire", init_suite_success , clean_suite_success );
	if (NULL == pSuiteDictionnaire) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	pSuiteCorrecteur = CU_add_suite("Tests boite noire de CorrecteurOrthographique", init_suite_success , clean_suite_success );
	if (NULL == pSuiteCorrecteur) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

 /* Ajout des tests `a la suite de tests boite noire */
	if (
		(NULL == CU_add_test(pSuiteMot, "Test de la fonction F_file", test_F_file))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction F_enfiler", test_F_enfiler))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction F_defiler", test_F_defiler))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction F_obtenirElement", test_F_obtenirElement))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction F_nbElement", test_F_nbElement))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction F_estVide", test_F_estVide))
	) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (
		(NULL == CU_add_test(pSuiteMot, "Test de la fonction M_estUnCaractereValide", test_M_estUnCaractereValide))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction M_estMot", test_M_estMot))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction M_iemeCaractere", test_M_iemeCaractere))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction M_longueur", test_M_longueur))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction M_longueurCDC", test_M_longueurCDC))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction M_estUneMaj", test_M_estUneMaj))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction M_majEnMin", test_M_majEnMin))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction M_supprimerIemeLettre", test_M_supprimerIemeLettre))
		|| (NULL == CU_add_test(pSuiteMot, "Test de la fonction M_ord", test_M_ord))
        || (NULL == CU_add_test(pSuiteMot, "Test de la fonction M_chr", test_M_chr))
        || (NULL == CU_add_test(pSuiteMot, "Test de la fonction M_motvide", test_M_motvide))
        || (NULL == CU_add_test(pSuiteMot, "Test de la fonction M_creerMot", test_M_creerMot))
	) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (
		(NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_dictionnaire", test_D_dictionnaire))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_creerNoeud", test_D_creerNoeud))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_liberer", test_D_liberer))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_ajouterUneLettre", test_D_ajouterUneLettre))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_fixerFils", test_D_fixerFils))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_fixerFrere", test_D_fixerFrere))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_fixerLettre", test_D_fixerLettre))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_obtenirFils", test_D_obtenirFils))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_obtenirFrere", test_D_obtenirFrere))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_obtenirLettre", test_D_obtenirLettre))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_obtenirFinDeMotValide", test_D_obtenirFinDeMotValide))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_fixerFinDeMotValide", test_D_fixerFinDeMotValide))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_motPresent", test_D_motPresent))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_ajouterUnMot", test_D_ajouterUnMot))
		|| (NULL == CU_add_test(pSuiteDictionnaire, "Test de la fonction D_serialiser et D_deserialiser", test_D_serialiser_et_D_deserialiser))
	) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (
		(NULL == CU_add_test(pSuiteCorrecteur, "Test de la procédure CO_insererLettre", test_CO_insererLettre))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la procédure CO_inverserDeuxLettresConsecutives", test_CO_inverserDeuxLettresConsecutives))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la procédure CO_remplacerLettre", test_CO_remplacerLettre))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la procédure CO_supprimerLettre", test_CO_supprimerLettre))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la procédure CO_decomposerMotEnDeux", test_CO_decomposerMotEnDeux))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction C_correction", test_C_correction))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la procédure C_fixerNbCorrections", test_C_fixerNbCorrections))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction C_obtenirNbCorrections", test_C_obtenirNbCorrections))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la procédure C_fixerFileDesMotsCorriges", test_C_fixerFileDesMotsCorriges))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction C_obtenirFilesDesMotsCorriges", test_C_obtenirFilesDesMotsCorriges))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la procédure C_fixerMotACorriger", test_C_fixerMotACorriger))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction C_obtenirMotACorriger", test_C_obtenirMotACorriger))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la procédure CO_fixerDico", test_CO_fixerDico))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction CO_obtenirDico", test_CO_obtenirDico))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la procédure CO_fixerFileACorriger", test_CO_fixerFileACorriger))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction CO_obtenirFileACorriger", test_CO_obtenirFileACorriger))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la procédure CO_fixerFileDesCorrections", test_CO_fixerFileDesCorrections))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction CO_obtenirFileDesCorrections", test_CO_obtenirFileDesCorrections))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction CO_correcteur", test_CO_correcteur))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction CO_strategieRemplacerLettre", test_CO_strategieRemplacerLettre))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction CO_strategieInverserLettre", test_CO_strategieInverserLettre))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction CO_strategieDecomposer", test_CO_strategieDecomposer))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction CO_strategieSupprimerLettre", test_CO_strategieSupprimerLettre))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction CO_strategieInsererLettre", test_CO_strategieInsererLettre))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la fonction CO_corrigerUnMot", test_CO_corrigerUnMot))
		|| (NULL == CU_add_test(pSuiteCorrecteur, "Test de la procédure CO_corrigerUneChaine", test_CO_corrigerUneChaine))
	) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


/* Lancement des tests */
CU_basic_set_mode(CU_BRM_VERBOSE);
CU_basic_run_tests();
printf("\n");
CU_basic_show_failures(CU_get_failure_list());
printf("\n\n");

/* Nettoyage du registre */
CU_cleanup_registry();
return CU_get_error();
}