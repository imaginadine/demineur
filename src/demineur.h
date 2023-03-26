/*! \file demineur.h
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 09/12/2021
 *  \brief fichier d'en-tête de demineur.c
 */

#ifndef __DEMINEUR_H_
#define __DEMINEUR_H_

 /* Inclusion des entetes de librairie */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*!
    \def ERREUR_SAISIE
    Code d'erreur associé à la saisie
*/
#define ERREUR_SAISIE -1


/*! \struct case
 * Structure pour la manipulation d'une case de démineur
 */

typedef struct caseD caseD;
struct caseD{
    int int_mine; /*!< présence de mine : 1 si oui, 0 sinon*/
    int int_decouvert; /*!< case découverte : 1 si oui, 0 sinon*/
    int int_drapeau; /*!< case marquée : 1 si oui, 0 sinon*/
    char char_symbole; /*!< ce qui doit être affiché*/
    int int_nbMines; /*!< nombre de mines voisines à la case*/
};


/**
 *  \fn int saisieEntier(const char* texte)
 *  \author Legrand Amandine <legrandama@eisti.eu>
 *  \version 0.1
 *  \date 06/12/2021
 *
 *  \brief vérifie que les valeurs entrées sont des chiffres entiers
 *
 * \remarks
 */
int saisieEntier(const char* texte);

/*! \fn caseD** creeTab(int int_n, int int_m)
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 09/12/2021
 *
 *  \brief crée un tableau dynamique 2D de cases en allouant la mémoire
 *
 */

caseD** creeTab(int int_n, int int_m);

/*! \fn void supprTab(caseD** ppcaseD_tab, int int_n)
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 09/12/2021
 *
 *  \brief supprime un tableau dynamique 2D en libérant l'espace mémoire
 *
 */

void supprTab(caseD** ppcaseD_tab, int int_n);

/*! \fn void afficheDTab(caseD** ppint_tab, int int_n, int int_m)
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 09/12/2021
 *
 *  \brief affiche le plateau de jeu
 *
 *  \remarks 
 */
void afficheDTab(caseD** ppcaseD_tab, int int_n, int int_m);

/*! \fn void initialisation(caseD** ppcaseD_tab, int int_n, int int_m, int int_nbMines)
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 09/12/2021
 *
 *  \brief initialise le plateau en mettant les mines .......
 *
 *  \remarks 
 */
void initialisation(caseD** ppcaseD_tab, int int_n, int int_m, int int_nbMines);

/*! \fn int compteMines(caseD** ppcaseD_tab, int int_x, int int_y, int int_n, int int_m)
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 12/12/2021
 *
 *  \brief compte le nombre de mines adjacentes à chaque case
 *
 *  \remarks 
 */
int compteMines(caseD** ppcaseD_tab, int int_x, int int_y, int int_n, int int_m);

/*! \fn char symbole(caseD** ppcaseD_tab, int int_x, int int_y, int int_n, int int_m)
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 12/12/2021
 *
 *  \brief renvoie le symbole qui doit être affiché
 *
 *  \remarks 
 */
char symbole(caseD** ppcaseD_tab, int int_x, int int_y, int int_n, int int_m);

/*! \fn void decouvrir(caseD** ppcaseD_tab, int int_x, int int_y, int int_n, int int_m)
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 12/12/2021
 *
 *  \brief découvre la case
 *
 *  \remarks si la case n'a pas de mines adjacentes, les cases autour d'elle sont aussi découvertes
 */
void decouvrir(caseD** ppcaseD_tab, int int_x, int int_y, int int_n, int int_m);

/*! \fn int compteMinesTotal(caseD** ppcaseD_tab, int int_n, int int_m, int int_nbMines)
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 12/12/2021
 *
 *  \brief compte le nombre de mines total qui n'ont pas été découvertes, sous l'hypothèse que les drapeaux soient justes
 *
 *  \remarks 
 */
int compteMinesTotal(caseD** ppcaseD_tab, int int_n, int int_m, int int_nbMines);

/*! \fn int victoire(caseD** ppcaseD_tab, int int_n, int int_m)
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 12/12/2021
 *
 *  \brief vérifie si toutes les cases sont découvertes
 *
 *  \return 1 si le joueur a découvert toutes les cases et donc gagné, 0 sinon
 */
int victoire(caseD** ppcaseD_tab, int int_n, int int_m);

/*! \fn int tourDeJeu(caseD** ppcaseD_tab, int int_n, int int_m, int int_nbMines)
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 12/12/2021
 *
 *  \brief tour du joueur : demande de la ligne et colonne de la case, puis découverte ou non de celle-ci
 *
 *  \remarks 
 */
int tourDeJeu(caseD** ppcaseD_tab, int int_n, int int_m, int int_nbMines);

#endif