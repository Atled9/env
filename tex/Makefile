coor.png: coor.pdf
	convert -density 384 coor.pdf -resize 25% -alpha remove ../images_for_README/coor.png
coor.pdf: coor.tex
	pdflatex coor.tex

proj.png: proj.pdf
	convert -density 384 proj.pdf -resize 25% -alpha remove ../images_for_README/proj.png
proj.pdf: proj.tex
	pdflatex proj.tex

trans.png: trans.pdf
	convert -density 384 trans.pdf -resize 25% -alpha remove ../images_for_README/trans.png
trans.pdf: trans.tex
	pdflatex trans.tex

clean:
	rm *.pdf *.log *.aux 
