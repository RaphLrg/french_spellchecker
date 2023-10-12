/**
 * \file dictionnaire.c
 * \brief Fonctions pour le type D_Dictionnaire.
 * \author Raphaël LARGEAU.
 * \version 1.4
 * \date 12/12/2021
 *
 * Description des fonctions à utiliser pour manipuler le type D_Dictionnaire.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "mot.h"
#include "dictionnaire.h"
#include "dictionnairePrive.h"
#define TRUE 1
#define FALSE 0
#define TAILLE_MOT 255*sizeof(char)
#define TAILLE_DICO sizeof(struct D_Noeud)

/**
 * \fn D_Dictionnaire D_obtenirFils(D_Dictionnaire dico)
 * \brief Encapsulation, renvoit la valeur de l'attribut fils du dictionnaire dico.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire de référence.
 * \return D_Dictionnaire, la valeur de l'attribut fils du dictionnaire dico.
 */
D_Dictionnaire D_obtenirFils(D_Dictionnaire dico)
{
    return dico->fils;
}

/**
 * \fn D_Dictionnaire D_obtenirFrere(D_Dictionnaire dico)
 * \brief Encapsulation, renvoit la valeur de l'attribut frere du dictionnaire dico.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire de référence.
 * \return D_Dictionnaire, la valeur de l'attribut frere du dictionnaire dico.
 */
D_Dictionnaire D_obtenirFrere(D_Dictionnaire dico)
{
    return (dico->frere);
}

/**
 * \fn char D_obtenirLettre(D_Dictionnaire dico)
 * \brief Encapsulation, renvoit la valeur de l'attribut lettre du dictionnaire dico.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire de référence.
 * \return char, la valeur de l'attribut lettre du dictionnaire dico.
 */
char D_obtenirLettre(D_Dictionnaire dico)
{
    return (dico->lettre);
}

/**
 * \fn int D_obtenirFinDeMotValide(D_Dictionnaire dico)
 * \brief Encapsulation, renvoit la valeur de l'attribut finDeMotValide du dictionnaire dico.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire de référence.
 * \return unsigned int, la valeur de l'attribut finDeMotValide du dictionnaire dico.
 */
unsigned int D_obtenirFinDeMotValide(D_Dictionnaire dico)
{
    return dico->finDeMotValide;
}

/**
 * \fn void D_fixerFils(D_Dictionnaire dico, D_Dictionnaire filsDico)
 * \brief Encapsulation, change la valeur de l'attribut fils du dictionnaire dico.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire dont on modifie la valeur de son attribut fils.
 * \param filsDico de type D_Dictionnaire, la valeur donnée à l'attribut fils du dictionnaire dico.
 */
void D_fixerFils(D_Dictionnaire dico, D_Dictionnaire filsDico)
{
    dico->fils = filsDico;
}

/**
 * \fn void D_fixerFrere(D_Dictionnaire dico, D_Dictionnaire frereDico)
 * \brief Encapsulation, change la valeur de l'attribut frere du dictionnaire dico.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire dont on modifie la valeur de son attribut frere.
 * \param frereDico de type D_Dictionnaire, la valeur donnée à l'attribut frere du dictionnaire dico.
 */
void D_fixerFrere(D_Dictionnaire dico, D_Dictionnaire frereDico)
{
    dico->frere = frereDico;
}

/**
 * \fn void D_fixerLettre(D_Dictionnaire dico, char lettreDico)
 * \brief Encapsulation, change la valeur de l'attribut lettre du dictionnaire dico.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire dont on modifie la valeur de son attribut lettre.
 * \param lettreDico de type char, la valeur donnée à l'attribut lettre du dictionnaire dico.
 */
void D_fixerLettre(D_Dictionnaire dico, char lettreDico)
{
    dico->lettre = lettreDico;
}

/**
 * \fn void D_fixerFinDeMotValide(D_Dictionnaire dico, unsigned int finDeMotValideDico)
 * \brief Encapsulation, change la valeur de l'attribut finDeMotValide du dictionnaire dico.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire dont on modifie la valeur de son attribut finDeMotValide.
 * \param finDeMotValideDico de type unsigned int, la valeur donnée à l'attribut finDeMotValide du dictionnaire dico.
 */
void D_fixerFinDeMotValide(D_Dictionnaire dico, unsigned int finDeMotValideDico)
{
    dico->finDeMotValide = finDeMotValideDico;
}

/**
 * \fn D_Dictionnaire D_creerNoeud(char lettre)
 * \brief Renvoit un noeud de dictionnaire alloué et initialisé
 *
 * \param lettre de type char, le caractère que va contenir le noeud.
 * \return D_Dictionnaire, les attributs fils et frère sont initialisés à NULL, l'attribut lettre vaut la valeur de la variable lettre donnée en entrée, l'attribut finDeMotValide est initialisé à 0 (FAUX).
 */
D_Dictionnaire D_creerNoeud(char lettre)
{
    D_Dictionnaire dico = (D_Dictionnaire)malloc(TAILLE_DICO);
    D_fixerFils(dico, NULL);
    D_fixerFrere(dico, NULL);
    D_fixerLettre(dico, lettre);
    D_fixerFinDeMotValide(dico, FALSE);
    return dico;
}

/**
 * \fn void D_liberer(D_Dictionnaire *pdico)
 * \brief lLibère réccursivement les espaces mémoire alloués au dictionnaire dico.
 *
 * \param pdico de type D_Ditionnaire, le dictionnaire libéré égal à NULL en sortie de procédure.
 */
void D_liberer(D_Dictionnaire *pdico)
{
    if (D_obtenirFils(*pdico) != NULL)
    {
        D_Dictionnaire fils = D_obtenirFils(*pdico);
        D_liberer(&fils);
    }
    if (D_obtenirFrere(*pdico) != NULL)
    {
        D_Dictionnaire frere = D_obtenirFrere(*pdico);
        D_liberer(&frere);
    }
    free(*pdico);
    *pdico = NULL;
}

/**
 * \fn D_Dictionnaire D_ajouterUneLettre(D_Dictionnaire *pdico, char lettre)
 * \brief Ajoute le caractère lettre si il n'est pas présent parmis les frères du dictionnaire dico et renvoit un pointeur vers le noeud contenant le caractère, si le caractère est présent, renvoit juste le pointeur vers le noeud le contenant.
 *
 * \param pdico de type *D_Dictionnaire, le dictionnaire dans lequel on ajoute la lettre.
 * \param lettre de type char, le caractère à ajouter.
 * \return D_Dictionnaire.
 */
D_Dictionnaire D_ajouterUneLettre(D_Dictionnaire *pdico, char lettre)
{
    if (*pdico == NULL)
    {
        *pdico = D_creerNoeud(lettre);
        return *pdico;
    }
    else
    {
        if (D_obtenirLettre(*pdico) != lettre)
        {
            D_Dictionnaire temp = D_obtenirFrere(*pdico);
            D_Dictionnaire dicoARetourner = D_ajouterUneLettre(&temp, lettre);
            D_fixerFrere(*pdico, temp);
            return dicoARetourner;
        }
        else
        {
            return *pdico;
        }
    }
}

/**
 * \fn D_Dictionnaire D_dictionnaire(void)
 * \brief Renvoit un dictionnaire vide.
 *
 * \return D_Dictionnaire, de valeur NULL.
 */
D_Dictionnaire D_dictionnaire(void)
{
    return NULL;
}

/**
 * \fn D_Dictionnaire D_trouverLettreDansLesFreres(D_Dictionnaire dico, char lettre)
 * \brief Renvoit un pointeur vers le noeud contenant le caractère lettre donnée parmi les frères dépendant du dictionnaire dico si il existe, sinon renvoit NULL.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire de référence.
 * \param lettre de type char, la lettre recherchée.
 * \return D_Dictionnaire pointeur vers le frère contenant le caractère lettre si il existe, sinon NULL.
 */
D_Dictionnaire D_trouverLettreDansLesFreres(D_Dictionnaire dico, char lettre)
{
    if (dico == NULL)
    {
        return NULL;
    }
    else
    {
        if (D_obtenirLettre(dico) == lettre)
        {
            return dico;
        }
        else
        {
            return D_trouverLettreDansLesFreres(D_obtenirFrere(dico), lettre);
        }
    }
}

/**
 * \fn void D_ajouterUnMotReccursif(D_Dictionnaire *pdico, char *mot, int i, int tailleDuMot)
 * \brief Ajouter réccursivement un à un les caractères du mot dans le dictionnaire dico.
 *
 * \param pdico de type *D_Dictionnaire, pointeur vers le dictionnaire dans lequel on va ajouter le mot.
 * \param mot de type *char, le mot à ajouter dans le dictionnaire.
 * \param i de type unsigned int, l'indice du caractère atteint dans la réccursivité.
 * \param tailleDuMot de type unsigned int, la longueur du mot à ajouter.
 */
void D_ajouterUnMotReccursif(D_Dictionnaire *pdico, char *mot, int i, int tailleDuMot)
{
    D_Dictionnaire temp = D_dictionnaire();
    if (*pdico == NULL)
    {
        *pdico = D_creerNoeud((mot[i]));
        temp = *pdico;
    }
    else
    {
        temp = D_ajouterUneLettre(pdico, mot[i]);
    }
    if (i < tailleDuMot)
    {
        D_Dictionnaire fils = D_obtenirFils(temp);
        D_ajouterUnMotReccursif(&fils, mot, i + 1, tailleDuMot);
        D_fixerFils(temp, fils);
    }
    else
    {
        D_fixerFinDeMotValide(temp, TRUE);
    }
}

/**
 * \fn void D_ajouterUnMot(D_Dictionnaire *pdico, char *mot)
 * \brief Ajoute un mot dans le dictionnaire dico.
 *
 * \param pdico de type *D_Dictionnaire, pointeur vers le dictionnaire dans lequel on va ajouter le mot.
 * \param mot de type *char, le mot à ajouter dans le dictionnaire.
 */
void D_ajouterUnMot(D_Dictionnaire *pdico, char *mot)
{
    D_ajouterUnMotReccursif(pdico, mot, 0, M_longueur(mot) - 1);
}

/**
 * \fn unsigned int D_motPresentReccursif(D_Dictionnaire dico, char *mot, unsigned int i, unsigned int tailleDuMot)
 * \brief Recherche reccursivement un à un les caractères du mot dans le dictionnaire.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire de référence.
 * \param mot de type *char, le mot recherché.
 * \param i de type unsigned int, l'indice du caractère atteint dans la réccursivité.
 * \param tailleDuMot de type unsigned int, la longueur du mot recherché.
 * \return unsigned int, 1 si le mot est présent, 0 sinon.
 */
unsigned int D_motPresentReccursif(D_Dictionnaire dico, char *mot, unsigned int i, unsigned int tailleDuMot)
{
    D_Dictionnaire temp = D_trouverLettreDansLesFreres(dico, mot[i]);
    if (temp == NULL)
    {
        return FALSE;
    }
    else
    {
        if (tailleDuMot == i)
        {
            return D_obtenirFinDeMotValide(temp);
        }
        else
        {
            temp = D_obtenirFils(temp);
            return D_motPresentReccursif(temp, mot, i + 1, tailleDuMot);
        }
    }
}

/**
 * \fn int D_motPresent(D_Dictionnaire dico, char *mot)
 * \brief Vérifie si un mot est présent dans le dictionnaire dico.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire de réference.
 * \param mot de type *char, le mot que l'on recherche dans le dictionnaire.
 * \return int, 1 si le mot est présent, 0 sinon.
 */
unsigned int D_motPresent(D_Dictionnaire dico, char *mot)
{
    return D_motPresentReccursif(dico, mot, 0, M_longueur(mot) - 1);
}

/**
 * \fn void D_serialiserReccursif(D_Dictionnaire dico, FILE *fichier)
 * \brief Remplit récursivement le fichier à partir du dictionnaire dico.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire à sérialiser.
 * \param fichier de type *FILE fichier stockant le dictionnaire.
 */
void D_serialiserReccursif(D_Dictionnaire dico, FILE *fichier)
{
    if (dico != NULL)
    {
        fputc(D_obtenirLettre(dico), fichier);
        if (D_obtenirFinDeMotValide(dico))
        {
            fputc('.', fichier);
        }
        else
        {
            fputc('_', fichier);
        }
        D_serialiserReccursif(D_obtenirFrere(dico), fichier);
        D_serialiserReccursif(D_obtenirFils(dico), fichier);
    }
    else
    {
        fputc('#', fichier);
    }
}

/**
 * \fn void D_serialiser(D_Dictionnaire dico, char *nomFichier)
 * \brief Sérialise le dictionnaire dico sous forme du fichier nommé <nomFichier>.
 *
 * \param dico de type D_Dictionnaire, le dictionnaire à sérialiser.
 * \param nomFichier de type *char, le nom du fichier.
 */
void D_serialiser(D_Dictionnaire dico, char *nomFichier)
{
    FILE *fichier = fopen(nomFichier, "w");
    fputc('&', fichier);
    D_serialiserReccursif(dico, fichier);
    fclose(fichier);
}

/**
 * \fn void D_deserialiserReccursif(D_Dictionnaire *pdico, FILE *fichier)
 * \brief Reconstruit récursivement le dictionnaire pointé par pdico à partir du fichier.
 *
 * \param pdico de type *D_Dictionnaire qui est reconstruit.
 * \param fichier de type *FILE pointeur vers le fichier contenant le dictionnaire.
 */
void D_deserialiserReccursif(D_Dictionnaire *pdico, FILE *fichier)
{
    if (!feof(fichier))
    {
        char lettre = fgetc(fichier);
        if (lettre == '#')
        {
            free(*pdico);
            *pdico = D_dictionnaire();
        }
        else
        {
            char finDeMotValide = fgetc(fichier);
            *pdico = D_creerNoeud(lettre);
            if (finDeMotValide == '.')
            {
                D_fixerFinDeMotValide(*pdico, TRUE);
            }
            D_Dictionnaire frere = D_dictionnaire();
            D_deserialiserReccursif(&frere, fichier);
            D_fixerFrere(*pdico, frere);

            D_Dictionnaire fils = D_dictionnaire();
            D_deserialiserReccursif(&fils, fichier);
            D_fixerFils(*pdico, fils);
        }
    }
    else
    {
        free(*pdico);
    }
}

/**
 * \fn D_Dictionnaire D_deserialiser(char *nomFichier)
 * \brief Déserialise un fichier contenant un dictionnaire et renvoit ce dictionnaire.
 *
 * \param nomFichier de type char* nom du fichier à déserialiser.
 * \return D_Dictionnaire le dictionnaire obtenu.
 */
D_Dictionnaire D_deserialiser(char *nomFichier)
{
    D_Dictionnaire dico = D_dictionnaire();
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier != NULL)
    {
        if (fgetc(fichier) == '&')
        {
            D_deserialiserReccursif(&dico, fichier);
            fclose(fichier);
            return dico;
        }
        else
        {
            fclose(fichier);
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

/**
 * @fn F_File D_fichierVersFile(char *nomDuFichier)
 * \brief Fonction qui sépare les mots d'un fichier et qui renvoit uniquement les mots valides dans une file.
 * 
 * @param nomDuFichier de type char*, le nom du fichier.
 * @return F_File 
 */
F_File D_fichierVersFile(char *nomDuFichier)
{
	FILE *fichier = fopen(nomDuFichier, "r");
	F_File maFile = F_file();
	if (fichier != NULL)
	{
		while (!feof(fichier))
		{
			char *mot = (char *)malloc(TAILLE_MOT);
			fgets(mot, 255, fichier);
			if (mot != NULL)
			{
				if (!feof(fichier))
				{
					char *motValide = M_creerMot(mot);
					if (motValide != NULL)
					{
						F_enfiler(&maFile, (void **)&motValide, TAILLE_MOT);
					}
				}
				free(mot);
			}
		}
		fclose(fichier);
		return maFile;
	}
	else
	{
		return NULL;
	}
}

/**
 * @fn void D_entrerUnDictionnaire(char *nomDico, char *nomFichier)
 * \brief Fonction qui remplit un dictionnaire et le sérialise à partir d'un fichier de mots.
 * 
 * @param nomDico de type char*, nom du fichier dictionnaire créé.
 * @param nomFichier de type char*, nom du fichier contenant les mots à ajouter.
 */
void D_entrerUnDictionnaire(char *nomDico, char *nomFichier)
{
	D_Dictionnaire dico = D_dictionnaire();
	F_File maFile = D_fichierVersFile(nomFichier);
	if (maFile == NULL)
	{
		printf("Le fichier %s n'existe pas.\n", nomFichier);
	}
	else
	{
		while (!F_estVide(maFile))
		{
			char *monMot = F_obtenirElement(maFile, TAILLE_MOT);
			D_ajouterUnMot(&dico, monMot);
			free(monMot);
			F_defiler(&maFile);
		}
		D_serialiser(dico, nomDico);
		D_liberer(&dico);
	}
}