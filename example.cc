#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
  {

  mat pic = randu<mat>(756);

  pic.reshape(28,28);

  cout << pic <<endl;

  mat A = randu<mat>(4,5);
  mat B = randu<mat>(4,5);
  
  cout << A*B.t() << endl;
  

  return 0;
  }