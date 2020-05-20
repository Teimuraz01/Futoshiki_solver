#include"fonctions.h"

void init(int *tab,int L) {
		int i , j ; 
		for(i=0;i<L;i++) {
			for(j=0;j<L;j++){
				*( (tab+i*L) + j ) = 0 ; 
			}
		}
}

void verif(int i, int L) {
	if(i<1 || i>L)  {
		printf("Erreur, entier mal defini \n" ) ;
		exit(1) ; 
	}
}

void regle_1_2(FILE *g,int L) {
		int i,j,n,tmp ;

		for(i=1;i<=L;i++) {
			for(j=1;j<=L;j++) {
				for(n=1;n<=L;n++) {
					for(tmp=1;tmp<=L;tmp++) {
						if(tmp!=j) 
							fprintf(g,"-%d%d%d -%d%d%d 0 \n",i,j,n,i,tmp,n) ;
						if(tmp!=i)
							fprintf(g,"-%d%d%d -%d%d%d 0 \n",i,j,n,tmp,j,n) ;
						if(tmp!=n)
							fprintf(g,"-%d%d%d -%d%d%d 0 \n",i,j,n,i,j,tmp) ; 
					}
				}
			}
		}					
}

void regle_1_1(FILE *g,int L){
		int i,j,n,tmp ;
		
		for(i=1;i<=L;i++) {
			for(j=1;j<=L;j++) {
				for(n=1;n<=L;n++) {
					fprintf(g,"%d%d%d ",i,j,n) ;
					for(tmp=1;tmp<=L;tmp++) {
						if(tmp!=j) 
							fprintf(g,"%d%d%d ",i,tmp,n) ;
						if(tmp!=i)
							fprintf(g,"%d%d%d ",tmp,j,n) ;
						if(tmp!=n)
							fprintf(g,"%d%d%d ",i,j,tmp) ;
					}
					fprintf(g,"0 \n") ;
				}
			}
		}					
}

void regle_2(FILE *g,int i1,int j1,int i2,int j2 ,int L) {
		int n,tmp;

		for(n=2;n<=L;n++) {
			fprintf(g,"-%d%d%d ",i2,j2,n) ;
			for(tmp=1;tmp<n;tmp++) {
				fprintf(g,"%d%d%d ",i1,j1,tmp) ;
			}
			fprintf(g," 0 \n ") ;
			/*for(tmp=1;tmp<n;tmp++) {
				fprintf(g,"%d%d%d -%d%d%d 0 \n",i2,j2,n,i1,j1,tmp) ;
			}*/
		}


		for(n=1;n<L;n++) {
			fprintf(g,"-%d%d%d ",i1,j1,n) ;
			for(tmp=n+1;tmp<=L;tmp++) {
				fprintf(g,"%d%d%d ",i2,j2,tmp) ;
			}
			fprintf(g," 0 \n ") ;
			/*for(tmp=n+1;tmp<=L;tmp++) {
				fprintf(g,"%d%d%d -%d%d%d 0 \n",i1,j1,n,i2,j2,tmp) ;
			}*/
		}

		fprintf(g,"-%d%d%d 0\n ",i1,j1,L) ;
		fprintf(g,"-%d%d%d 0\n",i2,j2,1) ;
}


void regle_3(FILE *g,int L){
	int i,j,n ; 

	for(i=1;i<=L;i++) {
		for(j=1;j<=L;j++) {
			for(n=1;n<=L;n++) {
				fprintf(g,"%d%d%d ",i,j,n) ;
			}
			fprintf(g,"0 \n") ;
		}
	}

}




int lect_sol(FILE *g,int *tab,int L) {
	int i,j,n ; 
	char s[4] ;
		
	fscanf(g,"%s",s) ;
	if(s[0]=='U') { return 0 ; }

	fscanf(g,"%s",s) ;
	while(!feof(g) && strcmp(s,"1000")!= 0 && strcmp(s,"-1000")!= 0 ) {
		if(s[0]!='-') {	
			i = s[0] - '0'- 1 ;
			j = s[1] - '0' - 1 ;
			n = s[2] - '0' ;
			*( (tab+i*L) + j ) = n ;
		}
		fscanf(g,"%s",s) ;
	}
	return 1 ;
}


void afficher_fichier(FILE *g,int *tab,int L) {
	int i,j ;

	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			fprintf(g,"%d\n",*( (tab+i*L) + j )) ;
		}
	}
}


//3_SAT

Liste init_liste() {
	Liste l ;
	l.taille = 0 ; 
	l.tete = NULL ;
	l.fin = NULL  ;
	return l ;
}

Cellule *creer_Cellule(int i) {
	Cellule *c ;
	c = (Cellule *)malloc(sizeof(Cellule)) ;
	if(c==NULL) {
		printf("Erreur allocation impossible \n") ;
		exit(-1) ;
	}
	c->n= i ;
	c->suiv = NULL ;
	return c ;
}



void ajout_entier(Liste *l , int i) {
	Cellule *c ,*f;
	
	c = creer_Cellule(i) ;
	if(l->taille == 0) {
		l->tete = l->fin = c ;
	}
	else {
		f = l->fin ;
		f->suiv = c ;
		l->fin = c ;
	}
	l->taille++ ;
}

void supprimer_liste(Liste *l) {
	Cellule *c ;
	c = l->tete ;
	while(c!=NULL) {	
		Cellule *suiv ;
		suiv =  c->suiv ;
		free(c) ;
		c = suiv ;
	}
	l->tete=l->fin=NULL;
	l->taille=0 ;
}


int sat_3(Liste l , FILE *g,int *cpt,int n_clauses) { 
	int literal ; 
	Cellule *c , *c2 , *c3;
	literal = *cpt ;
	switch(l.taille) {
		case 1 :
			c = l.tete ;
			 
			fprintf(g,"%d %d %d 0 \n",c->n,literal,literal+1) ; 
			fprintf(g,"%d %d -%d 0 \n",c->n,literal,literal+1) ; 
			fprintf(g,"%d -%d %d 0 \n",c->n,literal,literal+1) ; 
			fprintf(g,"%d -%d -%d 0 \n",c->n,literal,literal+1) ; 
			literal = literal + 2  ;
			n_clauses = n_clauses + 4 ; 
			return n_clauses ;
		case 2 :
			c = l.tete ;
			c2 = c->suiv ; 
			fprintf(g,"%d %d %d 0 \n",c->n,c2->n,literal) ;
			fprintf(g,"%d %d -%d 0 \n",c->n,c2->n,literal) ;
			n_clauses = n_clauses + 2 ; 
			literal++ ; 
			return n_clauses ;
		case 3 : 
			c = l.tete ;
			c2 = c->suiv ; 
			c3 = c2->suiv ; 
			
			fprintf(g,"%d %d %d 0 \n",c->n,c2->n,c3->n) ;
			n_clauses++ ;
			return n_clauses ;
		default:
			c = l.tete ;
			c2 = c->suiv ; 


			fprintf(g,"%d %d %d 0 \n",c->n,c2->n,literal) ;

			l.taille = l.taille -2 ; //car on a lue 2 entier deja
			while(l.taille != 2 ) {
				c2 = c2->suiv ; 
				fprintf(g,"-%d %d ",literal,c2->n) ;
				literal++ ;
				fprintf(g,"%d 0\n",literal) ;
				l.taille-- ; 
				n_clauses++ ; 
			}
			c = c2->suiv ; 
			c2 = c->suiv ; 
			fprintf(g," -%d %d %d 0\n",literal,c->n,c2->n) ;
			literal++ ; 
			*cpt = literal ; 
			n_clauses = n_clauses + 2 ; 
			return n_clauses ;
	}
			
}














