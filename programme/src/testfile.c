/**
 * \file testfile.c
 * \author Tristan LOUKIANENKO.
 * \brief Développement des tests unitaires de F_File.
 * \version 1.0
 * \date 2021-12-27
 *
 *
 */

#include <CUnit/Basic.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"

/**
 * \fn void test_F_file(void)
 * \brief Tests unitaires de la fonction F_file.
 *
 */
void test_F_file(void)
{
    F_File file = F_file();
    CU_ASSERT_PTR_NULL(file);
}

/**
 * \fn void test_F_enfiler(void)
 * \brief Tests unitaires de la procédure F_enfiler.
 *
 */
void test_F_enfiler(void)
{
    F_File file = F_file();

    char *element = (char *)malloc(255 * sizeof(char));
    char *element2 = (char *)malloc(255 * sizeof(char));
    char *element3 = (char *)malloc(255 * sizeof(char));

    strcpy(element, "bonjour");
    strcpy(element2, "comment");
    strcpy(element3, "çava");

    F_enfiler(&file, (void **)&element, 255 * sizeof(char));
    F_enfiler(&file, (void **)&element2, 255 * sizeof(char));
    F_enfiler(&file, (void **)&element3, 255 * sizeof(char));

    CU_ASSERT_PTR_EQUAL(file->queueDeFile, file->fileSuivante->fileSuivante);
    //char *mot = (char*)malloc(255*sizeof(char));
    
    CU_ASSERT_STRING_EQUAL("bonjour", file->element);
    CU_ASSERT_STRING_EQUAL("comment", file->fileSuivante->element);
    CU_ASSERT_STRING_EQUAL("çava", file->fileSuivante->fileSuivante->element);

    free(file->fileSuivante->fileSuivante->element);
    free(file->fileSuivante->fileSuivante);
    free(file->fileSuivante->element);
    free(file->fileSuivante);
    free(file->element);
    free(file);
}

/**
 * \fn void test_F_estVide(void)
 * \brief Tests unitaires de la fonction F_estVide.
 *
 */
void test_F_estVide(void)
{
    F_File file = F_file();
    CU_ASSERT_TRUE(F_estVide(file));

    F_File file2 = F_file();
    char *element = (char *)malloc(255 * sizeof(char));
    strcpy(element, "bonjour");
    F_enfiler(&file2, (void **)&element, 255 * sizeof(char));
    CU_ASSERT_FALSE(F_estVide(file2));
    free(file2->element);
    free(file2);
}

/**
 * \fn void test_F_obtenirElement(void)
 * \brief Tests unitaires de la fonction F_obtenirElement.
 *
 */
void test_F_obtenirElement(void)
{
    F_File file = F_file();
    char *element = (char *)malloc(255 * sizeof(char));
    strcpy(element, "bonjour");
    F_enfiler(&file, (void **)&element, 255 * sizeof(char));
    char *elementObtenu = F_obtenirElement(file, 255 * sizeof(char));
    CU_ASSERT_STRING_EQUAL("bonjour", elementObtenu);
    F_defiler(&file);
    free(elementObtenu);
}

/**
 * \fn void test_F_defiler(void)
 * \brief Tests unitaires de la procédure F_defiler.
 *
 */
void test_F_defiler(void)
{
    char *element = (char *)malloc(255 * sizeof(char));
    char *element2 = (char *)malloc(255 * sizeof(char));
    char *element3 = (char *)malloc(255 * sizeof(char));

    strcpy(element, "bonjour");
    strcpy(element2, "comment");
    strcpy(element3, "çava");

    F_File file = F_file();
    F_enfiler(&file, (void **)&element, 255 * sizeof(char));
    F_enfiler(&file, (void **)&element2, 255 * sizeof(char));
    F_enfiler(&file, (void **)&element3, 255 * sizeof(char));

    unsigned int i = 0;
    while (!F_estVide(file))
    {
        char *elementObtenu3 = F_obtenirElement(file, 255 * sizeof(char));
        if (i == 1)
        {
            CU_ASSERT_STRING_EQUAL("comment", elementObtenu3);
        }
        if (i == 2)
        {
            CU_ASSERT_STRING_EQUAL("çava", elementObtenu3);
        }
        free(elementObtenu3);
        F_defiler(&file);
        i++;
    }
}

/**
 * \fn void test_F_nbElement(void)
 * \brief Tests unitaires de la fonction F_nbElement.
 *
 */
void test_F_nbElement(void)
{
    F_File file = F_file();
    char *element = (char *)malloc(255 * sizeof(char));
    strcpy(element, "bonjour");
    F_enfiler(&file, (void **)&element, 255 * sizeof(char));
    element = (char *)malloc(255 * sizeof(char));
    strcpy(element, "comment");
    F_enfiler(&file, (void **)&element, 255 * sizeof(char));
    CU_ASSERT_TRUE(F_nbElements(file) == 2);
    element = (char *)malloc(255 * sizeof(char));
    strcpy(element, "çava");
    F_enfiler(&file, (void **)&element, 255 * sizeof(char));
    CU_ASSERT_TRUE(F_nbElements(file) == 3);

    char *elementObtenu = F_obtenirElement(file, 255 * sizeof(char));
    free(elementObtenu);
    F_defiler(&file);
    elementObtenu = F_obtenirElement(file, 255 * sizeof(char));
    free(elementObtenu);
    F_defiler(&file);
    elementObtenu = F_obtenirElement(file, 255 * sizeof(char));
    free(elementObtenu);
    F_defiler(&file);
}
