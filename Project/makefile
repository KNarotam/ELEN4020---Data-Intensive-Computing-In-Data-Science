all:
	g++ tableGenerator.cpp -o tableGenerator
	g++ -fopenmp -lgomp openMP.cpp -o openMP
	mpiCC -std=c++11 -o mpi mpi.cpp

build:
	g++ tableGenerator.cpp
	g++ -fopenmp -lgomp openMP.cpp

run table:
	./tableGenerator

run openMP:
	./openMP

run MPI:
	mpiexec -n 4 ./mpi

clean:
	rm -rf *o tableGenerator
	rm -rf *o openMP
	rm -rf *o mpi
