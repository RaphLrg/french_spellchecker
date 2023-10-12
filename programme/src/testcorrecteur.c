/**
 * \file testcorrecteur.c
 * \author Ijlal ROCHAIDA.
 * \brief Développement des Tests unitaires de CO_CorrecteurOrthographique et de C_Correction. 
 * \version 1.2
 * \date 2021-12-28
 * 
 * 
 */

#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include "testcorrecteur.h"
#include "correcteurorthographique.h"
#include "correcteurorthographiquePrive.h"
#include "dictionnaire.h"
#include "mot.h"
#define TRUE 1
#define FALSE 0

/**
 * \file testcorrecteurorthographique.c
 * \brief Programme de tests unitaires de CorrecteurOrthographique.
 * \author
 * \version 1.1
 * \date 12/12/2021
 *
 */

/**
 * \fn void test_CO_insererLettre(void)
 * \brief Tests unitaires de la procédure CO_insererLettre.
 * 
 */
void test_CO_insererLettre(void)
{
	char *resultatObtenu = M_creerMot("exemle");
	CO_insererLettre(resultatObtenu, 4, 'p');
	CU_ASSERT_STRING_EQUAL(resultatObtenu, "exemple");
	free(resultatObtenu);
}

/**
 * \fn void test_CO_inverserDeuxLettresConsecutives(void)
 * \brief Tests unitaires de la procédure CO_inverserDeuxLettresConsecutives.
 * 
 */
void test_CO_inverserDeuxLettresConsecutives(void)
{
	char *resultatObtenu = M_creerMot("exemple");
	CO_inverserDeuxLettresConsecutives(resultatObtenu, 3);
	CU_ASSERT_STRING_EQUAL(resultatObtenu, "exepmle");
	free(resultatObtenu);
}

/**
 * \fn void test_CO_remplacerLettre(void)
 * \brief Tests unitaires de la procédure CO_remplacerLettre.
 * 
 */
void test_CO_remplacerLettre(void)
{
	char *resultatObtenu = M_creerMot("exemdle");
	CO_remplacerLettre(resultatObtenu, 4, 'p');
	CU_ASSERT_STRING_EQUAL(resultatObtenu, "exemple");
	free(resultatObtenu);
}

/**
 * \fn void test_CO_supprimerLettre(void)
 * \brief Tests unitaires de la procédure CO_supprimerLettre.
 * 
 */
void test_CO_supprimerLettre(void)
{
	char *resultatObtenu = M_creerMot("exemaple");
	CO_supprimerLettre(resultatObtenu, 4);
	CU_ASSERT_STRING_EQUAL(resultatObtenu, "exemple");
	free(resultatObtenu);
}

/**
 * \fn void test_CO_decomposerMotEnDeux(void)
 * \brief Tests unitaires de la procédure CO_decomposerMotEnDeux.
 * 
 */
void test_CO_decomposerMotEnDeux(void)
{
	char *resultatObtenu1 = (char *)malloc(255 * sizeof(char));
	char *resultatObtenu2 = (char *)malloc(255 * sizeof(char));
	CO_decomposerMotEnDeux("monexemple", 3, resultatObtenu1, resultatObtenu2);
	CU_ASSERT_STRING_EQUAL(resultatObtenu1, "mon");
	CU_ASSERT_STRING_EQUAL(resultatObtenu2, "exemple");
	CO_decomposerMotEnDeux(resultatObtenu2, 3, resultatObtenu1, resultatObtenu2);
	CU_ASSERT_STRING_EQUAL(resultatObtenu1, "exe");
	CU_ASSERT_STRING_EQUAL(resultatObtenu2, "mple");
	free(resultatObtenu1);
	free(resultatObtenu2);
}

/**
 * \fn void test_C_correction(void)
 * \brief Tests unitaires de la fonction C_correction.
 * 
 */
void test_C_correction(void)
{
	C_Correction *pCorrection = C_correction("motacorriger", 12);
	CU_ASSERT_PTR_NULL(pCorrection->fileDesMotsCorriges);
	CU_ASSERT_EQUAL(pCorrection->nbCorrections, 12);
	CU_ASSERT_STRING_EQUAL(pCorrection->motACorriger, "motacorriger");
	free(pCorrection);
	pCorrection = C_correction("mot", 0);
	CU_ASSERT_PTR_NULL(pCorrection->fileDesMotsCorriges);
	CU_ASSERT_EQUAL(pCorrection->nbCorrections, 0);
	CU_ASSERT_STRING_EQUAL(pCorrection->motACorriger, "mot");
	free(pCorrection);
}

/**
 * \fn void test_C_fixerNbCorrections(void)
 * \brief Tests unitaires de la procédure C_fixerNbCorrections.
 * 
 */
void test_C_fixerNbCorrections(void)
{
	C_Correction *pCorrection = C_correction("mot", 0);
	C_fixerNbCorrections(pCorrection, 10);
	CU_ASSERT_EQUAL(pCorrection->nbCorrections, 10);
	free(pCorrection);
}

/**
 * \fn void test_C_obtenirNbCorrections(void)
 * \brief Tests unitaires de la fonction C_obtenirNbCorrections.
 * 
 */
void test_C_obtenirNbCorrections(void)
{
	C_Correction *pCorrection = C_correction("mot", 0);
	CU_ASSERT_EQUAL(C_obtenirNbCorrections(*pCorrection), 0);
	C_fixerNbCorrections(pCorrection, 10);
	CU_ASSERT_EQUAL(C_obtenirNbCorrections(*pCorrection), 10);
	free(pCorrection);
}

/**
 * \fn void test_C_fixerFileDesMotsCorriges(void)
 * \brief Tests unitaires de la procédure C_fixerFileDesMotsCorriges.
 * 
 */
void test_C_fixerFileDesMotsCorriges(void)
{
	C_Correction *pCorrection = C_correction("mot", 0);
	CU_ASSERT_PTR_NULL(pCorrection->fileDesMotsCorriges);
	F_File maFile = NULL;
	char *mot1 = M_creerMot("abc");
	char *mot2 = M_creerMot("def");
	F_enfiler(&maFile, (void **)&mot1, 255 * sizeof(char));
	F_enfiler(&maFile, (void **)&mot2, 255 * sizeof(char));
	C_fixerFileDesMotsCorriges(pCorrection, maFile);
	CU_ASSERT_PTR_EQUAL(pCorrection->fileDesMotsCorriges, maFile);
	CU_ASSERT_PTR_EQUAL(pCorrection->fileDesMotsCorriges->fileSuivante, maFile->fileSuivante);
	CU_ASSERT_STRING_EQUAL(maFile->fileSuivante->element, "def");
	CU_ASSERT_STRING_EQUAL(maFile->element, "abc");
	free(maFile->fileSuivante->element);
	free(maFile->fileSuivante);
	free(maFile->element);
	free(maFile);
	free(pCorrection);
}

/**
 * \fn void test_C_obtenirFilesDesMotsCorriges(void)
 * \brief Tests unitaires de la fonction C_obtenirFilesDesMotsCorriges.
 * 
 */
void test_C_obtenirFilesDesMotsCorriges(void)
{
	C_Correction *pCorrection = C_correction("mot", 0);
	F_File maFile = NULL;
	char *mot1 = M_creerMot("abc");
	char *mot2 = M_creerMot("def");
	F_enfiler(&maFile, (void **)&mot1, 255 * sizeof(char));
	F_enfiler(&maFile, (void **)&mot2, 255 * sizeof(char));
	C_fixerFileDesMotsCorriges(pCorrection, maFile);
	F_File fileObtenue = C_obtenirFilesDesMotsCorriges(*pCorrection);
	CU_ASSERT_PTR_EQUAL(fileObtenue, maFile);
	char *nouveauMot1 = F_obtenirElement(fileObtenue, 255 * sizeof(char));
	CU_ASSERT_STRING_EQUAL(nouveauMot1, "abc");
	F_defiler(&fileObtenue);
	free(nouveauMot1);
	char *nouveauMot2 = F_obtenirElement(fileObtenue, 255 * sizeof(char));
	CU_ASSERT_STRING_EQUAL(nouveauMot2, "def");
	F_defiler(&fileObtenue);
	free(nouveauMot2);
	CU_ASSERT_PTR_NULL(fileObtenue);
	free(pCorrection);
}

/**
 * \fn void test_C_fixerMotACorriger(void)
 * \brief Tests unitaires de la procédure C_fixerMotACorriger.
 * 
 */
void test_C_fixerMotACorriger(void)
{
	C_Correction *pCorrection = C_correction("mot", 0);
	CU_ASSERT_STRING_EQUAL(pCorrection->motACorriger, "mot");
	C_fixerMotACorriger(pCorrection, "nouveau-mot");
	CU_ASSERT_STRING_EQUAL(pCorrection->motACorriger, "nouveau-mot");
	free(pCorrection);
}

/**
 * \fn void test_C_obtenirMotACorriger(void)
 * \brief Tests unitaires de la fonction C_obtenirMotACorriger.
 * 
 */
void test_C_obtenirMotACorriger(void)
{
	C_Correction *pCorrection = C_correction("mot", 0);
	CU_ASSERT_STRING_EQUAL(C_obtenirMotACorriger(*pCorrection), "mot");
	C_fixerMotACorriger(pCorrection, "nouveau-mot");
	CU_ASSERT_STRING_EQUAL(C_obtenirMotACorriger(*pCorrection), "nouveau-mot");
	free(pCorrection);
}

/**
 * \fn void test_CO_fixerDico(void)
 * \brief Tests unitaires de la procédure CO_fixerDico. 
 * 
 */
void test_CO_fixerDico(void)
{
	CO_CorrecteurOrthographique correcteur;
	D_Dictionnaire dico = D_dictionnaire();
	D_ajouterUnMot(&dico, "blabla");
	CO_fixerDico(&correcteur, dico);
	CU_ASSERT_PTR_EQUAL(correcteur.dico, dico);
	D_liberer(&dico);
}

/**
 * \fn void test_CO_obtenirDico(void)
 * \brief Tests unitaires de la fonction CO_obtenirDico.
 * 
 */
void test_CO_obtenirDico(void)
{
	CO_CorrecteurOrthographique correcteur;
	D_Dictionnaire dico = D_dictionnaire();
	D_ajouterUnMot(&dico, "blabla");
	CO_fixerDico(&correcteur, dico);
	CU_ASSERT_PTR_EQUAL(CO_obtenirDico(correcteur), dico);
	D_liberer(&dico);
}

/**
 * \fn void test_CO_fixerFileACorriger(void)
 * \brief Tests unitaires de la procédure CO_fixerFileACorriger.
 * 
 */
void test_CO_fixerFileACorriger(void)
{
	CO_CorrecteurOrthographique correcteur;
	F_File maFile = F_file();
	char *mot1 = (char *)malloc(255 * sizeof(char));
	strcpy(mot1, "mot1");
	F_enfiler(&maFile, (void **)&mot1, 255 * sizeof(char));
	CO_fixerFileACorriger(&correcteur, maFile);
	CU_ASSERT_PTR_EQUAL(correcteur.fileACorriger, maFile);
	char *motObtenu = F_obtenirElement(correcteur.fileACorriger, 255 * sizeof(char));
	CU_ASSERT_STRING_EQUAL(motObtenu, "mot1");
	free(motObtenu);
	free(maFile);
}

/**
 * \fn void test_CO_obtenirFileACorriger(void)
 * \brief Tests unitaires de la fonction CO_obtenirFileACorriger.
 * 
 */
void test_CO_obtenirFileACorriger(void)
{
	CO_CorrecteurOrthographique correcteur;
	F_File maFile = F_file();
	char *mot1 = (char *)malloc(255 * sizeof(char));
	strcpy(mot1, "mot1");
	F_enfiler(&maFile, (void **)&mot1, 255 * sizeof(char));
	CO_fixerFileACorriger(&correcteur, maFile);
	CU_ASSERT_PTR_EQUAL(CO_obtenirFileACorriger(correcteur), maFile);
	char *motObtenu = F_obtenirElement(CO_obtenirFileACorriger(correcteur), 255 * sizeof(char));
	CU_ASSERT_STRING_EQUAL(motObtenu, "mot1");
	free(motObtenu);
	free(maFile);
}

/**
 * \fn void test_CO_fixerFileDesCorrections(void)
 * \brief Tests unitaires de la procédure CO_fixerFileDesCorrections.
 * 
 */
void test_CO_fixerFileDesCorrections(void)
{
	char *monMot = (char*)malloc(255*sizeof(char));
	strcpy(monMot, "test");
	C_Correction *pCorrection1 = C_correction(monMot, 1); 
	F_File maFile = F_file();
	F_enfiler(&maFile, (void**)&pCorrection1, sizeof(C_Correction));
	F_File maFileACorriger = F_file();
	D_Dictionnaire dico = D_dictionnaire();
	CO_CorrecteurOrthographique *pCorrecteur = CO_correcteur(dico, maFileACorriger);
	CO_fixerFileDesCorrections(pCorrecteur, maFile);
	CU_ASSERT_PTR_EQUAL(pCorrecteur->fileDesCorrections, maFile);
	F_File maFileObtenue = pCorrecteur->fileDesCorrections;
	C_Correction *pCorrectionObtenu = F_obtenirElement(maFileObtenue, sizeof(C_Correction));
	F_defiler(&maFileObtenue);
	free(pCorrectionObtenu);
	free(pCorrecteur);
	free(monMot);
}

/**
 * \fn void test_CO_obtenirFileDesCorrections(void)
 * \brief Tests unitaires de la fonction CO_obtenirFileDesCorrections.
 * 
 */
void test_CO_obtenirFileDesCorrections(void)
{
	char *monMot = (char*)malloc(255*sizeof(char));
	strcpy(monMot, "test");
	C_Correction *pCorrection1 = C_correction(monMot, 1); 
	F_File maFile = F_file();
	F_enfiler(&maFile, (void**)&pCorrection1, sizeof(C_Correction));
	F_File maFileACorriger = F_file();
	D_Dictionnaire dico = D_dictionnaire();
	CO_CorrecteurOrthographique *pCorrecteur = CO_correcteur(dico, maFileACorriger);
	CO_fixerFileDesCorrections(pCorrecteur, maFile);
	CU_ASSERT_PTR_EQUAL(pCorrecteur->fileDesCorrections, maFile);
	F_File maFileObtenue = CO_obtenirFileDesCorrections(*pCorrecteur);
	C_Correction *pCorrectionObtenu = F_obtenirElement(maFileObtenue, sizeof(C_Correction));
	F_defiler(&maFileObtenue);
	free(pCorrectionObtenu);
	free(pCorrecteur);
	free(monMot);
}

/**
 * \fn D_Dictionnaire creerDicoTests(void)
 * \brief fonction qui crée un dictionnaire pour servir d'exemple.
 * 
 */
D_Dictionnaire creerDicoTests(void)
{
	D_Dictionnaire dico = D_dictionnaire();
	D_ajouterUnMot(&dico, "fete");
	D_ajouterUnMot(&dico, "ftee");
	D_ajouterUnMot(&dico, "efte");
	D_ajouterUnMot(&dico, "feter");
	D_ajouterUnMot(&dico, "feta");
	D_ajouterUnMot(&dico, "fet");
	D_ajouterUnMot(&dico, "fetes");
	D_ajouterUnMot(&dico, "feet");
	D_ajouterUnMot(&dico, "fe");
	D_ajouterUnMot(&dico, "te");
	D_ajouterUnMot(&dico, "f");
	D_ajouterUnMot(&dico, "ete");
	D_ajouterUnMot(&dico, "fele");
	D_ajouterUnMot(&dico, "tete");
	D_ajouterUnMot(&dico, "fele");
	D_ajouterUnMot(&dico, "fee");
	D_ajouterUnMot(&dico, "fte");
	D_ajouterUnMot(&dico, "fear");
	D_ajouterUnMot(&dico, "fatr");
	D_ajouterUnMot(&dico, "letr");
	D_ajouterUnMot(&dico, "arbre");
	D_ajouterUnMot(&dico, "arre");
	D_ajouterUnMot(&dico, "arb");
	D_ajouterUnMot(&dico, "re");
	D_ajouterUnMot(&dico, "marbre");
	D_ajouterUnMot(&dico, "arbres");
	D_ajouterUnMot(&dico, "arbra");
	return dico;
}

/**
 * \fn void test_CO_correcteur(void)
 * \brief Tests unitaires de la fonction CO_correcteur.
 * 
 */
void test_CO_correcteur(void)
{
	char *mot1 = (char *)malloc(255 * sizeof(char));
	char *mot2 = (char *)malloc(255 * sizeof(char));
	strcpy(mot1, "fete");
	strcpy(mot2, "arbre");
	F_File fileACorriger = F_file();
	F_enfiler(&fileACorriger, (void **)&mot1, 255 * sizeof(char));
	F_enfiler(&fileACorriger, (void **)&mot2, 255 * sizeof(char));
	D_Dictionnaire dico = creerDicoTests();
	CO_CorrecteurOrthographique *pCorrecteur = CO_correcteur(dico, fileACorriger);
	CU_ASSERT_PTR_EQUAL(CO_obtenirDico(*pCorrecteur), dico);
	F_File fileObtenue = CO_obtenirFileACorriger(*pCorrecteur);

	char *motObtenu = F_obtenirElement(fileObtenue, 255 * sizeof(char));
	CU_ASSERT_STRING_EQUAL(motObtenu, "fete");
	F_defiler(&fileObtenue);
	free(motObtenu);

	motObtenu = F_obtenirElement(fileObtenue, 255 * sizeof(char));
	CU_ASSERT_STRING_EQUAL(motObtenu, "arbre");
	F_defiler(&fileObtenue);
	free(motObtenu);

	D_liberer(&dico);

	free(pCorrecteur);
}

/**
 * \fn void test_CO_strategieRemplacerLettre(void)
 * \brief Tests unitaires de la fonction CO_strategieRemplacerLettre.
 * 
 */
void test_CO_strategieRemplacerLettre(void)
{
	char *monMot = "fete";
	D_Dictionnaire dico = creerDicoTests();
	F_File maFile = CO_strategieRemplacerLettre(dico, monMot);
	while (! F_estVide(maFile))
	{
		char *motFile = F_obtenirElement(maFile, 255 * sizeof(char));
		CU_ASSERT_EQUAL(M_longueur(monMot), M_longueur(motFile));
		CU_ASSERT_TRUE(D_motPresent(dico, motFile));
		free(motFile);
		F_defiler(&maFile);
	}
	D_liberer(&dico);
}

/**
 * \fn void test_CO_strategieInverserLettre(void)
 * \brief Tests unitaires de la fonction CO_strategieInverserLettre.
 * 
 */
void test_CO_strategieInverserLettre(void)
{
	char *monMot = "fete";
	D_Dictionnaire dico = creerDicoTests();
	F_File maFile = CO_strategieInverserLettre(dico, monMot);
	while (! F_estVide(maFile))
	{
		char *motFile = F_obtenirElement(maFile, 255 * sizeof(char));
		CU_ASSERT_EQUAL(M_longueur(monMot), M_longueur(motFile));
		CU_ASSERT_TRUE(D_motPresent(dico, motFile));
		free(motFile);
		F_defiler(&maFile);
	}
	D_liberer(&dico);
}

/**
 * \fn void test_CO_strategieDecomposer(void)
 * \brief Tests unitaires de la fonction CO_strategieDecomposer.
 * 
 */
void test_CO_strategieDecomposer(void)
{
	char *monMot = "fete";
	D_Dictionnaire dico = creerDicoTests();
	F_File maFile = CO_strategieDecomposer(dico, monMot);
	while (! F_estVide(maFile))
	{
		char *motFile = F_obtenirElement(maFile, 255 * sizeof(char));
		CU_ASSERT_TRUE(M_longueur(monMot) > M_longueur(motFile));
		CU_ASSERT_TRUE(D_motPresent(dico, motFile));
		free(motFile);
		F_defiler(&maFile);
	}
	printf("\n");
	D_liberer(&dico);
}

/**
 * \fn void test_CO_strategieSupprimerLettre(void)
 * \brief Tests unitaires de la fonction CO_strategieSupprimerLettre.
 * 
 */
void test_CO_strategieSupprimerLettre(void)
{
	char *monMot = "fete";
	D_Dictionnaire dico = creerDicoTests();
	F_File maFile = CO_strategieSupprimerLettre(dico, monMot);
	while (! F_estVide(maFile))
	{
		char *motFile = F_obtenirElement(maFile, 255 * sizeof(char));
		CU_ASSERT_TRUE(M_longueur(monMot) > M_longueur(motFile));
		CU_ASSERT_TRUE(D_motPresent(dico, motFile));
		free(motFile);
		F_defiler(&maFile);
	}
	D_liberer(&dico);
}

/**
 * \fn void test_CO_strategieInsererLettre(void).
 * \brief Tests unitaires de la fonction CO_strategieInsererLettre.
 * 
 */
void test_CO_strategieInsererLettre(void)
{
	char *monMot = "fete";
	D_Dictionnaire dico = creerDicoTests();
	F_File maFile = CO_strategieInsererLettre(dico, monMot);
	while (! F_estVide(maFile))
	{
		char *motFile = F_obtenirElement(maFile, 255 * sizeof(char));
		CU_ASSERT_TRUE(M_longueur(monMot) < M_longueur(motFile));
		CU_ASSERT_TRUE(D_motPresent(dico, motFile));
		free(motFile);
		F_defiler(&maFile);
	}
	D_liberer(&dico);
}

/**
 * \fn void test_CO_corrigerUnMot(void)
 * \brief Tests unitaires de la fonction CO_corrigerUnMot.
 * 
 */
void test_CO_corrigerUnMot(void)
{
	char *monMot = "fete";
	D_Dictionnaire dico = creerDicoTests();
	F_File maFile = CO_corrigerUnMot(dico, monMot);
	while (! F_estVide(maFile))
	{
		char *motFile = F_obtenirElement(maFile, 255 * sizeof(char));
		CU_ASSERT_TRUE(D_motPresent(dico, motFile));
		free(motFile);
		F_defiler(&maFile);
	}
	D_liberer(&dico);
}

/**
 * \fn void test_CO_corrigerUneChaine(void)
 * \brief Tests unitaires de la procédure CO_corrigerUneChaine.
 * 
 */
void test_CO_corrigerUneChaine(void)
{
	char *mot1 = (char *)malloc(255 * sizeof(char));
	char *mot2 = (char *)malloc(255 * sizeof(char));
	strcpy(mot1, "fete");
	strcpy(mot2, "arbre");
	F_File fileACorriger = F_file();
	F_enfiler(&fileACorriger, (void **)&mot1, 255 * sizeof(char));
	F_enfiler(&fileACorriger, (void **)&mot2, 255 * sizeof(char));
	D_Dictionnaire dico = creerDicoTests();
	CO_CorrecteurOrthographique *pCorrecteur = CO_correcteur(dico, fileACorriger);
	CO_corrigerUneChaine(pCorrecteur);
	D_Dictionnaire dicoDuCorrecteur = CO_obtenirDico(*pCorrecteur);
	F_File fileDesCorrectionsDuCorrecteur = CO_obtenirFileDesCorrections(*pCorrecteur);
	
	while (! F_estVide(fileDesCorrectionsDuCorrecteur))
	{
		C_Correction *pCorrection = F_obtenirElement(fileDesCorrectionsDuCorrecteur, sizeof(struct C_Correction));
		F_File fileDesMotCorriges = C_obtenirFilesDesMotsCorriges(*pCorrection);
		CU_ASSERT_TRUE(F_nbElements(fileDesMotCorriges) > 0);
		while (! F_estVide(fileDesMotCorriges))
		{
			char *motFile = F_obtenirElement(fileDesMotCorriges, 255 * sizeof(char));
			CU_ASSERT_TRUE(D_motPresent(dico, motFile));
			free(motFile);
			F_defiler(&fileDesMotCorriges);
		}
		free(C_obtenirMotACorriger(*pCorrection));
		free(pCorrection);
		F_defiler(&fileDesCorrectionsDuCorrecteur);
	}
	D_liberer(&dicoDuCorrecteur);
	free(pCorrecteur);
}