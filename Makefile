all: NN

NN: NN.cc
	g++ -std=c++11 NN.cc -o NN -O2 -larmadill

