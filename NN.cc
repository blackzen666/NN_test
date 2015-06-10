#include <iostream>
#include <fstream>
#include <armadillo>
#include <vector>

#define db(x) if(1) cout<<x<<endl;

using namespace std;
using namespace arma;

int reverseInt (int i) {
  unsigned char c1, c2, c3, c4;

  c1 = i & 255;
  c2 = (i >> 8) & 255;
  c3 = (i >> 16) & 255;
  c4 = (i >> 24) & 255;

  return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

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

double alpha = 0.08;
double error = 100;

mat back_propagation(mat &X, mat &A, mat &H, mat &Y, mat &weigth, mat &weigth_2, int number_of_images, mat J_theta) {

  mat H_prima = H % (1 - H);
  mat A_prima = A % (1 - A);
  mat D3 = (H - Y) % H_prima;
  mat D2 = (D3 * weigth_2) % A_prima;
  mat Dw2 =  D3.t() * A;
  mat Dw1 =  X.t() * D2;

  weigth = weigth -  alpha * Dw1.t();
  weigth_2 = weigth_2 - alpha * Dw2;

  mat J_t = (1 / (double)number_of_images) * (pow( ( Y - H), 2));
  J_theta = sum(sum(J_t));
  double t_error = J_theta(0,0);
  if(t_error >= error)
    alpha /= 3;
  if(t_error - error <= 0.00001)
    alpha *= 2;
  error = t_error;
  cout << error <<" "<<alpha <<endl;
  return J_theta;
}




int read_MNIST_labels(mat &data) {
  // ifstream file ("t10k-images_unzip");

  ifstream file ("dataset/t10k-labels");
  int num_data;
  if (file.is_open()) {
    int magic_number=0;
    int number_of_images=0;
    int n_rows=0;
    int n_cols=0;
    file.read((char*)&magic_number,sizeof(magic_number));
    magic_number= reverseInt(magic_number);
    //cout << magic_number <<endl;

    file.read((char*)&number_of_images,sizeof(number_of_images));
    number_of_images= reverseInt(number_of_images);
    //cout << number_of_images <<endl;

    num_data = number_of_images;

    int counter = 0;

    unsigned char  cadena;

    ////matriz definition because of element read
    data = zeros<mat>(number_of_images,10);

    while(!file.eof()) {

      file.read((char*)&cadena,sizeof(char));
      int pixel= cadena;

      if(counter < number_of_images - 1){
        //std::cout << pixel << endl;
        data(counter,pixel)= 1;
        //cout<< data(counter,0) <<endl;
      }
      counter++;
    }
    /*cout <<data(0,0)<<endl;
      cout <<data(1,0)<<endl;
      cout <<data(2,0)<<endl;
      cout <<data(3,0)<<endl;
      cout <<size(data)<<endl;*/


    //cout <<"read counter: "<<counter <<endl;
  }
  return num_data;
}


int read_MNIST_images(mat &data) {
  // ifstream file ();
  int num_data;

  ifstream file ("dataset/t10k-images");
  if (file.is_open()) {
    int magic_number=0;
    int number_of_images=0;
    int n_rows=0;
    int n_cols=0;
    file.read((char*)&magic_number,sizeof(magic_number));
    magic_number= reverseInt(magic_number);
    cout << magic_number <<endl;

    file.read((char*)&number_of_images,sizeof(number_of_images));
    number_of_images= reverseInt(number_of_images);
    cout << number_of_images <<endl;

    file.read((char*)&n_rows,sizeof(n_rows));
    n_rows= reverseInt(n_rows);
    cout << n_rows <<endl;

    file.read((char*)&n_cols,sizeof(n_cols));
    n_cols= reverseInt(n_cols);
    cout <<n_cols <<endl;

    num_data= number_of_images * n_rows * n_cols;

    int counter = 0;

    unsigned char  cadena;

    ////matriz definition because of element read
    data = zeros<mat>(num_data, 1);

    while(!file.eof()) {

      file.read((char*)&cadena,sizeof(char));
      int pixel= cadena;

      if(counter < number_of_images - 1){
        data(counter,0)= ((double)pixel)/255.0;
      }
      counter++;
    }
    data.reshape(number_of_images,n_cols*n_rows);
    mat tmp = data.row(0);
    cout<<"sized "<<size(data.row(0))<<endl;
    tmp.reshape(n_rows, n_cols);
    cout<<"sizet "<<size(tmp)<<endl;
    tmp.save("tmp.mio", arma_ascii);
    mat bias = ones<mat>(number_of_images,1);
    data = join_horiz(data,bias);
    //cout << size(data) <<endl;

    //cout <<"read counter: "<<counter <<endl;
  }
  return num_data;
}

int check_res(mat &A, mat &B) {
  int err = 0;
  for(int i = 0; i < A.n_rows; i++) {
    for(int j = 0; j < A.n_cols; i++) {
      if(A(i,j) != B(i,j)) {
        err++;
        break;
      }
    }
  }
  return err;
}

int main() {
  int neurons_number = 20, max_iter = 1;
  arma_rng::set_seed_random();
  mat Y;
  mat X;
  cin >> alpha;
  int number_of_labels = read_MNIST_labels(Y);

  int number_of_images = read_MNIST_images(X);
  int outputs_number = 10;
  int characteristics = 28*28;
  // mat bias =  ones<mat>(number_of_images,1);
  //X = join_horiz(bias,X);

  mat weigth = randn<mat>(neurons_number, characteristics+1);

  mat weigth_2 = randn<mat>(outputs_number , neurons_number);

  mat J_theta = zeros<mat>(0, outputs_number);
  for (int i = 0; i < max_iter; ++i) {
    vector<mat> results =  forward(X, weigth, weigth_2);
    mat A = results[0];
    mat H = results[1];
    J_theta = back_propagation(X, A, H, Y, weigth, weigth_2, number_of_images, J_theta);
    cout << i << endl;
  }
  return 0;
  cout << "INPUT TEST" << endl;

  mat test_input;

  int test_images = read_MNIST_images(test_input);
  mat test_outputs;
  read_MNIST_labels(test_outputs);

  //mat bias_t =  ones<mat>(4,1);
  //test_input = join_horiz(bias_t,test_input);

  //cout << test_input << endl;

  vector<mat> salida = forward(test_input, weigth, weigth_2);
  //cout << salida[1].transform([](double val){ if(val < 0.5) return 0; else return 1;}) <<endl;
  mat tmp = salida[1].transform([](double val){ if(val < 0.5) return 0; else return 1;});
  int errors = check_res(tmp, test_outputs);
  cout<<"errors: "<< errors<<endl;
  return 0;
}
