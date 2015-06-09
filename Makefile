CC = g++ -std=c++11

all: NN Experiment Endian

NN: NN.cc
	$(CC) NN.cc -o NN.out -larmadillo

Experiment: experiment.cc
	$(CC) experiment.cc -o experiment.out -larmadillo

Endian: swap_endian.cc
	$(CC) swap_endian.cc -o swap_endian.out

Xor: xor_test.cc
	$(CC) xor_test.cc -o xor_test.out -larmadillo

clean:
	rm -rf *.out
