/**
 * \file file.h
 * \author Raphaël Largeau
 * \brief Développement de F_File.
 * \version 1
 * \date 2021-12-28
 * 
 * 
 */

#ifndef __FILE_GENERIQUE__
#define __FILE_GENERIQUE__
#include <stdlib.h>

/**
 * \struct F_File
 * \brief file générique
 * 
 */
typedef struct F_Noeud *F_File;

/**
 * \struct F_Noeud
 * \brief noeud d'une file générique
 * 
 */
typedef struct F_Noeud
{
    void *element;          /*! pointeur vers un élément de la file de type indéterminé */
    F_File fileSuivante;    /*! pointeur vers le F_Noeud suivant */
    F_File queueDeFile;     /*! ponteur vers le dernier F_Noeud de la file */
} F_Noeud;

//Initialisation
F_File F_file(void);

//Enfiler et défiler
void F_enfiler(F_File *pFile, void **motSource, size_t taille);
void F_defiler(F_File *pFile);

//Obtenir un élément
void *F_obtenirElement(F_File maFile, size_t taille);

//Autres
unsigned int F_estVide(F_File maFile);
unsigned int F_nbElements(F_File maFile);

#endif
