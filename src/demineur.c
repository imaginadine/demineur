/*! \file demineur.c
 *  \author Amandine Legrand <legrandama@cy-tech.fr>
 *  \version 0.1
 *  \date 09/12/2021
 *  \brief contient toutes les fonctions pour jouer au démineur
 */

#include "demineur.h"

int saisieEntier(const char* texte)
{
	int int_retour; /*valeur de retour du scanf*/
	int int_valeur; /*entier à renvoyer*/
	char char_caractereSuivant; /*caractère à vérifier*/
	printf("%s", texte); /*affichage du message*/
	int_retour = scanf("%d", &int_valeur); /*lecture du nombre*/
	char_caractereSuivant = getchar();
    /*si le nombre n'est pas un entier...*/
	if ((int_retour == 0) || (char_caractereSuivant == '.') || (char_caractereSuivant == ',')) {
		fprintf (stderr, "Problème de saisie utilisateur \n");
        /*on quitte le programme*/
		exit(EXIT_FAILURE);
	}
	return(int_valeur);
}

caseD** creeTab(int int_n, int int_m){
    caseD** ppcaseD_tab; /*tableau dynamique d'entiers*/
    int i; /*indice de boucle*/
    /*réservation de l'espace mémoire*/
    ppcaseD_tab=malloc(int_n*sizeof(caseD*));
    for(i=0;i<int_n;i++){
        ppcaseD_tab[i]=malloc(int_m*sizeof(caseD));
    }
    /*si l'allocation a échouée*/
    if(ppcaseD_tab==NULL){
        /*on indique et on quitte*/
        fprintf(stderr, "Allocation échouée");
        exit(EXIT_FAILURE);
    }
    return(ppcaseD_tab);
}

void supprTab(caseD** ppcaseD_tab, int int_n){
    int i; /*indice de boucle*/
    for(i=0;i<int_n;i++){
        free(ppcaseD_tab[i]);
    }
    free(ppcaseD_tab);
}

char symbole(caseD** ppcaseD_tab, int int_x, int int_y, int int_n, int int_m){
    char char_res; /*caractère à afficher à l'écran pour la case*/
    /*si le symbole a un drapeau, on l'affiche*/
    if(ppcaseD_tab[int_x][int_y].int_drapeau==1){
        char_res='D';
    } else{
        /*si le symbole n'est pas découvert, on le cache*/
        if(ppcaseD_tab[int_x][int_y].int_decouvert==0){
            char_res=' ';
        } else { /*si le symbole est découvert, on l'affiche*/
            /*mine?*/
            if(ppcaseD_tab[int_x][int_y].int_mine==1){
                char_res='M';
            } else {
                if(ppcaseD_tab[int_x][int_y].int_nbMines==0){
                    char_res='.';
                } else{
                    char_res='x'; /*x = il faut afficher le nb de mines adjacentes*/
                }
            }
        }
    }
    return(char_res);
}

void afficheDTab(caseD** ppcaseD_tab, int int_n, int int_m){
    int i; /*numéro de ligne du plateau*/
    int j; /*numéro de colonne du plateau*/

    /*symboles affichés*/
    for(i=0;i<int_n;i++){
        for(j=0;j<int_m;j++){
            ppcaseD_tab[i][j].char_symbole=symbole(ppcaseD_tab, i, j, int_n, int_m);
        }
    }
    /*affichage des numéros de colonne*/
    printf("   ");
    for(j=0;j<int_m;j++){
            printf(" %d  ",j);
        }
    printf("\n"); 

    for(i=0;i<int_n;i++){
        /*affichage des lignes verticales*/
        printf("  ");
        for(j=0;j<int_m;j++){
            printf("+---");
        }
        printf("+\n");
        /*affichage des numéros de ligne*/
        printf("%d ", i);
        /*affichage de l'intérieur du plateau*/
        for(j=0;j<int_m;j++){
            if(ppcaseD_tab[i][j].char_symbole=='x'){
                printf("| %d ", ppcaseD_tab[i][j].int_nbMines); 
            } else{
                printf("| %c ", ppcaseD_tab[i][j].char_symbole); 
            }
        }
        printf("|\n");
    }
    /*affichage de la dernière ligne verticale*/
    printf("  ");
    for(j=0;j<int_m;j++){
            printf("+---");
    }
    printf("+\n");
}

void initialisation(caseD** ppcaseD_tab, int int_n, int int_m, int int_nbMines){
    int int_x; /*première coordonnée de la case*/
    int int_y; /*deuxième coordonnée de la case*/
    int int_ok; /*vérifie qu'il y ait une mine au bon endroit*/

    /*toutes les mines à 0*/
    for(int_x=0;int_x<int_n;int_x++){
        for(int_y=0;int_y<int_m;int_y++){
            ppcaseD_tab[int_x][int_y].int_mine=0;
        }
    }
    int_ok=0;
    /*initialisation du temps pour l'aléatoire*/
    srand(time(NULL));
    /*remplissage de mines*/
    do{
        int_x=(int)rand()%int_n;
        int_y=(int)rand()%int_m;
        if(ppcaseD_tab[int_x][int_y].int_mine==0){
            ppcaseD_tab[int_x][int_y].int_mine=1;
            int_ok++;
        }
    }while(int_ok<int_nbMines);
    
    for(int_x=0;int_x<int_n;int_x++){
        for(int_y=0;int_y<int_m;int_y++){
            /*comptage des mines adjacentes*/
            ppcaseD_tab[int_x][int_y].int_nbMines=compteMines(ppcaseD_tab, int_x, int_y, int_n, int_m);
            /*toutes cases découvert à 0*/
            ppcaseD_tab[int_x][int_y].int_decouvert=0;
            /*pas de drapeaux*/
            ppcaseD_tab[int_x][int_y].int_drapeau=0;
        }
    }
}

int compteMines(caseD** ppcaseD_tab, int int_x, int int_y, int int_n, int int_m){
    int i; /*indice de boucle*/
    int j; /*indice de boucle*/
    int int_cpt; /*compteur de mines proches*/
    int int_debuti; /*début de ligne pour regarder les mines*/
    int int_fini; /*fin de ligne pour regarder les mines*/
    int int_debutj; /*début de colonne pour regarder les mines*/
    int int_finj; /*fin de colonne pour regarder les mines*/

    /*initialisation du compteur à 0*/
    int_cpt=0;
    /*initialisation des débuts et fins*/
    int_debuti=int_x-1;
    int_fini=int_x+1;
    int_debutj=int_y-1;
    int_finj=int_y+1;
    /*vérificaion que ces débuts et fins existent*/
    if(int_debuti<0){
        int_debuti++;
    }
    if(int_debutj<0){
        int_debutj++;
    }
    if(int_fini==int_n){
        int_fini--;
    }
    if(int_finj==int_m){
        int_finj--;
    }
    /*on compte*/
    for(i=int_debuti;i<=int_fini;i++){
        for(j=int_debutj;j<=int_finj;j++){
            if(ppcaseD_tab[i][j].int_mine==1){
                int_cpt++;
            }
        }
    }
    return(int_cpt);
}

void decouvrir(caseD** ppcaseD_tab, int int_x, int int_y, int int_n, int int_m){
    int i; /*indice de boucle*/
    int j; /*indice de boucle*/
    int int_debuti; /*début de ligne pour regarder les mines*/
    int int_fini; /*fin de ligne pour regarder les mines*/
    int int_debutj; /*début de colonne pour regarder les mines*/
    int int_finj; /*fin de colonne pour regarder les mines*/

    /*la case est découverte*/
    ppcaseD_tab[int_x][int_y].int_decouvert=1;
    
    /*si la case n'a pas de mines adjacentes, on découvre les cases adjacentes*/
    if(ppcaseD_tab[int_x][int_y].int_nbMines==0){
        /*initialisation des débuts et fins*/
        int_debuti=int_x-1;
        int_fini=int_x+1;
        int_debutj=int_y-1;
        int_finj=int_y+1;
        /*vérificaion que ces débuts et fins existent*/
        if(int_debuti<0){
            int_debuti++;
        }
        if(int_debutj<0){
            int_debutj++;
        }
        if(int_fini==int_n){
            int_fini--;
        }
        if(int_finj==int_m){
            int_finj--;
        }
       for(i=int_debuti;i<=int_fini;i++){
            for(j=int_debutj;j<=int_finj;j++){
                /*on réitère l'opération...*/
                /*sans compter les cases déjà découvertes*/
                if(ppcaseD_tab[i][j].int_decouvert!=1){
                   decouvrir(ppcaseD_tab,i,j,int_n,int_m); 
                }
            }
        } 
    }
}

int compteMinesTotal(caseD** ppcaseD_tab, int int_n, int int_m, int int_nbMines){
    int i; /*indice de boucle*/
    int j; /* indice de boucle*/
    int int_cpt; /*compteur de mines*/

    /*initialisation du compteur*/
    int_cpt=0;
    for(i=0;i<int_n;i++){
        for(j=0;j<int_m;j++){
            /*si présence d'une mine non découverte...*/
            if(ppcaseD_tab[i][j].int_drapeau==1){
                /*on incrémente le compteur*/
                int_cpt++;
            }
        }
    }
    return(int_nbMines-int_cpt);
}

int victoire(caseD** ppcaseD_tab, int int_n, int int_m){
    int i; /*indice de boucle*/
    int j; /* indice de boucle*/
    int int_res; /*1 si la joueur a gagné, 0 sinon*/

    /*initialisation du compteur*/
    int_res=1;
    for(i=0;i<int_n;i++){
        for(j=0;j<int_m;j++){
            /*si présence d'une case non découverte*/
            if(ppcaseD_tab[i][j].int_decouvert==0){
                /*le joueur n'a pas encore gagné*/
                int_res=0;
            }
        }
    }
    return(int_res);
}

int tourDeJeu(caseD** ppcaseD_tab, int int_n, int int_m, int int_nbMines){
    int int_x; /*première coordonnée de la case*/
    int int_y; /*deuxième coordonnée de la case*/
    int int_choix; /*entier choisi pour le menu*/
    int int_res; /*1 si la case est une mine, 0 sinon*/
    
    int_res=0;

    /*récupération de la ligne*/
    do{
        int_x=saisieEntier("Quelle ligne voulez-vous choisir ?\n");
    }while((int_x<0) || (int_x>=int_n));
    /*récupération de la colonne*/
    do{
        int_y=saisieEntier("Quelle colonne voulez-vous choisir ?\n");
    }while((int_y<0) || (int_y>=int_m));
    /*si la case est déjà découverte : on affiche un message d'erreur et on recommence*/
    while(ppcaseD_tab[int_x][int_y].int_decouvert==1){
        printf("Erreur : case déjà découverte. \n");
        /*récupération de la ligne*/
        do{
            int_x=saisieEntier("Quelle ligne voulez-vous choisir ?\n");
        }while((int_x<0) || (int_x>=int_n));
        /*récupération de la colonne*/
        do{
            int_y=saisieEntier("Quelle colonne voulez-vous choisir ?\n");
        }while((int_y<0) || (int_y>=int_m));
    }

    /*menu : 2 options*/
    /*si on a utilisé tous les drapeaux*/
    if(compteMinesTotal(ppcaseD_tab,int_n,int_m,int_nbMines)==0){
        /*on ne peut que découvrir une case*/
        int_choix=2; 
    } else {
        /*sinon on laisse le choix*/
        do{
            int_choix=saisieEntier("Voulez-vous :\n1 : Déminer\n2 : Découvrir la case\n");
        } while((int_choix!=1)&&(int_choix!=2));
    }
    
    if(int_choix==1){
        /*déminer : mettre un drapeau*/
        ppcaseD_tab[int_x][int_y].int_drapeau=1;
        ppcaseD_tab[int_x][int_y].int_decouvert=1;
    } else{
        /*vérification de si la case est une mine*/
        if(ppcaseD_tab[int_x][int_y].int_mine==1){
            int_res=1;
        }else{
            /*si pas mine découvrir la case*/
            decouvrir(ppcaseD_tab,int_x,int_y,int_n,int_m); 
        }
    }

    /*affichage du plateau*/
    afficheDTab(ppcaseD_tab,int_n,int_m);

    return(int_res);
}