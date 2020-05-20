#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Cellule_ {
		int n;
		struct Cellule_ *suiv ;
} Cellule ;

typedef struct Liste_ {
	unsigned int taille ;
	Cellule *tete ;
	Cellule *fin ;
} Liste ;



//partie dimacs


//regle 1 represente l'unicite du chiffre dans chaque czse , ligne et colonne

//ecrit les clauses de la regle 1(2eme partie) dans le fichier g ( implication de gauche a droite ) 
void regle_1_2(FILE *g,int L) ;

//ecrit les clauses de la regle 1(1ere partie) dans le fichier g ( implication de gauche a droite ) 
void regle_1_1(FILE *g,int L) ;

//ecrit les clauses de la regle 2 dans le fichier g avec case[i1][j1] < case [i2][j2]
void regle_2(FILE *g,int i1,int j1,int i2,int j2 ,int L)  ;

//regle pour que chaque case soit rempli 
void regle_3(FILE *g,int L) ;

//verifi la valeur de i 
void verif(int i ,int L) ;




//partie res_dimacs



//initialise le tableau a des 0 partout 
void init(int *tab,int L) ;

//affiche le les cases du tableau ligne par ligne  obtenu dans le fichier g
void afficher_fichier(FILE *g,int *tab,int L) ;

//soit g le fichier contenuant le resultat du solveur donc on rempli le tableau et on envoit 1 si c'est satisfaisable et on renvoie 0 sinon 
int lect_sol(FILE *g,int *tab,int L) ;



//partie 3-SAT

Liste init_liste() ;

Cellule *creer_cellule(int i) ; 

void supprimer_liste(Liste *l) ;

void ajout_entier(Liste *l , int i) ; 

//l est la liste qui contient les litteraux d'une clause , donc cette fonction printe selon le cas son equivalent dans le fichier g 
int sat_3(Liste l , FILE *g,int *cpt,int n_clauses);










