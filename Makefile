
# Ce Makefile sert à faciliter la mise à jour de la documentation,
# quand celle-ci a effectivement été modifiée. Pour l'utiliser : make.

# Pour donner plus de détails, par défaut quand on lance juste 'make',
# ce Makefile mettera à jour le site web et le PDF de la documentation
# seulement si nécessaire, c'est-à-dire seulement si la date de
# modification du fichier make.timestamp est antérieure à une de celles
# des fichiers sources de la bibliothèque Tortuino. Cette fonctionnalité
# est assurée par make, elle est donc sûre.
# De plus, on peut avoir accès à un moyen de mettre à jour "proprement"
# le repertoire git grâce à 'make pull' qui va d'abord exécuter 'git pull'
# pour récupérer les derniers commits, puis 'touch make.timestamp' pour
# s'assurer que la date de dernière modification de ce fichier soit
# plus récente que ce qui permet de générer la documentation, et ainsi
# éviter de recréer par erreur la documentation.
# Enfin, il est aussi possible de faire 'make cleanall' qui permet de
# nettoyer ce que produit ce Makefile en supprimant tout le contenu
# du dossier Documentation, les logs et autres fichiers.



# Documentation folder
DOC=./Documentation

# Library folder
LIB=./Tortuino

# Doxygen configuration file
DGN=./DoxyConfig

# Make output log file
LOG=./make.log

# Make timestamp file
MTS=./make.timestamp

# LaTeX header file
LHD=$(DOC)/latex/header.tex


# Default target set to the following one
.DEFAULT_GOAL := $(MTS)


$(MTS): $(LIB)/Tortuino.h $(LIB)/Tortuino.cpp $(LIB)/TortuinoDessins.h $(LIB)/TortuinoDessins.cpp
	@echo "[make] Started documentation make log." | tee $(LOG)
	
	@echo "[make] Generating custom LaTeX header...\n" | tee -a $(LOG)
	@rm -f $(LHD)*
	doxygen -w latex $(LHD) /dev/null /dev/null $(DGN)
	sed -i 's={\\Large Your title here}\\\\=\\includegraphics\[width\=100mm\,scale\=0.5\]{../../Images/logo-tortuino.png}\\\\\n\\vspace*{3cm}\n{\\Large Documentation $$projectname}\\\\=g' $(LHD)
	@rm -f $(LHD).*
	sed -i 's/Generated by/Généré par/g' $(LHD)
	@rm -f $(LHD).*
	@echo "\n[make] Custom LaTeX header generation finished." | tee -a $(LOG)
	
	@echo "[make] Calling Doxygen for the rest...\n" | tee -a $(LOG)
	outDir=$(DOC) doxygen $(DGN) >> $(LOG)
	@echo "\n[make] Doxygen finished." | tee -a $(LOG)
	
	@echo "[make] Calling the PDF make...\n" | tee -a $(LOG)
	make -C $(DOC)/latex/ >> $(LOG)
	@rm -f $(LHD)*
	@echo "\n[make] PDF make finished." | tee -a $(LOG)
	
	@echo "[make] Updating make.timestamp...\n" | tee -a $(LOG)
	date +'%Y/%m/%d %H:%M:%S.%N' > $(MTS)
	@echo "\n[make] make.timestamp update finished." | tee -a $(LOG)
	
	@echo "[make] Documentation make log ended." | tee -a $(LOG)

pull:
	@echo "[make] Pulling with git...\n"
	git pull
	@echo "\n[make] git pull finished."
	@echo "[make] Making sure $(MTS) is up-to-date...\n"
	touch $(MTS)
	@echo "\n[make] Touch finished."

cleanall:
	@echo "[make] Removing auto-generated files from . and from $(DOC)..."
	rm -rf $(DOC)/*
	rm -f $(LOG)
	rm -f $(MTS)
	@echo "[make] Removal finished."