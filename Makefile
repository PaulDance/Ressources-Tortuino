
# Ce Makefile sert à faciliter la mise à jour de la documentation,
# quand celle-ci a effectivement été modifiée. Pour l'utiliser : make.

DOC=./Documentation
LIB=./Tortuino
DGN=./DoxyConfig
LOG=./make.log

all: $(LIB)/Tortuino.h $(LIB)/Tortuino.cpp $(LIB)/TortuinoDessins.h $(LIB)/TortuinoDessins.cpp
	echo "[make] Started documentation make log." > $(LOG)
	echo "[make] Calling Doxygen...\n" >> $(LOG)
	doxygen $(DGN) >> $(LOG)
	echo "\n[make] Doxygen finished." >> $(LOG)
	echo "[make] Calling the PDF's make...\n" >> $(LOG)
	make -C $(DOC)/latex/ >> $(LOG)
	echo "\n\[make] PDF's make finished." >> $(LOG)
	echo "[make] Documentation make log terminated." >> $(LOG)

cleanall:
	rm -rf $(DOC)/*
	rm -f $(LOG)
