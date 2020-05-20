#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"fonctions.h"



int main(int argc , char *argv[]) {
	FILE *f ,*g;
	int L , i, j ,n ,point , couple ,cpt ,i2,j2,n_clauses;
	 


	if ( argc != 3 )  {
		printf("entree : <nom_fichier> <taille> \n" ) ;
		exit(1) ;
	}

	f = fopen(argv[1],"r") ; 
	g = fopen("dimacs.txt","w") ;


	if( f==NULL || g == NULL ) { printf("erreur fichier \n") ; exit(1) ;  }

	L = atoi(argv[2]) ;
	fscanf(f,"%d",&point) ; 
	fscanf(f,"%d",&couple) ; 
	
	if ( L<0 ||  L>9 ) {
		printf("Erreur , 0<longueur <= 9 \n ") ;
		exit(2) ;
	}
  	fprintf(g,"c Tableau avec %d cases \n",L) ;
  	n_clauses = (pow(L,3)*(1+3*(L-1)) ) + couple*( 2*(L-1)+2 ) + point + pow(L,2) ;
  	fprintf(g,"p cnf %d%d%d %d \n",L,L,L,n_clauses) ;
 
 
	cpt = 0 ;
	while(!feof(f) && cpt<point) {
		fscanf(f,"%d %d %d ",&i,&j,&n) ;
		verif(i,L) ;
		verif(j,L) ;
		verif(n,L) ;
		fprintf(g,"%d%d%d 0\n",i,j,n) ;
		cpt++ ;
	}

	if(cpt<point) { printf("Erreur format fichier \n") ; }

	cpt = 0 ;
	while(!feof(f) && cpt<couple) {
		fscanf(f,"%d %d %d %d ",&i,&j,&i2,&j2) ;
		verif(i,L) ;
		verif(j,L) ;
		verif(i2,L) ;
		verif(j2,L) ;
		regle_2(g,i,j,i2,j2 ,L)  ;
		cpt++ ;
	}

	if(cpt<point) { printf("Erreur format fichier \n") ; }

	
	regle_1_1(g,L) ;
	regle_1_2(g,L) ;
	
	regle_3(g,L) ; 
		
	fclose(f) ;
	fclose(g) ;

	return 0 ;
}
	
						
	
	
