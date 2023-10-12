/**
 * \file testDictionnaire.c
 * \author Clément OBLED.
 * \brief Développement des tests unitaires de D_Dictionnaire. 
 * \version 0.1
 * \date 2021-12-28
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "dictionnaire.h"
#include "dictionnairePrive.h"
#include <CUnit/Basic.h>
#define TRUE 1
#define FALSE 0

/**
 * \fn void test_D_dictionnaire(void)
 * \brief Tests unitaires de la fonction D_dictionnaire.
 * 
 */
void test_D_dictionnaire(void)
{
	D_Dictionnaire dico = D_dictionnaire();
	CU_ASSERT_PTR_NULL(dico);
}

/**
 * \fn void test_D_creerNoeud(void)
 * \brief Tests unitaires de la fonction D_creerNoeud.
 * 
 */
void test_D_creerNoeud(void)
{
	D_Dictionnaire dico = (D_Dictionnaire)malloc(sizeof(struct D_Noeud));
	dico->lettre = 'a';
	dico->finDeMotValide = 0;
	dico->frere = NULL;
	dico->fils = NULL;
	D_Dictionnaire dicoTemoin = D_creerNoeud('a');
	CU_ASSERT_EQUAL(D_obtenirLettre(dicoTemoin), D_obtenirLettre(dico));
	CU_ASSERT_EQUAL(D_obtenirFinDeMotValide(dicoTemoin), D_obtenirFinDeMotValide(dico));
	CU_ASSERT_PTR_EQUAL(D_obtenirFrere(dicoTemoin), D_obtenirFrere(dico));
	CU_ASSERT_PTR_EQUAL(D_obtenirFils(dicoTemoin), D_obtenirFils(dico));
	D_liberer(&dico);
	D_liberer(&dicoTemoin);
}

/**
 * \fn void test_D_liberer(void)
 * \brief Tests unitaires de la procédure D_liberer.
 * 
 */
void test_D_liberer(void)
{
	D_Dictionnaire dico = D_creerNoeud('a');
	dico->frere = D_creerNoeud('b');
	dico->fils = D_creerNoeud('c');
	D_liberer(&dico);
	CU_ASSERT_PTR_NULL(dico);
}

/**
 * \fn void test_D_ajouterUneLettre(void)
 * \brief Tests unitaires de la fonction D_ajouterUneLettre.
 * 
 */
void test_D_ajouterUneLettre(void)
{
	D_Dictionnaire dico = D_dictionnaire();
	D_Dictionnaire dicoTheorique = D_ajouterUneLettre(&dico, 'm');
	CU_ASSERT_PTR_EQUAL(dico, dicoTheorique);
	CU_ASSERT_TRUE(D_obtenirLettre(dico) == 'm');
	D_Dictionnaire frereTheorique = D_ajouterUneLettre(&dico, 'a');
	CU_ASSERT_PTR_EQUAL(D_obtenirFrere(dico), frereTheorique);
	CU_ASSERT_TRUE(D_obtenirLettre(D_obtenirFrere(dico)) == 'a');
	D_Dictionnaire frereDufrereTheorique = D_ajouterUneLettre(&dico, 'd');
	CU_ASSERT_PTR_EQUAL(D_obtenirFrere(D_obtenirFrere(dico)), frereDufrereTheorique);
	CU_ASSERT_TRUE(D_obtenirLettre(D_obtenirFrere(D_obtenirFrere(dico))) == 'd');
	D_liberer(&dico);
}

/**
 * \fn void test_D_fixerFils(void)
 * \brief Tests unitaires de la procédure D_fixerFils.
 * 
 */
void test_D_fixerFils(void)
{
	D_Dictionnaire dico = D_creerNoeud('a');
	D_Dictionnaire fils = D_creerNoeud('s');
	D_fixerFils(dico, fils);
	CU_ASSERT_TRUE(dico->fils == fils);
	D_liberer(&dico);
}

/**
 * \fn void test_D_fixerFrere(void)
 * \brief Tests unitaires de la procédure D_fixerFrere.
 * 
 */
void test_D_fixerFrere(void)
{
	D_Dictionnaire dico = D_creerNoeud('a');
	D_Dictionnaire frere = D_creerNoeud('b');
	D_fixerFrere(dico, frere);
	CU_ASSERT_TRUE(dico->frere == frere);
	D_liberer(&dico);
}

/**
 * \fn void test_D_fixerLettre(void)
 * \brief Tests unitaires de la procédure D_fixerLettre.
 * 
 */
void test_D_fixerLettre(void)
{
	D_Dictionnaire dico = D_creerNoeud('a');
	D_fixerLettre(dico, 'b');
	CU_ASSERT_TRUE('b' == dico->lettre);
	D_liberer(&dico);
}

/**
 * \fn void test_D_obtenirFils(void)
 * \brief Tests unitaires de la fonction D_obtenirFils.
 * 
 */
void test_D_obtenirFils(void)
{
	D_Dictionnaire dico = D_creerNoeud('a');
	D_fixerFils(dico, D_creerNoeud('s'));
	CU_ASSERT_TRUE(dico->fils == D_obtenirFils(dico));
	D_liberer(&dico);
}

/**
 * \fn void test_D_obtenirFrere(void)
 * \brief Tests unitaires de la fonction D_obtenirFrere.
 * 
 */
void test_D_obtenirFrere(void)
{
	D_Dictionnaire dico = D_creerNoeud('a');
	D_fixerFrere(dico, D_creerNoeud('b'));
	CU_ASSERT_TRUE(dico->frere == D_obtenirFrere(dico));
	D_liberer(&dico);
}

/**
 * \fn void test_D_obtenirLettre(void)
 * \brief Tests unitaires de la fonction D_obtenirLettre.
 * 
 */
void test_D_obtenirLettre(void)
{
	D_Dictionnaire dico = D_creerNoeud('a');
	CU_ASSERT_TRUE('a' == D_obtenirLettre(dico));
	D_liberer(&dico);
}

/**
 * \fn void test_D_obtenirFinDeMotValide(void)
 * \brief Tests unitaires de la fonction D_obtenirFinDeMotValide.
 * 
 */
void test_D_obtenirFinDeMotValide(void)
{
	D_Dictionnaire dico = D_creerNoeud('a');
	CU_ASSERT_FALSE(D_obtenirFinDeMotValide(dico));
	dico->finDeMotValide = TRUE;
	CU_ASSERT_TRUE(D_obtenirFinDeMotValide(dico));
	D_liberer(&dico);
}

/**
 * \fn void test_D_fixerFinDeMotValide(void)
 * \brief Tests unitaires de la procédure D_fixerFinDeMotValide.
 * 
 */
void test_D_fixerFinDeMotValide(void)
{
	D_Dictionnaire dico = D_creerNoeud('a');
	CU_ASSERT_FALSE(D_obtenirFinDeMotValide(dico));
	D_fixerFinDeMotValide(dico, 1);
	CU_ASSERT_TRUE(D_obtenirFinDeMotValide(dico));
	D_liberer(&dico);
}

/**
 * \fn void test_D_ajouterUnMot(void)
 * \brief Tests unitaires de la procédure D_ajouterUnMot.
 * 
 */
void test_D_ajouterUnMot(void)
{
	D_Dictionnaire dico = D_dictionnaire();
	D_ajouterUnMot(&dico, "mot");
	D_ajouterUnMot(&dico, "chat");
	CU_ASSERT_EQUAL(D_obtenirLettre(dico), 'm');
	CU_ASSERT_FALSE(D_obtenirFinDeMotValide(dico));
	CU_ASSERT_EQUAL(D_obtenirLettre(D_obtenirFils(dico)), 'o');
	CU_ASSERT_FALSE(D_obtenirFinDeMotValide(D_obtenirFils(dico)));
	CU_ASSERT_EQUAL(D_obtenirLettre(D_obtenirFils(D_obtenirFils(dico))), 't');
	CU_ASSERT_TRUE(D_obtenirFinDeMotValide(D_obtenirFils(D_obtenirFils(dico))));

	CU_ASSERT_EQUAL(D_obtenirLettre(D_obtenirFrere(dico)), 'c');
	CU_ASSERT_FALSE(D_obtenirFinDeMotValide(D_obtenirFrere(dico)));
	CU_ASSERT_EQUAL(D_obtenirLettre(D_obtenirFils(D_obtenirFrere(dico))), 'h');
	CU_ASSERT_FALSE(D_obtenirFinDeMotValide(D_obtenirFils(D_obtenirFrere(dico))));
	CU_ASSERT_EQUAL(D_obtenirLettre(D_obtenirFils(D_obtenirFils(D_obtenirFrere(dico)))), 'a');
	CU_ASSERT_FALSE(D_obtenirFinDeMotValide(D_obtenirFils(D_obtenirFils(D_obtenirFrere(dico)))));
	CU_ASSERT_EQUAL(D_obtenirLettre(D_obtenirFils(D_obtenirFils(D_obtenirFils(D_obtenirFrere(dico))))), 't');
	CU_ASSERT_TRUE(D_obtenirFinDeMotValide(D_obtenirFils(D_obtenirFils(D_obtenirFils(D_obtenirFrere(dico))))));

	D_liberer(&dico);
}

/**
 * \fn void test_D_motPresent(void)
 * \brief Tests unitaires de la fonction D_motPresent.
 * 
 */
void test_D_motPresent(void)
{
	D_Dictionnaire dico = D_dictionnaire();
	D_ajouterUnMot(&dico, "chat");
	D_ajouterUnMot(&dico, "chatton");
	D_ajouterUnMot(&dico, "c");
	D_ajouterUnMot(&dico, "suis");
	D_ajouterUnMot(&dico, "suicc");
	D_ajouterUnMot(&dico, "armoir");
	D_ajouterUnMot(&dico, "livre");
	CU_ASSERT_TRUE(D_motPresent(dico, "chat"));
	CU_ASSERT_TRUE(D_motPresent(dico, "chat"));
	CU_ASSERT_TRUE(D_motPresent(dico, "armoir"));
	CU_ASSERT_TRUE(D_motPresent(dico, "livre"));
	CU_ASSERT_TRUE(D_motPresent(dico, "c"));
	CU_ASSERT_TRUE(D_motPresent(dico, "suis"));
	CU_ASSERT_FALSE(D_motPresent(dico, "suic"));
	CU_ASSERT_FALSE(D_motPresent(dico, "h"));
	CU_ASSERT_FALSE(D_motPresent(dico, "a"));
	CU_ASSERT_FALSE(D_motPresent(dico, "l"));
	CU_ASSERT_FALSE(D_motPresent(dico, "t"));
	CU_ASSERT_FALSE(D_motPresent(dico, "cha"));
	CU_ASSERT_FALSE(D_motPresent(dico, "livres"));
	CU_ASSERT_FALSE(D_motPresent(dico, "amoir"));
	D_liberer(&dico);
}

/**
 * \fn void test_D_serialiser_et_D_deserialiser(void)
 * \brief Tests unitaires de la procédure D_serialiser et de la fonction D_deserialiser.
 * 
 */
void test_D_serialiser_et_D_deserialiser(void)
{
	D_Dictionnaire dico = D_dictionnaire();
	D_ajouterUnMot(&dico, "chatton");
	D_ajouterUnMot(&dico, "mouton");
	D_ajouterUnMot(&dico, "dictionnaire");
	D_serialiser(dico, "dico");
	D_liberer(&dico);
	dico = D_deserialiser("dico");
	CU_ASSERT_TRUE(D_motPresent(dico, "chatton"));
	CU_ASSERT_TRUE(D_motPresent(dico, "mouton"));
	CU_ASSERT_TRUE(D_motPresent(dico, "dictionnaire"));
	CU_ASSERT_FALSE(D_motPresent(dico, "chat"));
	CU_ASSERT_FALSE(D_motPresent(dico, "chattons"));
	CU_ASSERT_FALSE(D_motPresent(dico, "chaton"));
	CU_ASSERT_FALSE(D_motPresent(dico, "moutons"));
	CU_ASSERT_FALSE(D_motPresent(dico, "dictionaire"));
	D_liberer(&dico);
}