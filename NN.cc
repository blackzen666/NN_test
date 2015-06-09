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

vector<mat> forward(mat In, mat W1, mat W2) {
  mat A = sigmoid(In * W1.t());
  mat out = sigmoid(A* W2.t());

  vector<mat> results(2);

  results[0] = A;
  results[1] = out;
  return results;
}


mat back_propagation(mat X, mat A, mat H, mat Y, mat weigth, mat weigth_2, int number_of_images, mat J_theta) {
  float alpha = 0.5f;

  mat H_prima = H % (1 - H);
  mat A_prima = A % (1 - A);

  mat D3 = (H - Y) % H_prima;
  mat D2 = (D3 * weigth_2) % A_prima;

  mat Dw2 =  D3.t() * A;
  mat Dw1 =  X.t() * D2;

  weigth   = weigth   - (alpha / number_of_images) * Dw1.t();
  weigth_2 = weigth_2 - (alpha / number_of_images) * Dw2;


  mat J_t = (1 / (double)number_of_images) * (pow( ( Y - H), 2));

  J_theta = join_vert(J_theta,sum(J_t));

  return J_theta;
}




int main() {


  int number_of_images = 10000;

  ////////////////////////////////////OPERACION DE LABELS ///////////////////////

  mat Y = randn<mat>(number_of_images,10);


  //CONVERSION DE LABELS A CODIFICACION "BINARIA" PARA CORREGIR FORWARD.

  /////////////////inicializacion//////////////////////////////
  int neurons_number = 40;

  // leer los numeros
  mat read = randu<mat>(784*1000);

  //pic.reshape(28,28);
  //cout << pic <<endl;

  int epsilon = 1;

  //organizndo los datos de forma de q queden en una matrix de 784x10000
  //mat X = read.reshape(number_of_images,784);
  mat X = 50*randn<mat>(number_of_images,784);

  //agregando el termino bias a nuestras caracteristicas
  mat bias =  ones<mat>(number_of_images,1);
  X = join_horiz(bias,X);

  //creando matrix aleatoria para los pesos intermedios

  ///INICIALIZACION ALEATORIA ES EMJOR HACERLA ENTRE -1 Y 1
  //recordar q esta es de 785 debido a el bias term.
  mat weigth = randn<mat>(neurons_number,785);

  //pesos 2
  mat weigth_2 = randn<mat>(10,neurons_number);

  /*cout << size(read) << endl;
  cout << size(X) <<endl;
  cout << size(Y) << endl;
  cout << size(bias) << endl;
  cout << size(weigth) << endl;
  cout << size(weigth_2) << endl;*/

  /////--------------------------------------------------------------------------------------------
  //FORWARD PROPAGATION


  mat J_theta = zeros<mat>(0,10);

  //ESTE FOR ES PARA HACER BACK Y FORWARD PROPAGATION graficas resultantes quedan en termino sde j_thera y iteraciones.
  for (int i = 0; i < 1; ++i) {

    vector<mat> results =  forward(X, weigth, weigth_2);
    mat A = results[0];
    mat H = results[1];

    //////BACK PROPAGATION./////

    J_theta =back_propagation(X, A, H, Y, weigth, weigth_2, number_of_images, J_theta);

    cout <<i<<endl;
    cout <<J_theta<<endl;
  }

  return 0;
}
