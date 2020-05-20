#include"fonctions.h"

int main(int argc , char *argv[]) {
	FILE *f, *g , *tmp;
	int lit_max,n ;
	char *nom,ligne[256],c[1],a[3] ;
	Liste l ;
	l = init_liste() ; 
	
	if ( argc != 2 )  {
		printf("entree : <nom_fichier_dimacs> \n" ) ;
		exit(1) ;
	}	
		

	nom = (char *)malloc( (strlen(argv[1])+14)*sizeof(char) )  ;
	sprintf(nom,"%s_3_SAT",argv[1]) ; 
	
	f = fopen(argv[1],"r")  ;
	tmp = fopen("tmp.txt","w") ; 
	g = fopen(nom,"w") ; 

	if( f==NULL || g == NULL ) { printf("erreur fichier \n") ; exit(1) ;  }
	




	//Je cree un fichier temporaires contenant les clauses modifie en 3_SAT sans les 2 premières lignes ( pour savoir le nombre des variables et de clauses )

	fgets(ligne,255,f) ; 


	//fprintf(g,"c Tableau avec %d cases \n",n) ;
	
	fscanf(f,"%s %s %d %d \n",c,a,&lit_max,&n) ; 
	
	// on parcours chaque clause et on la transforme
	// on comence par 1000 pour eviter les repetitions des literaux

	fscanf(f,"%d",&n) ;
	int lit = 1000 , n_clauses = 0;  
	while(!feof(f)) {
		while(n != 0) {
			ajout_entier(&l,n) ; 
			fscanf(f,"%d",&n) ;
		}
		n_clauses = sat_3(l,tmp,&lit,n_clauses) ; 
		supprimer_liste(&l) ;
		fscanf(f,"%d",&n) ;
	}
	
	fclose(tmp) ; 
	
	//maintenant on a le nombre de clauses et la valeur du literal max donc on peut ecrire le fichier DIMACS
	
	fprintf(g,"c Tableau avec %d cases \n",lit_max % 10 ) ;
	fprintf(g,"p cnf %d %d \n",lit-1,n_clauses) ; 
	tmp = fopen("tmp.txt","r") ; 

	fgets(ligne,255,tmp) ;
	
	while(!feof(tmp)) {
		fprintf(g,"%s",ligne) ;
		fgets(ligne,255,tmp) ;
	}

	

	

	
	fclose(tmp) ; 	
	remove("tmp.txt") ;
	fclose(f) ; 
	fclose(g) ;
	return 0 ;
}
			
		
	
