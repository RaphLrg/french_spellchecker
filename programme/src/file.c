/**
 * \file file.c
 * \author Raphaël Largeau
 * \brief Definition des fonctions du type général F_File
 * \version 1
 * \date 2021-12-20
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "file.h"

/**
 * \fn F_File F_file(void)
 * \brief Renvoit une file vide (initialisée à NULL).
 *
 * \return F_File, de valeur NULL.
 */
F_File F_file(void)
{
    return NULL;
}

/**
 * \fn void F_enfiler(F_File *pFile, void **elementSource, size_t taille)
 * \brief Initialise et alloue un espace mémoire à un noeud en queue de file.
 *
 * \example F_enfiler
 * F_enfiler(&maFile, (void **)&monElement, sizeof(int));\n
 * Avec maFile de type F_File, monElement de type indéterminé (par exemple ici int) et sizeof(int) l'espace mémoire occupé par monElement.
 * \warning L'élément source doit être alloué.
 *
 * \param pFile de type F_File*, pointeur vers la file modifée.
 * \param motSource de type void*, pointeur vers l'élément ajouté.
 * \param taille de type size_t, espace mémoire occupé par l'élément source.
 */
void F_enfiler(F_File *pFile, void **elementSource, size_t taille)
{
    if (F_estVide(*pFile))
    {
        *pFile = (F_File)malloc(sizeof(struct F_Noeud));
        (*pFile)->queueDeFile = *pFile;
        (*pFile)->fileSuivante = F_file();
        (*pFile)->element = malloc(taille);
        memcpy((*pFile)->element, *elementSource, taille);
        free(*elementSource);
    }
    else
    {
        F_File nouvelleFile = (F_File)malloc(sizeof(struct F_Noeud));
        nouvelleFile->fileSuivante = F_file();
        nouvelleFile->element = malloc(taille);
        memcpy(nouvelleFile->element, *elementSource, taille);
        free(*elementSource);
        (*pFile)->queueDeFile->fileSuivante = nouvelleFile;
        (*pFile)->queueDeFile = nouvelleFile;
        // F_File fileSuivanteTemp = (*pFile)->fileSuivante;
        // F_enfiler(&fileSuivanteTemp, elementSource, taille);
        //(*pFile)->fileSuivante = fileSuivanteTemp;
    }
}

/**
 * \fn void F_defiler(F_File *pFile)
 * \brief Libère le noeud en tête de file.
 *
 * \example F_defiler
 * F_defiler(&maFile);\n
 * Avec maFile de type F_File.
 *
 * \warning Ne libère pas son élément, utiliser F_obtenirElement pour cela.
 *
 * \param pFile de type *F_File, pointeur vers la file modifée.
 */
void F_defiler(F_File *pFile)
{
    assert(!F_estVide(*pFile));
    if ((*pFile)->fileSuivante != NULL)
    {
        (*pFile)->fileSuivante->queueDeFile = (*pFile)->queueDeFile;
    }
    F_File nouvelleFile = (*pFile)->fileSuivante;
    free(*pFile);
    *pFile = nouvelleFile;
}

/**
 * \fn int F_estVide(F_File maFile)
 * \brief vérifie si une file est vide (égale à NULL) ou pas
 *
 * \param maFile de type F_File, file de référence
 * \return unsigned int, 1 si la file est vide, 0 sinon
 */
unsigned int F_estVide(F_File maFile)
{
    return NULL == maFile;
}

/**
 * \fn void *F_obtenirElement(F_File maFile, size_t taille)
 * \brief Renvoit l'élément alloué contenu dans la tête de la file et le libère dans la file.
 *
 * \warning Attention libère l'élément lu dans la file.
 *
 * \example F_obtenirElement
 * int monElement = F_obtenirElement(maFile, sizeof(int));\n
 * Avec maFile de type F_File et sizeof(int) l'espace mémoire occupé par un élément de la file (de type indéterminé, dans cet exemple int).
 *
 * \param maFile de type F_File, file de référence.
 * \param taille de type size_t, espace mémoire de l'élément.
 * \return void*, valeur de l'élément contenu en tête de maFile alloué.
 */
void *F_obtenirElement(F_File maFile, size_t taille)
{
    if (!F_estVide(maFile))
    {
        void *nouvelElement = malloc(taille);
        memcpy(nouvelElement, maFile->element, taille);
        free(maFile->element);
        return nouvelElement;
    }
    else
    {
        return NULL;
    }
}

/**
 * \fn unsigned int F_nbElements(F_File maFile)
 * \brief Renvoit le nombre d'éléments d'une file.
 *
 * \param maFile de type F_File, file de référence.
 * \return unsigned int, le nombre d'éléments de la file maFile.
 */
unsigned int F_nbElements(F_File maFile)
{
    F_File fileTemp = maFile;
    unsigned int compteur = 0;
    while (!F_estVide(fileTemp))
    {
        fileTemp = fileTemp->fileSuivante;
        compteur = compteur + 1;
    }
    return compteur;
}
