coor.png: coor.pdf
	convert -density 384 coor.pdf -resize 25% -alpha remove ../images_for_README/coor.png
coor.pdf: coor.tex
	pdflatex coor.tex

proj.pdf: proj.tex
	pdflatex proj.tex

clean:
	rm *.pdf *.log *.aux 
