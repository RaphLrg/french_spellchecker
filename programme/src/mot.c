/**
 * \file mot.c
 * \brief Développement des fonctions relatives à la conception détaillée.
 * \author Clément OBLED.
 * \version 1.3
 * \date 15/12/2021
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mot.h>
#include <motPrive.h>
#define TAILLE_MOT 255 * sizeof(char)

/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn int M_ord(char caractere)
 * \brief Fonction qui retourne le chiffre d'un caractère dans la table ascii.
 *
 * \param *str est le caractère.
 * \return int, le chiffre de la table ascii.
 */
int M_ord(char caractere)
{
	return (int)caractere;
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn char M_chr(int chiffre)
 * \brief Fonction qui retourne le caractère du chiffre de la table ascii.
 *
 * \param chiffre est le chiffre de la table ascii.
 * \return char, le caractère de la table ascii.
 */
char M_chr(int chiffre)
{
	return (char)chiffre;
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn unsigned int M_estUnCaractereValide(char c)
 * \brief Fonction qui retourne la validité d'un caractère (0 si faux, 1 si vrai).
 *
 * \param c est le caractère a tester.
 * \return int, la validité du caractère (0 si faux, 1 si vrai).
 */
unsigned int M_estUnCaractereValide(char c)
{
	return (M_ord('a') <= M_ord(c) && M_ord(c) <= M_ord('z')) || c == '-';
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn char *mot M_motVide()
 * \brief Fonction qui retourne une chaine de caractère vide.
 *
 * \param pas de paramètre.
 * \return char *mot, la chaine de caracère vide.
 */
char *M_motVide()
{
	// char *mot;
	return NULL;
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn char M_iemeCaractere(char *mot, unsigned int i)
 * \brief Fonction qui retourne le ième caractère d'un mot.
 *
 * \param *mot, i, i est le caractère de *mot que l'ont veux obtenir.
 * \return mot[i], retourne le ième caractère du mot..
 */
char M_iemeCaractere(char *mot, unsigned int i)
{
	assert(i <= strlen(mot));
	return mot[i];
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn unsigned int M_longueur(char *mot)
 * \brief Fonction qui retourne la longueur d'un mot.
 *
 * \param *mot, le mot dont on doit claculer sa longueur.
 * \return i, la longueur du mot.
 */
unsigned int M_longueur(char *mot)
{
	unsigned int i = 0;
	while (M_estUnCaractereValide(M_iemeCaractere(mot, i)) == 1)
	{
		i++;
	}
	return i;
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn unsigned int M_longueurCDC(char *cdc)
 * \brief Fonction qui retourne la longueur d'une chaine de caractère.
 *
 * \param *cdc, la chaine de caractère dont on doit calculer sa M_longueur.
 * \return i, la longueur de la chaine de caractère.
 */
unsigned int M_longueurCDC(char *cdc)
{
	return strlen(cdc);
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn unsigned int M_estMot(char *cdc)
 * \brief Fonction qui si une chaine de caractères est un mot ou non.
 *
 * \param *mot, le mot dont on doit claculer sa M_longueur.
 * \return res, renvoit 1 si le mot est valide, 0 sinon.
 */
unsigned int M_estMot(char *cdc)
{
	unsigned int res = 1;
	unsigned int i = 0;
	while (res == 1 && i <= (M_longueurCDC(cdc) - 1))
	{
		if (!M_estUnCaractereValide(M_iemeCaractere(cdc, i)))
		{
			return res = 0;
		}
		i++;
	}
	return res = 1;
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn unsigned int M_estUneMaj(char c)
 * \brief Fonction qui retourne si un caractère est une majuscule (0 si il ne l'est pas 1 si c'est une majuscule).
 *
 * \param c, le caractère a tester.
 * \return 1 si c'est une majuscule, 0 sinon.
 */
unsigned int M_estUneMaj(char c)
{
	if ((M_ord('A') <= M_ord(c)) & (M_ord(c) <= M_ord('Z')))
		return 1;
	else
		return 0;
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn void M_majEnMin(char c)
 * \brief Procedure qui change un caractère majuscule en minuscule.
 *
 * \param entré/sortie c, le caractère majuscule que l'ont veut changer en minuscule.
 */
char M_majEnMin(char c)
{
	if (M_estUneMaj(c))
	{
		return c = M_chr(M_ord(c) - M_ord('A') + M_ord('a'));
	}
	else
	{
		return c;
	}
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn unsigned int M_estUnAccent(char c)
 * \brief Fonction qui retourne 1 si le caractère est un accent 0 si il ne l'est pas.
 *
 * \param c, le caractère a tester.
 * \return unsigned int, 0 si ça n'est pas un accent 1 si oui.
 */
unsigned int M_estUnAccent(char c)
{
	return -96 <= M_ord(c) && M_ord(c) <= -65;
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn void M_passerSansAccent(char c)
 * \brief Procedure qui modifie un caractère avec accent en un caractère sans accent.
 *
 * \param entré/sortie c, le caractère qui passe sans accent.
 */
char M_passerSansAccent(char c)
{
	char caractereARetourner = 'c';

	if (-67 == M_ord(c) || M_ord(c) == -65)
	{
		caractereARetourner = 'y';
	}
	if (-71 <= M_ord(c) && M_ord(c) <= -68)
	{
		caractereARetourner = 'u';
	}
	if (-78 <= M_ord(c) && M_ord(c) <= -74)
	{
		caractereARetourner = 'o';
	}
	if (-84 <= M_ord(c) && M_ord(c) <= -81)
	{
		caractereARetourner = 'i';
	}
	if (-88 <= M_ord(c) && M_ord(c) <= -85)
	{
		caractereARetourner = 'e';
	}
	if (M_ord(c) == -89)
	{
		caractereARetourner = 'c';
	}
	if (-96 <= M_ord(c) && M_ord(c) <= -90)
	{
		caractereARetourner = 'a';
	}
	return caractereARetourner;
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn void M_supprimerIemeLettre(char *mot, unsigned int indiceASupprimer)
 * \brief Procedure qui supprime la lettre d'un mot.
 *
 * \param *mot, le mot dont on veut supprimer la lettre.
 * \param indiceASupprimer, la position de la lettre a supprimer.
 */
void M_supprimerIemeLettre(char *mot, unsigned int indiceASupprimer)
{
	for (unsigned int i = 0; i <= M_longueurCDC(mot); i++)
	{
		if (i > indiceASupprimer)
		{
			mot[i - 1] = mot[i];
		}
	}
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn char *M_motFinal(char *cdc)
 * \brief Fonction qui retourne un mot valide et sans les caractères spéciaux du aux accents.
 *
 * \param *cdc, qui est la chaine de caractère presque considérée comme un mot.
 * \return *mot, le mot valide créé à partir de la chaine de caractère.
 */
void M_motFinal(char *cdc)
{
	//printf("\n |%i| ",M_longueurCDC(cdc));
	for (unsigned int i = 0; i < M_longueurCDC(cdc); i++)
	{
		//printf("- %i ",i);
		if (!M_estUnCaractereValide(cdc[i]))
		{
			M_supprimerIemeLettre(cdc, i);
		}
	}
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * \fn char *mot M_creerMot(char *cdc)
 * \brief Fonction qui retourne un mot valide à partir d'une chaine de caractère.
 *
 * \param *cdc, qui est la chaine de caractère pas encore considéré comme un mot.
 * \return *mot, le mot valide créer à partir de la chaine de caractère.
 */
char *M_creerMot(char *cdc)
{
	char *cdcModifiable = (char *)malloc(TAILLE_MOT);
	strcpy(cdcModifiable, cdc);
	unsigned int tailleChaine = M_longueurCDC(cdc);
	char caractere, caractereSuivant;
	char *monMot = (char *)malloc(255 * sizeof(char));
	unsigned int i = 0;
	unsigned int j = 0;
	while (j < tailleChaine)
	{
		caractere = M_iemeCaractere(cdc, j);
		caractereSuivant = M_iemeCaractere(cdc, j + 1);
		if (M_estUneMaj(caractere))
		{
			cdcModifiable[i] = M_majEnMin(caractere);
		}
		else
		{
			if (M_ord(caractere) == -61 && M_estUnAccent(caractereSuivant))
			{
				cdcModifiable[i] = M_passerSansAccent(caractereSuivant);
				j++;
			}
			else
			{
				cdcModifiable[i] = cdc[j];
			}
		}
		i++;
		j++;
	}
	cdcModifiable[i] = '\0';
	M_motFinal(cdcModifiable);
	strcpy(monMot, cdcModifiable);
	free(cdcModifiable);
	if (M_estMot(monMot))
	{
		return monMot;
	}
	else
	{
		free(monMot);
		return NULL;
	}
}
