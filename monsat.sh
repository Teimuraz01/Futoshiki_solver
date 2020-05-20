#!/bin/bash

if [ $# -ne 2 ]
then 
	echo nombre d\'arguments invalide \: "<fichieer_entree> <taille_tableau>"
	exit 1 
fi


if [ ! -r $1 ]
then
	echo erreur de lecture "du" fichier en argument
	exit 1
fi



./dimacs $1 $2
if [ $? -ne 0 ]  #si la lecture est mauvaise
then 
	exit 1
fi
./3_SAT dimacs.txt
minisat dimacs.txt_3_SAT sol_dimacs.txt
./res_dimacs sol_dimacs.txt $2
python3.6 interface_graphique.py

