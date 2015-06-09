#include <iostream>
#include <fstream>
#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;

mat sigmoid(mat A) {
  return 1 / (1 + exp(-A));
}

vector<mat> forward(mat In, mat& W1, mat& W2) {
  mat A = sigmoid(In * W1.t());
  mat out = sigmoid(A* W2.t());

  vector<mat> results(2);

  results[0] = A;
  results[1] = out;

  cout<<"In: " <<size(In)<< endl;
  //cout<<"In: " <<In<< endl;
  cout<<"W1: " <<size(W1)<< endl;
  //cout<<"W1: " <<W1<< endl;
  cout<<"A: " <<size(A)<< endl;
  //cout<<"A: " <<A<< endl;
  cout<<"W2: " <<size(W2)<< endl;
  //cout<<"W2: " <<W2<< endl;
  cout<<"out: " <<size(out)<< endl;
  //cout<<"out: " <<out<< endl;
  return results;
}


mat back_propagation(mat X, mat A, mat H, mat Y, mat& weigth, mat& weigth_2, int number_of_images, mat J_theta) {
  //valor del salto en j_theta
  float alpha = 0.01f;

  mat H_prima = H % (1 - H);
  ////cout <<H_prima<<endl;
  mat A_prima = A % (1 - A);
  //cout <<A_prima<<endl;
  mat D3 = (H - Y) % H_prima;
  //cout <<D3<<endl;
  mat D2 = (D3 * weigth_2) % A_prima;
  //cout <<D2<<endl;
  mat Dw2 =  D3.t() * A;
  //cout <<Dw2<<endl;
  mat Dw1 =  X.t() * D2;
  //cout <<Dw1<<endl;
  weigth = weigth - ( alpha / number_of_images) * Dw1.t();

  weigth_2 = weigth_2 - (alpha / number_of_images) * Dw2;


  //  esta linea esta creando puros zeros y la inicie en randoms yo creo q esta mala
  mat J_t = (1 / (double)number_of_images) * (pow( ( Y - H), 2));
  cout << J_t << endl;

  //sea agregan los valores calculados a  una matriz para luego graficarlos
  //esto es un .push_back() en matlab
  //J_theta = [J_theta;sum(J_t)];
  cout<< "error"<<sum(J_t)<<endl;

  J_theta = join_vert(J_theta,sum(J_t));

  cout<<"H_prima: " <<size(H_prima)<< endl;
  cout<<"A_prima: "<< size(A_prima)<< endl;

  cout<<"D3: "<< size(D3)<< endl;
  cout<<"D2: "<< size(D2)<< endl;

  cout<<"Dw2: "<< size(Dw2)<< endl;
  cout<<"Dw1: "<< size(Dw1)<< endl;


  cout<<"weigths1: "<< size(weigth)<< endl;
  cout<<"weigths2: "<< size(weigth_2)<< endl;


  cout<<"J_t: "<< size(J_t)<< endl;

  cout<<"J_t: "<< size(J_theta)<< endl;
  //return weigth,weigth_2;
  return J_theta;
}

int main() {


  int number_of_images = 4;

  ////////////////////////////////////OPERACION DE LABELS ///////////////////////

  //CREANOD MATRIZ DONDE GUARDAREMOS LOS VALORES DE LOS LABELS
  mat Y = zeros<mat>(number_of_images,1);
  Y(0,0) = 0;
  Y(1,0) = 1;
  Y(2,0) = 1;
  Y(3,0) = 0;


  cout <<Y<<endl;
  ///////////////////////////////////////////////////////////////////////////////

  /////////////////inicializacion//////////////////////////////
  //numero de neuronas en la capa oculta
  int neurons_number = 10;

  mat X = zeros<mat>(number_of_images,2);
  
  X(0,0) = 0;
  X(0,1) = 0; 
  X(1,0) = 0;
  X(1,1) = 1;
  X(2,0) = 1;
  X(2,1) = 0;
  X(3,0) = 1;
  X(3,1) = 1;

  cout << X << endl;

  //agregando el termino bias a nuestras caracteristicas
  mat bias =  ones<mat>(number_of_images,1);
  X = join_horiz(bias,X);

  //creando matrix aleatoria para los pesos intermedios

  ///INICIALIZACION ALEATORIA ES EMJOR HACERLA ENTRE -1 Y 1
  //recordar q esta es de 785 debido a el bias term.
  mat weigth = randn<mat>(neurons_number,3);

  //pesos 2
  mat weigth_2 = randn<mat>(1,neurons_number);

  //cout <<size(read)<< endl;
  cout <<size(X) <<endl;
  cout <<size(Y)<< endl;
  cout << size(bias) << endl;
  cout<< size(weigth)<< endl;
  cout<< size(weigth_2)<< endl;



  /////--------------------------------------------------------------------------------------------
  //FORWARD PROPAGATION


  mat J_theta = zeros<mat>(0,1);

  //ESTE FOR ES PARA HACER BACK Y FORWARD PROPAGATION graficas resultantes quedan en termino sde j_thera y iteraciones.
  for (int i = 0; i < 500; ++i) {

    ///NO ME ACUERDO SI ES NECESARIO EL TEMRINO BIAS EN LAS NEURONAS DE LA MITAD.
    /* #se crea un vector de 1
       matriz_A = ones(number_of_images,1);
#y se agrega a la matriz para representar el bias term.
A = [matriz_A,A];
*/

    vector<mat> results =  forward(X, weigth, weigth_2);
    mat A = results[0];
    mat H = results[1];


    //----------------------------------------------------------------------
    //////BACK PROPAGATION./////

    J_theta =back_propagation(X,A,H,Y,weigth,weigth_2,number_of_images,J_theta);

    cout <<i<<endl;
    cout <<J_theta<<endl;
  }

  cout << "INPUT TEST 1" << endl; 

  mat test_input1 = zeros<mat>(1,2);
	
  test_input1(0,0)= 0;
  test_input1(0,1)= 0;	

  mat bias1 =  ones<mat>(1,1);
  test_input1 = join_horiz(bias1,test_input1);

  cout << test_input1 << endl;

  vector<mat> salida1 = forward(test_input1, weigth, weigth_2);
  cout <<salida1[1]<<endl;

  cout << "INPUT TEST 2" << endl; 

  mat test_input2 = zeros<mat>(1,2);
	
  test_input2(0,0)= 0;
  test_input2(0,1)= 1;	

  mat bias2 =  ones<mat>(1,1);
  test_input2 = join_horiz(bias2,test_input2);

  cout << test_input2 << endl;

  vector<mat> salida2 = forward(test_input2, weigth, weigth_2);
  cout <<salida2[1]<<endl;

   cout << "INPUT TEST 3" << endl; 

  mat test_input3 = zeros<mat>(1,2);
	
  test_input3(0,0)= 1;
  test_input3(0,1)= 0;	

  mat bias3 =  ones<mat>(1,1);
  test_input3 = join_horiz(bias3,test_input3);

  cout << test_input3 << endl;

  vector<mat> salida3 = forward(test_input3, weigth, weigth_2);
  cout <<salida3[1]<<endl;

 cout << "INPUT TEST 4" << endl; 

  mat test_input4 = zeros<mat>(1,2);
	
  test_input4(0,0)= 1;
  test_input4(0,1)= 1;	

  mat bias4 =  ones<mat>(1,1);
  test_input4 = join_horiz(bias4,test_input4);

  cout << test_input4 << endl;

  vector<mat> salida4 = forward(test_input4, weigth, weigth_2);
  cout <<salida4[1]<<endl;
  return 0;
}

