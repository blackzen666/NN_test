all: NN

NN: NN.cc
	g++ -std=c++11 NN.cc -o NN.out -O2 -larmadill

