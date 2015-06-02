#include <iostream>
#include <fstream>
#include <armadillo>
using namespace std;
using namespace arma;

int main() {
   
   
   /////////////////////////LECTURA DE ARCHIVO /////////////////////////////
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
    
    
    int number_of_images = 10000;
    
    
///////////////////////////////////////////////////////////////////////////


////////////////////////////////////   OPERACION DE LABELS ///////////////////////

//CREANOD MATRIZ DONDE GUARDAREMOS LOS VALORES DE LOS LABELS
    mat Y = zeros<mat>(number_of_images,10);
    //cout << Y << endl;
    
    /*// CONVERSION DE LABELS PARA PODERLOS EVALUAR LOS VALORES DE SALIDA PARA CADA FOTO

         for m = 1:number_of_images2
         		Y(m,labels(m)+1) =1;
         end
    */
    
   
    //CONVERSION DE LABELS A CODIFICACION "BINARIA" PARA CORREGIR FORWARD.
   /*for(int i = 0 ; i<number_of_images2;i++)
    {
        
    }*/
    
    
 ///////////////////////////////////////////////////////////////////////////////
 
 
/////////////////inicializacion//////////////////////////////
    //numero de neuronas en la capa oculta
    int neurons_number = 40;
    
    mat read = randu<mat>(784*10000);

    //pic.reshape(28,28);
    //cout << pic <<endl;


    
    int epsilon = 1;

    
    //organizndo los datos de forma de q queden en una matrix de 784x10000 
    //mat X = read.reshape(number_of_images,784);
    mat X = zeros<mat>(number_of_images,784);


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

//valor del salto en j_theta
float alpha = 0.01f;

   vec J_theta = zeros<mat>(10);


//ESTE FOR ES PARA HACER BACK Y FORWARD PROPAGATION graficas resultantes quedan en termino sde j_thera y iteraciones.
//   for (int i = 0; i < 200; ++i)
//   {
      
      //haciendo las sumatorias (Xi*Wi) 
      mat A = X*weigth.t();

      //evaluando todos los valores de la matriz por la funcion H
      mat temp = 1./(1+exp(-A));

      ///NO ME ACUERDO SI ES NECESARIO EL TEMRINO BIAS EN LAS NEURONAS DE LA MITAD.
       /* #se crea un vector de 1 
        matriz_A = ones(number_of_images,1);
        #y se agrega a la matriz para representar el bias term.
        A = [matriz_A,A];
      */
      
      //calculando los valores de salida de la primera capa con los pesos
      mat A_resultado = weigth_2*temp.t();


      //evaluando los valores de la matriz por la funcion
      mat H = (1./(1+exp(-A_resultado))).t();

      
      cout<<"A: " <<size(A)<< endl;
      cout<<"temp:" << size(temp) << endl;
      cout<<"A_r: "<< size(A_resultado)<< endl;
      cout<<"H: "<< size(H)<< endl;
      
      
//----------------------------------------------------------------------     
 //////BACK PROPAGATION./////
      
      ///calculando derivada de funcion sigmuidal F(x)*(1-F(x))
      
     /////NO ES UNA MULTIPLICACION SINO OPERACION ELEMENTO A ELEMENTO
      ///ESTO DEBERIA DE SER UN ELEMENT WISE.
      
      //!!OJO OJO OJO OJO
      //!!!OJO OJO OJO OJO
      //!!!!!!!!!!!!!!!!
      
      //##calculandola derivda evaluando todos los valores de nuestram atriz en lapunion F(x)*(1-F(x))  
      //mat H_prima = H.*(1 .- H);
      //mat A_prima = A.*(1 .- A);
      
      
      mat H_prima = H*(1 -H).t();
      mat A_prima = A*(1- A).t();
      
     
     ////ACTUALIZACION DE LOS PESOS 
      
      
      //para la capa de salida se tiene D3 como el delta de la capa de salida
      //mat D3 = (H - Y).*H_prima;
     
      //test armadillo
      mat D3 = (H - Y)*H_prima.t();
      
      
      //para nuestra capa intermedia D2 como el delta de la capa intermedia
      //D2 = (D3*weigth_2).*A_prima;
      
      //test armadillo
      mat D2 = (D3*weigth_2)*A_prima.t();
      
      
      //en esta operacion kedan todos los valores con los cuales debemos actualizar nuestros pesos.
      //para la capa intermedia
      mat Dw2 =  D3.t()*A;
      
      //para la capa de entrada 
      //escojer desde el 2 hacia arriba o quitarle una columna
      //Dw1 = X.t()*D2(:,2:neurons_number+1);
      
       //test armadillo
      mat Dw1 =  X.t()*D2.t();
      
      
//restamos la matriz de los pesos actuales con el valor de cambio q esta guardado en la matriz y asi obtener los valores deseados de los pesos despues e nuestro entrenamiento
      //weigth = weigth - (alpha/number_of_images).*Dw1';

      //weigth_2 = weigth_2 - (alpha/number_of_images).*Dw2;
      
      
       //test armadillo
      weigth = weigth - (alpha/number_of_images)*Dw1.t();

      weigth_2 = weigth_2 - (alpha/number_of_images)*Dw2;
    
    
      
 //la funcion J_theta para representar el error y la funcion de aprnedizaje.
      //J_t = (1/number_of_images)*((Y-H).^2);
      
      //test armadillo
      mat J_t = (1/number_of_images)*((Y-H));
     
     
      //sea agregan los valores calculados a  una matriz para luego graficarlos
      //J_theta = [J_theta;sum(J_t)];
      
      //test armadillo
      J_theta = join_horiz(J_theta,sum(J_t));
      
      
        
      //verificando las iteraciones y el tamanio el vector agregado.
      size(J_theta);
 
  // }

      return 0;
}