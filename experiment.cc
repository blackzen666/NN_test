#include <iostream>
#include <armadillo>
#include <netinet/in.h>
#include <bitset>



using namespace std;
using namespace arma;

mat sigmoid(mat A) {
  return 1 / (1 + exp(-A));
}


int reverseInt (int i) {
  unsigned char c1, c2, c3, c4;

  c1 = i & 255;
  c2 = (i >> 8) & 255;
  c3 = (i >> 16) & 255;
  c4 = (i >> 24) & 255;

  return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}


void read_mnist_labels(mat &data) {
  // ifstream file ("t10k-images_unzip");
  

  ifstream file ("dataset/t10k-labels");
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


    int counter = 0;

    unsigned char  cadena;

////matriz definition because of element read
    data = zeros<mat>(number_of_images,1);

    while(!file.eof()) {

      file.read((char*)&cadena,sizeof(char));
      int pixel= cadena;
      
      if(counter < number_of_images - 1){
      		//std::cout << pixel << endl;
      		data(counter,0)= pixel;
      		//cout<< data(counter,0) <<endl;
      	}
      counter++;
    }
    /*cout <<data(0,0)<<endl;
    cout <<data(1,0)<<endl;
    cout <<data(2,0)<<endl;
    cout <<data(3,0)<<endl;
    cout <<size(data)<<endl;*/

  	 	
    cout <<"read counter: "<<counter <<endl;
	}
}


void read_mnist_images(mat &data) {
  // ifstream file ();
  

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


    int counter = 0;

    unsigned char  cadena;

////matriz definition because of element read
    data = zeros<mat>(number_of_images,1);

    while(!file.eof()) {

      file.read((char*)&cadena,sizeof(char));
      int pixel= cadena;
      
      if(counter < number_of_images - 1){
      		//std::cout << pixel << endl;
      		data(counter,0)= pixel;
      		//cout<< data(counter,0) <<endl;
      	}
      counter++;
    }
    
    data.reshape(n_cols*n_rows,number_of_images);
    mat bias = ones<mat>(1,number_of_images);
  	data = join_vert(data,bias);
  	cout << size(data) <<endl;

  	 	
    cout <<"read counter: "<<counter <<endl;
	}
}








int main() {

  int num = 1;
  if(*(char *)&num == 1) {
    printf("\nLittle-Endian\n");
  }
  else {
    printf("Big-Endian\n");
  }

  /// TRUE SI SON IMAGENES
  // read_mnist_data(string path,bool train_images)
  //   http://www.codeproject.com/Questions/601150/HowplustoplusreadpluspixelsplusfromplusMNISTplusdi

	mat X;
	mat Y;

  
	read_mnist_labels(Y);
	read_mnist_images(X);
  
  return 0;
}
