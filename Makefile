CC = g++ 

all: NN Experiment

NN: NN.cc
	$(CC) NN.cc -o NN.out -std=c++11 -larmadillo

Experiment: experiment.cc
	$(CC) experiment.cc -o experiment.out -std=c++11 -larmadillo
