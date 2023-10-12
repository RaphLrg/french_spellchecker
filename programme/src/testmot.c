/**
 * \file testmot.c
 * \author IJLAL ROCHAIDA.
 * \brief Développement des tests unitaires de Mot.
 * \version 1.2
 * \date 2021-12-28
 *
 *
 */

#include <CUnit/Basic.h>
#include <string.h>
#include <stdlib.h>
#include "mot.h"
#include "motPrive.h"

/**
 * \fn void test_M_estUnCaractereValide(void)
 * \brief Tests unitaires de la fonction M_estUnCaractereValide.
 *
 */
void test_M_estUnCaractereValide(void)
{
	CU_ASSERT_FALSE(M_estUnCaractereValide('?'));
	CU_ASSERT_TRUE(M_estUnCaractereValide('e'));
}

/**
 * \fn void test_M_estMot(void)
 * \brief Tests unitaires de la fonction M_estMot.
 *
 */
void test_M_estMot(void)
{
	CU_ASSERT_FALSE(M_estMot("te?t"));
	CU_ASSERT_TRUE(M_estMot("test"));
}

/**
 * \fn void test_M_iemeCaractere(void)
 * \brief Tests unitaires de la fonction M_iemeCaractere.
 *
 */
void test_M_iemeCaractere(void)
{
	CU_ASSERT_EQUAL(M_iemeCaractere("test", 0), 't');
}

/**
 * \fn void test_M_longueur(void)
 * \brief Tests unitaires de la fonction M_longueur.
 *
 */
void test_M_longueur(void)
{
	CU_ASSERT_EQUAL(M_longueur("test"), 4);
}

/**
 * \fn void test_M_longueurCDC(void)
 * \brief Tests unitaires de la fonction M_longueurCDC.
 *
 */
void test_M_longueurCDC(void)
{
	CU_ASSERT_EQUAL(M_longueurCDC("test"), 4);
}

/**
 * \fn void test_M_estUneMaj(void)
 * \brief Tests unitaires de la fonction M_estUneMaj.
 *
 */
void test_M_estUneMaj(void)
{

	CU_ASSERT_TRUE(M_estUnCaractereValide('e'));
	CU_ASSERT_FALSE(M_estUnCaractereValide('E'));
}

/**
 * \fn void test_M_majEnMin(void)
 * \brief Tests unitaires de la fonction M_majEnMin.
 *
 */
void test_M_majEnMin(void)
{
	CU_ASSERT_TRUE(M_majEnMin('A') == 'a');
}

/**
 * \fn void test_M_supprimerIemeLettre(void)
 * \brief Tests unitaires de la fonction M_supprimerIemeLettre.
 *
 */
void test_M_supprimerIemeLettre(void)
{
	char *resultatObtenu = (char *)malloc(255 * sizeof(char));
	strcpy(resultatObtenu, "test");
	M_supprimerIemeLettre(resultatObtenu, 1);
	CU_ASSERT_STRING_EQUAL(resultatObtenu, "tst");
	free(resultatObtenu);
}

/**
 * \fn void test_M_ord(void)
 * \brief Tests unitaires de la fonction M_ord.
 *
 */
void test_M_ord(void)
{
	CU_ASSERT_EQUAL(M_ord('a'), (int)'a');
}

/**
 * \fn void test_M_chr(void)
 * \brief Tests unitaires de la fonction M_chr.
 *
 */
void test_M_chr(void)
{
	CU_ASSERT_EQUAL(M_chr(127), (char)127);
}

/**
 * \fn void test_M_motvide(void)
 * \brief Tests unitaires de la fonction M_motVide.
 *
 */
void test_M_motvide(void)
{
	CU_ASSERT_PTR_NULL(M_motVide("test"));
}

/**
 * \fn void test_M_creerMot(void){
 * \brief Tests unitaires de la fonction M_creerMot.
 *
 */
void test_M_creerMot(void)
{
	char *monMot = M_motVide();
	monMot = M_creerMot("azertyuiop");
	CU_ASSERT_STRING_EQUAL(monMot, "azertyuiop");
	free(monMot);
	monMot = M_creerMot("façon");
	CU_ASSERT_PTR_NOT_NULL(monMot);
	if (monMot != NULL)
	{
		CU_ASSERT_STRING_EQUAL(monMot, "facon");
		free(monMot);
	}
	monMot = M_creerMot("aéïRZà");
	CU_ASSERT_PTR_NOT_NULL(monMot);
	if (monMot != NULL)
	{
		CU_ASSERT_STRING_EQUAL(monMot, "aeirza");
		free(monMot);
	}
	monMot = M_creerMot("MARCHE");
	CU_ASSERT_PTR_NOT_NULL(monMot);
	if (monMot != NULL)
	{
		CU_ASSERT_STRING_EQUAL(monMot, "marche");
		free(monMot);
	}
}