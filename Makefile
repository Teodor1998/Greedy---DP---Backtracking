build: frati.cpp 
	g++ -Wall frati.cpp -o frati_exe
	g++ -Wall planificare.cpp -o planificare_exe
	g++ -Wall numaratoare.cpp -o numaratoare_exe

run-p1: frati_exe
	./frati_exe

run-p3: planificare_exe
	./planificare_exe

run-p4: numaratoare_exe
	./numaratoare_exe

clean:
	rm -f *_exe
