BPATH=bin/
SRC=src/

SRCFILE=$(wildcard *.java)
BINFILE=$(SRCFILE:.java=.class)

vpath %.java src/
vpath %.class bin/

all:Addition.class Expression.class Oppose.class AnalyseurExpression.class FonctionBinaire.class ProjetPOO.class Constante.class FonctionUnaire.class Puissance.class Cosinus.class Inconnue.class RacineCarre.class Division.class InconnuValeur.class Sinus.class Equation.class Logarithme.class Soustraction.class Exponentielle.class Multiplication.class Tangente.class


%.class: %.java
	javac $^ -d $(BPATH) -classpath $(BPATH) -sourcepath $(SRC)

clean:
	rm $(BPATH)*.class

archive :all
	tar -f ProjetPOO_Thomas_Kuntz.tar.gz -cvz src/* bin/* makefile rapport.* DiagrammeClasse.jpg
