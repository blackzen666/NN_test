CC = g++ -std=c++11 -larmadillo

all: NN Experiment

NN: NN.cc
	$(CC) NN.cc -o NN.out

Experiment: experiment.cc
	$(CC) experiment.cc -o experiment.out
