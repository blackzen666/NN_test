#include <iostream>
#include <fstream>
#include <armadillo>
#include <vector>

#define db(x) if(1) cout<<x<<endl;

using namespace std;
using namespace arma;

mat sigmoid(mat A) {
  return 1 / (1 + exp(-A));
}

vector<mat> forward(mat &In, mat &W1, mat &W2) {
  mat A = sigmoid(In * W1.t());
  mat out = sigmoid(A* W2.t());

  vector<mat> results(2);

  results[0] = A;
  results[1] = out;
  return results;
}

mat back_propagation(mat &X, mat &A, mat &H, mat &Y, mat &weigth, mat &weigth_2, int number_of_images, mat J_theta) {
  float alpha = 0.6f;

  mat H_prima = H % (1 - H);
  mat A_prima = A % (1 - A);
  mat D3 = (H - Y) % H_prima;
  mat D2 = (D3 * weigth_2) % A_prima;
  mat Dw2 =  D3.t() * A;
  mat Dw1 =  X.t() * D2;

  weigth = weigth -  alpha * Dw1.t();
  weigth_2 = weigth_2 - alpha * Dw2;

  mat J_t = (1 / (double)number_of_images) * (pow( ( Y - H), 2));
  J_theta = join_vert(J_theta,sum(J_t));

  return J_theta;
}

int read_MNIST_labels(mat &A);
int read_MNIST_images(mat &A);


int main() {
  int neurons_number = 20, max_iter = 60000;
  arma_rng::set_seed_random();
  mat Y;
  mat X;

  int number_of_images = read_MNIST_images(X);
  int outputs_number = 10;
  int characteristics = 28*28;
  // mat bias =  ones<mat>(number_of_images,1);
  //X = join_horiz(bias,X);

  mat weigth = randn<mat>(neurons_number, characteristics);

  mat weigth_2 = randn<mat>(outputs_number , neurons_number);

  mat J_theta = zeros<mat>(0, outputs_number);
  for (int i = 0; i < max_iter; ++i) {
    vector<mat> results =  forward(X, weigth, weigth_2);
    mat A = results[0];
    mat H = results[1];
    J_theta = back_propagation(X, A, H, Y, weigth, weigth_2, number_of_images, J_theta);
  }

  cout << "INPUT TEST" << endl;

  mat test_input;

  int test_images = read_MNIST_images(test_input);
  mat test_outputs;
  read_MNIST_labels(test_outputs);

  //mat bias_t =  ones<mat>(4,1);
  //test_input = join_horiz(bias_t,test_input);

  //cout << test_input << endl;

  vector<mat> salida = forward(test_input, weigth, weigth_2);
  cout << salida[1] <<endl;
  return 0;
}
