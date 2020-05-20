#include<stdio.h>
#include<stdlib.h>
#include"fonctions.h"

int main(int argc , char *argv[]) {
	FILE *f ,*g;
	int L , res ;
	

	if ( argc != 3 )  {
		printf("entree : <nom_fichier_sat_obtenu> <taille_tableau> \n" ) ;
		exit(1) ;
	}

	f = fopen(argv[1],"r") ; 
	g = fopen("fichier.txt","w") ;

	if( f==NULL || g == NULL ) { printf("erreur fichier \n") ; exit(1) ;  }

	L = atoi(argv[2]) ;
 
 
	int *tab = (int *)malloc(L*L*sizeof(int) )  ;


	res = lect_sol(f,tab,L) ;
	
	if(res==0) {
		fprintf(g,"I") ;
		fclose(f) ;
		fclose(g) ;
		return 1 ;
	}
	else {
		afficher_fichier(g,tab,L) ;
	}


	fclose(f) ;
	fclose(g) ;
	
	return 0 ;
}
	
						
	
	
