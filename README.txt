
Compilation :
	-pour compiler executez "make" 
	-pour installer python3.6 : "sudo apt-get install python3.6"
	-pour installer "tkinter" : "sudo apt-get install python3.6-tk"

Execution :
	Si votre SAT solver s'appele "minisat"
		- "./monsat.sh <fichier_entree> <taille_grille> "
	sinon :
		-modifier ligne 24 dans le fichier "monsat.sh"
	
	A la fin du programme fermer la fenetre graphique pour terminer .

Tests :
	4 fichier tests : 
		Satisafaisable :
			-entree_grille_4.txt
			-entree_grille_6.txt
			-entree_grille_5.txt
		Insatisfaisable :
			-entree_grille_faux_4.txt



Le format du fichier_entree en argument est : 
	- le nombre de case remplies par hypothese , le nombre des couples "plus petit" par hypothese , 
	- puis indice ligne i ,indice  colonne j , la valeur n, de chaque case remplie ,( separés par un espace) ligne par ligne
	- enfin les couples ( par ex si case[i][j] < case[i'][j'] , on ecrit  i j i' j' ) ligne par ligne
	
	tous les nombres sont des entiers positives et separees par des espaces ou des retours a la ligne 
	et 0<taille<=9 
	1<=i<=taille 
	1<=j<=taille  
	1<=n<=taille


Note : ne pas ecrire des fichiers appelé : "fichier.txt" "dimacs.txt" "dimacs.txt_3_SAT" "sol_dimacs.txt" (ce sont des fichiers produits par le programme ) 
