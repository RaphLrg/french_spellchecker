/**
 * \file testDictionnaire.h
 * \author Clément OBLED.
 * \brief Tests unitaires de D_Dictionnaire.
 * \version 1
 * \date 2021-12-28
 * 
 */

#ifndef __TEST_DICTIONNAIRE__
#define __TEST_DICTIONNAIRE__

void test_D_dictionnaire(void);
void test_D_creerNoeud(void);
void test_D_liberer(void);
void test_D_ajouterUneLettre(void);
void test_D_fixerFils(void);
void test_D_fixerFrere(void);
void test_D_fixerLettre(void);
void test_D_obtenirFils(void);
void test_D_obtenirFrere(void);
void test_D_obtenirLettre(void);
void test_D_obtenirFinDeMotValide(void);
void test_D_fixerFinDeMotValide(void);
void test_D_motPresent(void);
void test_D_ajouterUnMot(void);
void test_D_serialiser_et_D_deserialiser(void);

#endif