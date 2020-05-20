#############################################################################
# Fichier Makefile 
# utilisation des variables internes $< $@ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond à toutes les dépendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'édition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = dimacs res_dimacs 3_SAT


#############################################################################
# definition des regles
#############################################################################

########################################################
# la règle par défaut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
fonctions.o : fonctions.c fonctions.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module fonctions"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

dimacs.o : dimacs.c fonctions.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module dimacs"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
res_dimacs.o : res_dimacs.c fonctions.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module res_dimacs"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

3-SAT.o : 3_SAT.c fonctions.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module 3_SAT"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
########################################################
# regles explicites de creation des executables

dimacs : dimacs.o fonctions.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

res_dimacs : res_dimacs.o fonctions.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

3_SAT : 3_SAT.o fonctions.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@


# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
