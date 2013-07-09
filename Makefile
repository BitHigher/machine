FORTRAN = gfortran
OPTS    = -O2
CC      = g++
CFLAGS  = -O3
LOADER  = g++
LFLAGS  = -llapacke -llapack -lrefblas -lcblas -lblas -lgfortran
ALL		= test


all: $(ALL)

test: test.o lda.o classifier.o hfmatrix.o hfvector.o perceptron.o saver.o loader.o
	$(LOADER) $^ $(LFLAGS) -o $@

hfmatrix.o: structure/hfmatrix.cpp 
	$(CC) -c -o $@ $^

hfvector.o: structure/hfvector.cpp
	$(CC) -c -o $@ $^

saver.o: io/saver.cpp io/saver.h
	$(CC) -c -o $@ $<

loader.o: io/loader.cpp
	$(CC) -c -o $@ $^

perceptron.o: classifier/perceptron.cpp
	$(CC) -c -o $@ $^

lda.o: classifier/lda.cpp
	$(CC) -c -o $@ $^

classifier.o: classifier/classifier.cpp
	$(CC) -c -o $@ $^

clean:
	rm -f *.o $(ALL) 
