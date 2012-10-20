.PHONY : all files.lst clean

all : code.pdf

clean :
	rm -f files.lst code.pdf code.aux code.log

files.lst : 
	git ls-files | grep ".cpp" > files.lst
code.pdf : code.tex files.lst
	pdflatex -interaction nonstopmode code.tex
