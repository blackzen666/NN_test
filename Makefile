CC = g++ -std=c++11

all: NN Experiment

NN: NN.cc
	$(CC) NN.cc -o NN.out -larmadillo

Experiment: experiment.cc
	$(CC) experiment.cc -o experiment.out -larmadillo

Xor: xor_test.cc
	$(CC) xor_test.cc -o xor_test.out -larmadillo

clean:
	rm -rf *.out
