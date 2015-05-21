#include <iostream>
#include <fstream>
using namespace std;

int main() {
   unsigned char cadena;
   ifstream fe("60klabels");

   int counter = 0;

   while(!fe.eof()) {
      fe >> cadena;
      cout << (int)cadena<<" ";
   	counter++;
   }
   fe.close();
   cout <<"counter : "<< counter << endl;

      return 0;
}