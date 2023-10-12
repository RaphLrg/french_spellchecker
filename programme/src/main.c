/**
 * \file main.c
 * \author Raphaël LARGEAU.
 * \brief Développement du main.
 * \version 4.2
 * \date 2021-12-28
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "correcteurorthographique.h"
#include "dictionnaire.h"
#include "mot.h"
#include "file.h"
#include <string.h>

/**
 * @fn int main(int argc, const char **argv)
 * \brief Programme principal, il détermine l'option entrée et exécute les fonctions et procédures associées.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, const char **argv)
{
	if (argc > 1)
	{
		if (argv[1][0] == '-')
		{
			if (strcmp(argv[1], "-h") == 0)
			{
				printf("Aide de asispell :\n");
				printf("  asispell -h : cette aide\n");
				printf("  asispell -d dico : correction de l'entree standard a l'aide du dictionnaire dico\n");
				printf("  asispell -d dico -f fic : completer le dictionnaire dico a l'aide des mots du fichier fic (un mot par ligne)\n");
			}
			else
			{
				if (strcmp(argv[1], "-d") == 0 && argc == 3)
				{
					D_Dictionnaire dico = D_dictionnaire();
					dico = D_deserialiser((char *)argv[2]);
					if (dico == NULL)
					{
						printf("Le fichier %s n'existe pas ou n'est pas un dictionnaire.\n", (char *)argv[2]);
					}
					else
					{
						CO_afficherCorrection(dico);
					}
				}
				else
				{
					if (strcmp((char *)argv[1], "-d") == 0 && strcmp((char *)argv[3], "-f") == 0 && argc == 5)
					{
						D_entrerUnDictionnaire((char *)argv[2], (char *)argv[4]);
					}
					else
					{
						printf("Erreur option %s inconnue ou mal utilisée.\nVeuillez utiliser asispell -h pour avoir de l'aide.\n", (char *)argv[1]);
					}
				}
			}
		}
		else
		{
			printf("Erreur, veuillez utiliser asispell -h pour avoir de l'aide.\n");
		}
	}
	else
	{
		printf("Aide de asispell :\n");
		printf("  asispell -h : cette aide\n");
		printf("  asispell -d dico : correction de l'entree standard a l'aide du dictionnaire dico\n");
		printf("  asispell -d dico -f fic : completer le dictionnaire dico a l'aide des mots du fichier fic (un mot par ligne)\n");
	}
	return EXIT_SUCCESS;
}