#création des variables
CC=gcc -Wall #compilation
CP=cp
RM=rm -f #suppression des fichiers objets et exécutables
ZIP=tar -cvzf legrandama-tp.zip
SRC=$(wildcard $(srcdir)*.c) #fichiers .c
HEAD=$(wildcard $(srcdir)*.h) #fichiers.h
OBJ=$(subst $(srcdir), $(bindir), $(SRC:.c=.o)) #fichiers .o
PROG=demineur #nom du programme
srcdir=src/#dossier contenant les fichiers .c et .h
bindir=bin/#dossier contenant les fichiers .o
docdir=doc/#dossier contenant la documentation du programme (doxyfile)
savedir=save/#dossier contenant une sauvegarde des fichiers source

all : $(PROG)

$(PROG) : $(OBJ)
	$(CC) $^ -o $@ -lm

./$(bindir)%.o : ./$(srcdir)%.c
	$(CC) -c $^ -o $@

.PHONY : clean

#suppression si on écrit make clean dans le terminal
clean :
	$(RM) $(OBJ) $(PROG)

.PHONY : save

#sauvegarde des fichiers dans le répertoire save
save :
	$(CP) $(SRC) $(HEAD) ./$(savedir)

.PHONY : restore

#copie des fichiers de sauvegarde dans le réperoire src
restore :
	$(CP) $(savedir)* $(srcdir)

.PHONY : give

#crée l'archive qui contient tous les fichiers nécessaires à la génération du projet
give :
	$(ZIP) $(srcdir) $(bindir) $(docdir) $(savedir)
