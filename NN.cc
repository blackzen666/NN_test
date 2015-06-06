#include <iostream>
#include <fstream>
#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;

mat sigmoid(mat A) {
  return 1 / (1 + exp(-A));
}

vector<mat> forward(mat In, mat W1, mat W2) {
  mat A = sigmoid(In * W1.t());
  mat out = sigmoid(A* W2.t());

  vector<mat> results;

  results.push_back(A);
  results.push_back(out);

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


mat back_propagation(mat X, mat A,mat H,mat Y,mat weigth,mat weigth_2,int number_of_images,mat J_theta) {
  //valor del salto en j_theta
  float alpha = 0.01f;

  mat H_prima = H%(1 - H);
  ////cout <<H_prima<<endl;
  mat A_prima = A%(1 - A);
  //cout <<A_prima<<endl;
  mat D3 = (H - Y)%H_prima;
  //cout <<D3<<endl;
  mat D2 = (D3*weigth_2)%A_prima;
  //cout <<D2<<endl;
  mat Dw2 =  D3.t()*A;
  //cout <<Dw2<<endl;
  mat Dw1 =  X.t()*D2;
  //cout <<Dw1<<endl;
  weigth = weigth - (alpha/number_of_images)*Dw1.t();

  weigth_2 = weigth_2 - (alpha/number_of_images)*Dw2;



  //  esta linea esta creando puros zeros y la inicie en randoms yo creo q esta mala. 
  mat J_t = (1/number_of_images)*(pow((Y-H), 2));
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


  int number_of_images = 10000;

  ////////////////////////////////////OPERACION DE LABELS ///////////////////////

  //CREANOD MATRIZ DONDE GUARDAREMOS LOS VALORES DE LOS LABELS
  mat Y = randn<mat>(number_of_images,10);
  //cout << Y << endl;

  /*// CONVERSION DE LABELS PARA PODERLOS EVALUAR LOS VALORES DE SALIDA PARA CADA FOTO

    for m = 1:number_of_images2
    Y(m,labels(m)+1) =1;
    end
    */


  //CONVERSION DE LABELS A CODIFICACION "BINARIA" PARA CORREGIR FORWARD.
  /*for(int i = 0 ; i<number_of_images2;i++) {
    }*/
  ///////////////////////////////////////////////////////////////////////////////

  /////////////////inicializacion//////////////////////////////
  //numero de neuronas en la capa oculta
  int neurons_number = 40;

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

  cout <<size(read)<< endl;
  cout <<size(X) <<endl;
  cout <<size(Y)<< endl;
  cout << size(bias) << endl;
  cout<< size(weigth)<< endl;
  cout<< size(weigth_2)<< endl;



  /////--------------------------------------------------------------------------------------------
  //FORWARD PROPAGATION


  mat J_theta = zeros<mat>(0,10);

  //ESTE FOR ES PARA HACER BACK Y FORWARD PROPAGATION graficas resultantes quedan en termino sde j_thera y iteraciones.
  for (int i = 0; i < 1; ++i) {

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

  return 0;
}
