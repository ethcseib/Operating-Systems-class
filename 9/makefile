
latex = 9

graphics = 9.pdf

all: $(graphics) $(latex)

$(latex): $(latex).tex
	pdflatex $(latex).tex

clean:
	rm $(graphics) $(latex).pdf *.log *aux
