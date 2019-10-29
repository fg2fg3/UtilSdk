CC1=g++

build:main.o epollserver.o
	$(CC1) -gdwarf-2 -o epolltest main.o epollserver.o

main.o:main.cpp epollserver.h
	$(CC1) -gdwarf-2 -c main.cpp

epollserver.o:epollserver.cpp epollserver.h
	$(CC1) -gdwarf-2 -c epollserver.cpp

clean:
	rm *.o epolltest
