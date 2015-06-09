CC = g++ -std=c++11

all: NN Experiment Endian

NN: NN.cc
	$(CC) NN.cc -o NN.out -larmadillo

Experiment: experiment.cc
	$(CC) experiment.cc -o experiment.out -larmadillo

Endian: swap_endian.cc
	$(CC) swap_endian.cc -o swap_endian.out

clean:
	rm -rf *.out
