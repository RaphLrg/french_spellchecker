/**
 * \file correcteurOrthographique.c
 * \brief Développement des fonctions relatives à la conception détaillée.
 * \author Tristan LOUKIANENKO.
 * \version 2.2
 * \date 15/12/2021
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "file.h"
#include "correcteurorthographique.h"
#include "dictionnaire.h"
#include "mot.h"
#define TAILLE_MOT 255 * sizeof(char)
#define TAILLE_FILE sizeof(F_File)
#define TAILLE_CORRECTION sizeof(C_Correction)
#define TAILLE_CORRECTEUR sizeof(CO_CorrecteurOrthographique)
#define TAILLE_MAX_CHAINE 10000 * sizeof(char)

/**
 * \fn void CO_decomposerMotEnDeux(char *mot, unsigned int p, char *motg, char *motd)
 * \brief Procédure permettant de décomposer un mot en deux.
 *
 * \param mot le mot à découper en entrée.
 * \param p l'indice de la découpe en entrée.
 * \param motg la coupe gauche du mot en sortie.
 * \param motd la coupe droite du mot en sortie.
 */
void CO_decomposerMotEnDeux(char *mot, unsigned int p, char *motg, char *motd)
{
    assert(p > 0);
    assert(p < M_longueurCDC(mot));
    for (unsigned int i = 0; i < p; i++)
    {
        motg[i] = M_iemeCaractere(mot, i);
    }
    motg[p] = '\0';
    for (unsigned int i = p; i <= M_longueur(mot); i++)
    {
        motd[i - p] = M_iemeCaractere(mot, i);
    }
    motd[M_longueur(mot) + 1] = '\0';
}

/**
 * \fn void CO_insererLettre(char *mot, unsigned int p, char e)
 * \brief Procédure permettant d'insérer une lettre dans un mot
 *
 * \param mot est le mot à modifier en entrée sortie.
 * \param p est l'indice où insérer la lettre en entrée.
 * \param e est la lettre à insérer en entrée.
 */
void CO_insererLettre(char *mot, unsigned int p, char e)
{
    assert(M_longueur(mot) < 255);
    assert(p <= M_longueur(mot));
    // unsigned int tailleDuMot = M_longueur(mot);
    for (unsigned int i = M_longueur(mot) + 1; i > p; i--)
    {
        mot[i] = mot[i - 1];
    }
    mot[p] = e;
}

/**
 * \fn void CO_inverserDeuxLettresConsecutives(char *mot, unsigned int p)
 * \brief Procédure permettant d'inverser deux lettres consécutives dans un mot.
 *
 * \param mot est le mot à modifier en entrée sortie.
 * \param p est l'indice où inverser les lettres (indice de la première lettre à inverser) en entrée.
 */
void CO_inverserDeuxLettresConsecutives(char *mot, unsigned int p)
{
    assert(p < M_longueur(mot) - 1);
    char lettreTemp = M_iemeCaractere(mot, p);
    mot[p] = M_iemeCaractere(mot, p + 1);
    mot[p + 1] = lettreTemp;
}

/**
 * \fn void CO_remplacerLettre(char *mot, unsigned int p, char e)
 * \brief Procédure permettant de remplacer une lettre dans un mot.
 *
 * \param mot est le mot à modifier en entrée sortie.
 * \param p est l'indice où insérer la lettre en entrée.
 * \param e est la lettre à insérer en entrée.
 */
void CO_remplacerLettre(char *mot, unsigned int p, char e)
{
    assert(p < M_longueur(mot));
    mot[p] = e;
}

/**
 * \fn void CO_supprimerLettre(char *mot, unsigned int p)
 * \brief Procédure permettant de supprimer une lettre dans un mot.
 *
 * \param mot est le mot à modifier en entrée sortie.
 * \param p est l'indice de la lettre à supprimer en entrée.
 */
void CO_supprimerLettre(char *mot, unsigned int p)
{
    assert(p < M_longueur(mot));
    for (unsigned int i = p; i < M_longueur(mot); i++)
    {
        mot[i] = M_iemeCaractere(mot, i + 1);
    }
}

/**
 * \fn void C_fixerNbCorrections(C_Correction *pCorrection, unsigned int nbSource)
 * \brief Procédure pour fixer l'attribut nbCorrections d'une variable de type C_Correction.
 *
 * \param pCorrection est de type C_Correction*.
 * \param nbSource est le nombre de corrections à fixer.
 *
 */
void C_fixerNbCorrections(C_Correction *pCorrection, unsigned int nbSource)
{
    pCorrection->nbCorrections = nbSource;
}

/**
 * \fn unsigned int C_obtenirNbCorrections(C_Correction maCorrection)
 * \brief Fonction pour obtenir l'attribut nbCorrections d'une variable de type C_Correction.
 *
 * \param maCorrection de type C_Correction.
 * \return maCorrection.nbCorrections.
 *
 */
unsigned int C_obtenirNbCorrections(C_Correction maCorrection)
{
    return maCorrection.nbCorrections;
}

/**
 * \fn void C_fixerFileDesMotsCorriges(C_Correction *pCorrection, F_File fileSource)
 * \brief Procédure pour fixer l'attribut fileDesMotsCorriges d'une variable de type C_Correction.
 *
 * \param pCorrection de type C_Correction*.
 * \param fileSource est la file des corrections à fixer.
 *
 */
void C_fixerFileDesMotsCorriges(C_Correction *pCorrection, F_File fileSource)
{
    pCorrection->fileDesMotsCorriges = fileSource;
}

/**
 * \fn F_File C_obtenirFilesDesMotsCorriges(C_Correction maCorrection)
 * \brief Fonction pour obtenir l'attribut fileDesMotsCorriges d'une variable de type C_Correction.
 *
 * \param maCorrection de type C_Correction.
 * \return maCorrection.fileDesMotsCorriges.
 *
 */
F_File C_obtenirFilesDesMotsCorriges(C_Correction maCorrection)
{
    return maCorrection.fileDesMotsCorriges;
}

/**
 * \fn void C_fixerMotACorriger(C_Correction *pCorrection, char *motSource)
 * \brief Procédure pour fixer l'attribut mot à corriger d'une variable de type C_Correction.
 *
 * \param pCorrection de type C_Correction*.
 * \param motSource est le mot à corriger à fixer.
 *
 */
void C_fixerMotACorriger(C_Correction *pCorrection, char *motSource)
{
    pCorrection->motACorriger = motSource;
}

/**
 * \fn char *C_obtenirMotACorriger(C_Correction maCorrection)
 * \brief Fonction pour obtenir l'attribut motACorriger d'une variable de type C_Correction.
 *
 * \param maCorrection de type C_Correction.
 * \return maCorrection.motACorriger.
 *
 */
char *C_obtenirMotACorriger(C_Correction maCorrection)
{
    return maCorrection.motACorriger;
}

/**
 * \fn void CO_fixerDico(CO_CorrecteurOrthographique *pCorrecteur, D_Dictionnaire dicoSource)
 * \brief Procédure pour fixer l'attribut dico d'une variable de type C_CorrecteurOrthographique.
 *
 * \param pCorrecteur de type CO_CorrecteurOrthographique*.
 * \param dicoSource est le dictionnaire à fixer.
 *
 */
void CO_fixerDico(CO_CorrecteurOrthographique *pCorrecteur, D_Dictionnaire dicoSource)
{
    pCorrecteur->dico = dicoSource;
}

/**
 * \fn D_Dictionnaire CO_obtenirDico(CO_CorrecteurOrthographique correcteur)
 * \brief Fonction pour obtenir l'attribut dico d'une variable de type CO_CorrecteurOrthographique.
 *
 * \param correcteur de type CO_CorrecteurOrthographique.
 * \return correcteur.dico.
 *
 */
D_Dictionnaire CO_obtenirDico(CO_CorrecteurOrthographique correcteur)
{
    return correcteur.dico;
}

/**
 * \fn C_Correction *C_correction(char *monMot, unsigned int nbCorrections)
 * \brief Initialisation d'une variable de type C_Correction.
 *
 * \param monMot est le mot à corriger.
 * \param nbCorrections est le nombre de corrections.
 * \return pCorrection est un pointeur vers la correction en question.
 */
C_Correction *C_correction(char *monMot, unsigned int nbCorrections)
{
    C_Correction *pCorrection = (struct C_Correction *)malloc(TAILLE_CORRECTION);
    C_fixerMotACorriger(pCorrection, monMot);
    C_fixerFileDesMotsCorriges(pCorrection, NULL);
    C_fixerNbCorrections(pCorrection, nbCorrections);
    return pCorrection;
}

/**
 * \fn void CO_fixerFileACorriger(CO_CorrecteurOrthographique *pCorrecteur, F_File fileSource)
 * \brief Procédure pour fixer l'attribut fileACorriger d'une variable de type C_CorrecteurOrthographique.
 *
 * \param pCorrecteur de type CO_CorrecteurOrthographique*.
 * \param fileSource est la file à corriger à fixer.
 *
 */
void CO_fixerFileACorriger(CO_CorrecteurOrthographique *pCorrecteur, F_File fileSource)
{
    pCorrecteur->fileACorriger = fileSource;
}

/**
 * \fn F_File CO_obtenirFileACorriger(CO_CorrecteurOrthographique correcteur)
 * \brief Fonction pour obtenir l'attribut fileACorriger d'une variable de type CO_CorrecteurOrthographique.
 *
 * \param correcteur de type CO_CorrecteurOrthographique.
 * \return correcteur.fileACorriger.
 *
 */
F_File CO_obtenirFileACorriger(CO_CorrecteurOrthographique correcteur)
{
    return correcteur.fileACorriger;
}

/**
 * \fn void CO_fixerFileDesCorrections(CO_CorrecteurOrthographique *pCorrecteur, F_File fileSource)
 * \brief Procédure pour fixer l'attribut fileDesCorrections d'une variable de type C_CorrecteurOrthographique.
 *
 * \param pCorrecteur de type CO_CorrecteurOrthographique*.
 * \param fileSource est la file des corrections à fixer.
 *
 */
void CO_fixerFileDesCorrections(CO_CorrecteurOrthographique *pCorrecteur, F_File fileSource)
{
    pCorrecteur->fileDesCorrections = fileSource;
}

/**
 * \fn F_File CO_obtenirFileDesCorrections(CO_CorrecteurOrthographique correcteur)
 * \brief Fonction pour obtenir l'attribut fileDesCorrections d'une variable de type CO_CorrecteurOrthographique.
 *
 * \param correcteur de type CO_CorrecteurOrthographique.
 * \return correcteur.fileDesCorrections.
 *
 */
F_File CO_obtenirFileDesCorrections(CO_CorrecteurOrthographique correcteur)
{
    return correcteur.fileDesCorrections;
}

/**
 * \fn CO_CorrecteurOrthographique *CO_correcteur(D_Dictionnaire dico, F_File fileACorriger)
 * \brief fonction pour initialiser un pointeur vers une variable de type CO_CorrecteurOrthographique.
 *
 * \param dico de type D_Dictionnaire.
 * \param fileACorriger de type F_File contient des mots de type char*.
 * \return CO_CorrecteurOrthographique* le pointeur vers la variable de type CO_CorrecteurOrthographique initialisée.
 */
CO_CorrecteurOrthographique *CO_correcteur(D_Dictionnaire dico, F_File fileACorriger)
{
    CO_CorrecteurOrthographique *pCorrecteur = (struct CO_CorrecteurOrthographique *)malloc(TAILLE_CORRECTEUR);
    CO_fixerDico(pCorrecteur, dico);
    CO_fixerFileDesCorrections(pCorrecteur, NULL);
    CO_fixerFileACorriger(pCorrecteur, fileACorriger);
    return pCorrecteur;
}

/**
 * \fn F_File CO_strategieRemplacerLettre(D_Dictionnaire dico, char *monMot)
 * \brief Fonction permettant d'utiliser la stratégie Remplacer Lettre et de trouver les mots existants suite à la transformation.
 * \param dico de type D_Dictionnaire.
 * \param monMot de type char*.
 * \return resultat, la liste des mots corrigés potentiels.
 */
F_File CO_strategieRemplacerLettre(D_Dictionnaire dico, char *monMot)
{
    unsigned int i;
    F_File resultat;
    char lettre;
    char *motTemp;

    resultat = F_file();
    for (i = 0; i < M_longueur(monMot); i++)
    {
        for (lettre = 'a'; lettre <= 'z'; lettre++)
        {
            motTemp = (char *)malloc(TAILLE_MOT);
            strcpy(motTemp, monMot);
            CO_remplacerLettre(motTemp, i, lettre);
            if (D_motPresent(dico, motTemp))
            {
                F_enfiler(&resultat, (void **)&motTemp, TAILLE_MOT);
            }
            else
            {
                free(motTemp);
            }
        }
    }
    return resultat;
}

/**
 * \fn F_File CO_strategieInverserLettre(D_Dictionnaire dico, char *monMot)
 * \brief Fonction permettant d'utiliser la stratégie Inverser Lettre et de trouver les mots existants suite à la transformation.
 * \param dico de type D_Dictionnaire.
 * \param monMot de type char*.
 * \return resultat, la liste des mots corrigés potentiels.
 */
F_File CO_strategieInverserLettre(D_Dictionnaire dico, char *monMot)
{
    unsigned int i;
    F_File resultat;
    char *motTemp;

    resultat = F_file();
    for (i = 0; i < M_longueur(monMot) - 1; i++)
    {
        motTemp = (char *)malloc(TAILLE_MOT);
        strcpy(motTemp, monMot);
        CO_inverserDeuxLettresConsecutives(motTemp, i);
        if (D_motPresent(dico, motTemp))
        {
            F_enfiler(&resultat, (void **)&motTemp, TAILLE_MOT);
        }
        else
        {
            free(motTemp);
        }
    }
    return resultat;
}

/**
 * \fn F_File CO_strategieDecomposer(D_Dictionnaire dico, char *monMot)
 * \brief Fonction permettant d'utiliser la stratégie Décomposer et de trouver les mots existants suite à la transformation.
 * \param dico de type D_Dictionnaire.
 * \param monMot de type char*.
 * \return resultat, la liste des mots corrigés potentiels.
 */
F_File CO_strategieDecomposer(D_Dictionnaire dico, char *monMot)
{
    unsigned int i;
    F_File resultat;
    char *motDecompose1, *motDecompose2;

    resultat = F_file();
    for (i = 1; i < M_longueur(monMot); i++)
    {
        motDecompose1 = (char *)malloc(TAILLE_MOT);
        motDecompose2 = (char *)malloc(TAILLE_MOT);
        CO_decomposerMotEnDeux(monMot, i, motDecompose1, motDecompose2);
        if (D_motPresent(dico, motDecompose1) && D_motPresent(dico, motDecompose2))
        {
            F_enfiler(&resultat, (void **)&motDecompose1, TAILLE_MOT);
            F_enfiler(&resultat, (void **)&motDecompose2, TAILLE_MOT);
        }
        else
        {
            free(motDecompose1);
            free(motDecompose2);
        }
    }
    return resultat;
}

/**
 * \fn F_File CO_strategieSupprimerLettre(D_Dictionnaire dico, char *monMot)
 * \brief Fonction permettant d'utiliser la stratégie Supprimer Lettre et de trouver les mots existants suite à la transformation.
 * \param dico de type D_Dictionnaire.
 * \param monMot de type char*.
 * \return resultat, la liste des mots corrigés potentiels.
 */
F_File CO_strategieSupprimerLettre(D_Dictionnaire dico, char *monMot)
{
    unsigned int i;
    F_File resultat;
    char *motTemp;

    resultat = F_file();
    for (i = 0; i < M_longueur(monMot) - 1; i++)
    {
        motTemp = (char *)malloc(TAILLE_MOT);
        strcpy(motTemp, monMot);
        CO_supprimerLettre(motTemp, i);
        if (D_motPresent(dico, motTemp))
        {
            F_enfiler(&resultat, (void **)&motTemp, TAILLE_MOT);
        }
        else
        {
            free(motTemp);
        }
    }
    return resultat;
}

/**
 * \fn F_File CO_strategieInsererLettre(D_Dictionnaire dico, char *monMot)
 * \brief Fonction permettant d'utiliser la stratégie Insérer Lettre et de trouver les mots existants suite à la transformation.
 * \param dico de type D_Dictionnaire.
 * \param monMot de type char*.
 * \return resultat, la liste des mots corrigés potentiels.
 */
F_File CO_strategieInsererLettre(D_Dictionnaire dico, char *monMot)
{
    unsigned int i;
    F_File resultat;
    char lettre;
    char *motTemp;

    resultat = F_file();
    for (i = 0; i <= M_longueur(monMot); i++)
    {
        for (lettre = 'a'; lettre <= 'z'; lettre++)
        {
            motTemp = (char *)malloc(TAILLE_MOT);
            strcpy(motTemp, monMot);
            CO_insererLettre(motTemp, i, lettre);
            if (D_motPresent(dico, motTemp))
            {
                F_enfiler(&resultat, (void **)&motTemp, TAILLE_MOT);
            }
            else
            {
                free(motTemp);
            }
        }
    }
    return resultat;
}

/**
 * \fn F_File CO_corrigerUnMot(D_Dictionnaire dico, char *monMot)
 * \brief Fonction permettant d'utiliser toutes les stratégies définies sur un mot et de trouver tous les mots existants suite aux transformations.
 * \param dico de type D_Dictionnaire.
 * \param monMot de type char*.
 * \return fileDUneCorrection, la liste des mots corrigés potentiels.
 */
F_File CO_corrigerUnMot(D_Dictionnaire dico, char *monMot)
{
    F_File fileDUneCorrection, FileTemp;
    fileDUneCorrection = F_file();
    FileTemp = CO_strategieInsererLettre(dico, monMot);
    while (FileTemp != NULL)
    {
        char *motFile = F_obtenirElement(FileTemp, 255 * sizeof(char));
        F_enfiler(&fileDUneCorrection, (void **)&motFile, 255 * sizeof(char));
        F_defiler(&FileTemp);
    }
    FileTemp = CO_strategieSupprimerLettre(dico, monMot);
    while (FileTemp != NULL)
    {
        char *motFile = F_obtenirElement(FileTemp, 255 * sizeof(char));
        F_enfiler(&fileDUneCorrection, (void **)&motFile, 255 * sizeof(char));
        F_defiler(&FileTemp);
    }
    FileTemp = CO_strategieRemplacerLettre(dico, monMot);
    while (FileTemp != NULL)
    {
        char *motFile = F_obtenirElement(FileTemp, 255 * sizeof(char));
        F_enfiler(&fileDUneCorrection, (void **)&motFile, 255 * sizeof(char));
        F_defiler(&FileTemp);
    }
    FileTemp = CO_strategieInverserLettre(dico, monMot);
    while (FileTemp != NULL)
    {
        char *motFile = F_obtenirElement(FileTemp, 255 * sizeof(char));
        F_enfiler(&fileDUneCorrection, (void **)&motFile, 255 * sizeof(char));
        F_defiler(&FileTemp);
    }
    FileTemp = CO_strategieDecomposer(dico, monMot);
    while (FileTemp != NULL)
    {
        char *motFile = F_obtenirElement(FileTemp, 255 * sizeof(char));
        F_enfiler(&fileDUneCorrection, (void **)&motFile, 255 * sizeof(char));
        F_defiler(&FileTemp);
    }
    return fileDUneCorrection;
}

/**
 * \fn void CO_corrigerUneChaine(CO_CorrecteurOrthographique *pCorrecteur)
 * \brief Procédure permettant de corriger une chaîne de mot et de stocker la correction dans l'attribut fileDesCorrections d'une variable de type CO_CorrecteurOrthographique.
 * \param pCorrecteur de type CO_CorrecteurOrthographique*.
 */
void CO_corrigerUneChaine(CO_CorrecteurOrthographique *pCorrecteur)
{
    char *motACorriger;
    D_Dictionnaire dico;
    C_Correction *pCorrection;
    F_File fileACorriger = F_file();
    F_File fileDesMotsCorriges = F_file();
    F_File fileDesCorrections = F_file();

    dico = CO_obtenirDico(*pCorrecteur);
    fileACorriger = CO_obtenirFileACorriger(*pCorrecteur);
    while (!F_estVide(fileACorriger))
    {
        motACorriger = F_obtenirElement(fileACorriger, TAILLE_MOT);
        F_defiler(&fileACorriger);
        fileDesMotsCorriges = CO_corrigerUnMot(dico, motACorriger);
        pCorrection = C_correction(motACorriger, F_nbElements(fileDesMotsCorriges));
        C_fixerFileDesMotsCorriges(pCorrection, fileDesMotsCorriges);
        F_enfiler(&fileDesCorrections, (void **)&pCorrection, TAILLE_CORRECTION);
    }
    CO_fixerFileDesCorrections(pCorrecteur, fileDesCorrections);
}

/**
 * @fn F_File CO_entreeStandardVersFile(void)
 * \brief Fonction qui sépare les mots de l'entrée standard et qui renvoit uniquement les mots valides dans une file.
 *
 * @return F_File
 */
F_File CO_entreeStandardVersFile(void)
{
    char *chaineDeMots = (char *)malloc(TAILLE_MAX_CHAINE);
    char *mot = (char *)malloc(TAILLE_MOT);
    F_File maFile = F_file();
    scanf("%[^\n]", chaineDeMots);
    unsigned int i = 0;
    while (i < M_longueurCDC(chaineDeMots))
    {
        unsigned int j = 0;
        while (j < 254 && i < M_longueurCDC(chaineDeMots) && chaineDeMots[i] != ' ')
        {
            mot[j] = chaineDeMots[i];
            j++;
            i++;
        }
        mot[j] = '\0';
        char *motValide = M_creerMot(mot);
        if (motValide != NULL)
        {
            // printf("\n\n<%s>\n\n", motValide);
            F_enfiler(&maFile, (void **)&motValide, TAILLE_MOT);
        }
        i++;
    }
    free(mot);
    free(chaineDeMots);
    return maFile;
}

/**
 * @fn void CO_afficherMot(C_Correction correction, D_Dictionnaire dico, unsigned int numeroDeLACorrection)
 * \brief Procédure qui affiche la correction d'un mot si il est faux.
 *
 * @param correction de type C_Correction, la correction à afficher.
 * @param dico de type D_Dictionnaire, le dictionnaire de référence.
 * @param numeroDeLACorrection de type unsigned int, l'ordre du mot dans la chaine entrée.
 */
void CO_afficherMot(C_Correction correction, D_Dictionnaire dico, unsigned int numeroDeLACorrection)
{
    F_File fileDesMotCorriges = C_obtenirFilesDesMotsCorriges(correction);
    char *motACorriger = C_obtenirMotACorriger(correction);
    unsigned int afficher = 1;
    if (D_motPresent(dico, motACorriger))
    {
        printf("*");
        afficher = 0;
    }
    else
    {
        printf("& %s : %i : %i :", motACorriger, numeroDeLACorrection, C_obtenirNbCorrections(correction));
    }
    while (!F_estVide(fileDesMotCorriges))
    {
        char *motFile = F_obtenirElement(fileDesMotCorriges, TAILLE_MOT);
        if (afficher)
        {
            printf(" %s", motFile);
        }
        free(motFile);
        F_defiler(&fileDesMotCorriges);
    }
    free(motACorriger);
}

/**
 * @fn void CO_afficherCorrection(D_Dictionnaire dicoSource)
 * \brief Fonction qui affiche toutes les corrections de toute les mots entrés.
 *
 * @param correcteur de type CO_CorrecteurOrthographique, le correcteur contenant toutes les corrections.
 */
void CO_afficherCorrection(D_Dictionnaire dicoSource)
{
    F_File fileACorriger = F_file();
    fileACorriger = CO_entreeStandardVersFile();
    CO_CorrecteurOrthographique *pCorrecteur = CO_correcteur(dicoSource, fileACorriger);
    CO_corrigerUneChaine(pCorrecteur);
    F_File fileDesCorrectionsDuCorrecteur = CO_obtenirFileDesCorrections(*pCorrecteur);
    unsigned int numeroDeLACorrection = 1;
    while (!F_estVide(fileDesCorrectionsDuCorrecteur))
    {
        C_Correction *pCorrection = F_obtenirElement(fileDesCorrectionsDuCorrecteur, TAILLE_CORRECTION);
        CO_afficherMot(*pCorrection, dicoSource, numeroDeLACorrection);
        free(pCorrection);
        F_defiler(&fileDesCorrectionsDuCorrecteur);

        numeroDeLACorrection++;
        printf("\n");
    }
    D_liberer(&dicoSource);
    free(pCorrecteur);
}
