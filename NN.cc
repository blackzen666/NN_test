#include <iostream>
#include <fstream>
#include <armadillo>
using namespace std;
using namespace arma;

int main() {
   /*unsigned char cadena;
   ifstream fe("60klabels");

   int counter = 0;

   while(!fe.eof()) {
      fe >> cadena;
      cout << (int)cadena<<" ";
   	counter++;
   }
   fe.close();
   cout <<"counter : "<< counter << endl;
   */

    mat read = randu<mat>(784*60000);

    //pic.reshape(28,28);
    //cout << pic <<endl;

    int number_of_images = 60000;
    
    mat Y = zeros<mat>(number_of_images,10);
    //cout << Y << endl;

    int epsilon = 1;

    int neurons_number = 40;

    //mat X = read.reshape(number_of_images,784);
    mat X = ones<mat>(number_of_images,784);

    mat bias =  ones<mat>(number_of_images,1);

    ////agrega 1 linea de 1 a la matrix dejandola de 785x 60000
    //linea matlab. 
    //X=[bias,X];
   
   ///INICIALIZACION ALEATORIA ES EMJOR HACERLA ENTRE -1 Y 1
   //pesos 1
    //recordar q esta es de 785 debido a el bias term.
   mat weigth = randn<mat>(neurons_number,784);

   //pesos 2
   mat weigth_2 = randn<mat>(10,neurons_number);


//////FORWARD PROPAGATION./////


   vec J_theta = zeros<mat>(10);

   for (int i = 0; i < 200; ++i)
   {
      mat A = X*weigth.t();

      mat temp = 1./(1+exp(-A));

      mat A_resultado = weigth_2*A.t();

      mat temp2 = 1./(1+exp(-A_resultado));

      cout << i << endl;
   }

   //cout << temp2 <<endl;

      return 0;
}