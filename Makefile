FORTRAN = gfortran
OPTS    = -O2
CC      = g++
CFLAGS  = -O3
LOADER  = g++
LFLAGS  = -llapacke -llapack -lrefblas -lcblas -lblas -lgfortran
ALL		= test


all: $(ALL)

linear: linear.o
	$(LOADER) $^ $(LFLAGS)  -o $@

lls: lls.o
	$(LOADER) $^ $(LFLAGS)  -o $@

test_cpp: test_cpp.o
	$(LOADER) $^ $(LFLAGS) -o $@

test_math: test_math.o
	$(LOADER) $^ $(LFLAGS) -o $@

test: test.o lda.o hfmatrix.o hfvector.o
	$(LOADER) $^ $(LFLAGS) -o $@

hfmatrix.o: structure/hfmatrix.cpp
	$(CC) -c -o $@ $^

hfvector.o: structure/hfvector.cpp
	$(CC) -c -o $@ $^

saver.o: io/saver.cpp
	$(CC) -c -o $@ $^

loader.o: io/loader.cpp
	$(CC) -c -o $@ $^

lda.o: classifier/lda.cpp
	$(CC) -c -o $@ $^

clean:
	rm -f *.o $(ALL) 
