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

hfmatrix.o: structure/hfmatrix.cpp structure/hfmatrix.h
	$(CC) -c -o $@ $<

hfvector.o: structure/hfvector.cpp structure/hfvector.h
	$(CC) -c -o $@ $<

saver.o: io/saver.cpp io/saver.h
	$(CC) -c -o $@ $<

loader.o: io/loader.cpp io/loader.h
	$(CC) -c -o $@ $<

perceptron.o: classifier/perceptron.cpp classifier/perceptron.h
	$(CC) -c -o $@ $<

lda.o: classifier/lda.cpp classifier/lda.h
	$(CC) -c -o $@ $<

classifier.o: classifier/classifier.cpp classifier/classifier.h
	$(CC) -c -o $@ $<

clean:
	rm -f *.o $(ALL) 
