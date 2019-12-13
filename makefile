SOURCE = teste
##################################################
c++:
	g++ $(SOURCE).cpp -c -Wall -std=c++11 -g
	g++ $(SOURCE).o -o $(SOURCE)
	./$(SOURCE)
c++in:
	g++ $(SOURCE).cpp -c -Wall -std=c++11 -g
	g++ $(SOURCE).o -o $(SOURCE)
	./$(SOURCE) < in.txt
##################################################
c:
	gcc $(SOURCE).c -o $(SOURCE)
	./$(SOURCE)
cin:
	gcc $(SOURCE).c -o $(SOURCE)
	./$(SOURCE) < in.txt
##################################################
py:
	python $(SOURCE).py
pyin:
	python $(SOURCE).py < in.txt
py3:
	python3 $(SOURCE).py
py3in:
	python3 $(SOURCE).py < in.txt
##################################################

executa-passo:
	gdb $(SOURCE)
##################################################
limpa:
	rm -f $(SOURCE).o $(SOURCE)
	clear

##################################################
compactar:
	zip -r  $(SOURCE).zip $(SOURCE)

descompactar:
	unzip $(SOURCE).zip -d destino
##################################################

bd:
	service postgresql
	sudo su postgres

	psql
	ALTER USER postgres WITH PASSWORD '';
