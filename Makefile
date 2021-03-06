FORTRAN = gfortran
OPTS    = -O2
CC      = g++
CFLAGS  = -O3
LOADER  = g++
LFLAGS  = -llapacke -llapack -lrefblas -lcblas -lblas -lgfortran -lpthread
ALL		= test


all: $(ALL)

test: test.o lda.o classifier.o hfmatrix.o hfvector.o perceptron.o saver.o loader.o kmeans.o parallel.o euclidean.o distance.o init.o
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

kmeans.o: clustering/kmeans.cpp clustering/kmeans.h
	$(CC) -c -o $@ $<

parallel.o: base/parallel.cpp base/parallel.h
	$(CC) -c -o $@ $<

euclidean.o: distance/euclidean.cpp distance/euclidean.h
	$(CC) -c -o $@ $<

distance.o: distance/distance.cpp distance/distance.h
	$(CC) -c -o $@ $<

init.o: init.cpp
	$(CC) -c -o $@ $<

clean:
	rm -f *.o $(ALL) 
