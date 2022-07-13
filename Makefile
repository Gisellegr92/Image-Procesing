cc = g++ -std=c++11

all: main clean

clean:
	-rm main.o ImageProcessing.o

main: main.o ImageProcessing.o
	$(cc) -g -o project2.out main.o ImageProcessing.o

main.o: src/main.cpp src/ImageProcessing.h
	$(cc) -c -g src/main.cpp

ImageProcessing.o: src/ImageProcessing.cpp src/ImageProcessing.h
	$(cc) -c -g src/ImageProcessing.cpp




