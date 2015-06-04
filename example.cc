#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

mat sigmoid(mat A) {
  return 1 / (1 + exp(-A));
}


int main() {

  /*mat pic = randu<mat>(756);

  pic.reshape(28,28);

  cout << pic <<endl;

  mat A = randu<mat>(4,5);
  mat B = randu<mat>(4,5);

  cout << A*B.t() << endl;
*/
  mat A = randu<mat>(5,5) * 100;
  A.print("A:");
  rowvec B = max(A);
  B.print("B:");
  A.each_row() /= B;
  A.print("C:");
  mat C = sigmoid(A);
  C.print("D:");
  return 0;
}
