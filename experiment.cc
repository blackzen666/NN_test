#include <iostream>
#include <armadillo>
#include <netinet/in.h>
#include <bitset>



using namespace std;
using namespace arma;

mat sigmoid(mat A) {
  return 1 / (1 + exp(-A));
}


int main() {

   int num = 1;
    if(*(char *)&num == 1) {
      printf("\nLittle-Endian\n");
    }
    else {
      printf("Big-Endian\n");
    }

    unsigned char  cadena;
    ifstream fe("t10k_unzip");

    int counter = 0;

    while(!fe.eof()) {
      fe >> cadena;
      int a= (int)cadena;
      cout <<  cadena<<" ";
      //int num =  (int)cadena;
      //cout << a << endl;
      std::bitset<8> x(a);
      std::cout << x << endl;
      //counter++;
    }
    fe.close();
    cout <<"counter : "<< counter << endl;




/*
  mat A = randu<mat>(5,5) * 100;
  A.print("A:");
  rowvec B = max(A);
  B.print("B:");
  A.each_row() /= B;
  A.print("C:");
  mat C = sigmoid(A);
  C.print("D:");
*/
  return 0;
}
