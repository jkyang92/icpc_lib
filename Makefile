.PHONY : all files.lst clean

all : code.pdf

clean :
	rm -f files.lst code.pdf code.aux code.log

files.lst : 
	git ls-files | grep -E "(.cpp)|(.java)|(vimrc)" | sed -e '/archive/d' -e '/test/d' > files.lst
#somewhat supprised this doesn't yield infinite loops, but this makes
#building the list of listings work correctly
code.lol : code.tex files.lst
	pdflatex -interaction nonstopmode code.tex
code.pdf : code.tex files.lst code.lol
	pdflatex -interaction nonstopmode code.tex
