all: main.pdf

%.pdf: %.dvi
	dvipdfmx $^

%.dvi: %.tex
	platex -shell-escape $^

clean:
	rm -rf *.dvi *.aux *.log main.pdf
	rm -rf _minted_main
