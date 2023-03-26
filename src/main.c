/*! \file main.c
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 09/12/2021
 *  \brief programme principal : TP9 - Démineur
 */

 /* Inclusion des entetes de librairie */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "demineur.h"

/*! \fn int main (int argc, char** argv)
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 09/12/2021
 *
 *  \brief Fonction principale
 * 
 *
 * \param argc : Nombre d'argument
 * \param argv : Tableau des arguments
 * \return 0   : le programme doit se terminer normalement
 *
 * \remarks 
 */

int main (int argc, char** argv) 
{
    int int_n; /*nb de lignes*/
    int int_m; /*nb de colonnes*/
    int int_nbMines; /*nb de mines*/
    caseD** ppcaseD_tab; /*tableau dynamique de cases*/
    int int_boum; /*1 si la case est une bombe, 0 sinon*/
    int i; /*indice de boucle*/
    int j; /*indice de boucle*/
    time_t time_debut; /*début du temps*/
    time_t time_fin; /*fin du temps*/

    /*la partie se prépare*/
    int_boum=0;
    do{
        int_n=saisieEntier("Combien voulez-vous de lignes ?\n");
        int_m=saisieEntier("Combien voulez-vous de colonnes ?\n");
        int_nbMines=saisieEntier("Et combien voulez-vous de mines ?\n");
    }while((int_n<=0)||(int_m<=0)||(int_nbMines<=0)||(int_nbMines>(int_n*int_m))); /*refaire tant que les 3 variables ne sont pas correctes*/

    ppcaseD_tab=creeTab(int_n,int_m);
    initialisation(ppcaseD_tab, int_n, int_m, int_nbMines);
    afficheDTab(ppcaseD_tab,int_n,int_m);

    /*la partie se joue*/
    time_debut=time(NULL);
    while((victoire(ppcaseD_tab, int_n, int_m)==0)&&(int_boum==0)){
       printf("Il reste encore %d mine(s)\n", compteMinesTotal(ppcaseD_tab,int_n,int_m, int_nbMines)); 
       int_boum=tourDeJeu(ppcaseD_tab,int_n,int_m, int_nbMines);
    }
    time_fin=time(NULL);
    /*la partie se finit*/
    if(int_boum==1){
        /*perdu car tombé sur une mine*/
        printf("Perdu ! Explosion !\n");
        /*affichage de tout le plateau*/
        for(i=0;i<int_n;i++){
            for(j=0;j<int_m;j++){
                ppcaseD_tab[i][j].int_decouvert=1;
            }
        }
        afficheDTab(ppcaseD_tab,int_n,int_m);
    } else{
        /*victoire*/
            printf("Bravo ! Vous avez gagné ! Temps mis : %f secondes\n", difftime(time_fin, time_debut));
    }
    
    /*libération de l'espace mémoire*/
    supprTab(ppcaseD_tab,int_n);

    /* Fin du programme, Il se termine normalement, et donc retourne 0 */
	return (0);
}