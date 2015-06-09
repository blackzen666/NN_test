#include <bits/stdc++.h>
using namespace std;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
#define endl '\n'

typedef unsigned char uchar;

uchar reverse(uchar b) {
  b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
  b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
  b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
  return b;
}

int main(int argc, char **argv) {
  string Name_out(argv[1]);
  //Name_out += "_swapped_endianness";
  ifstream in(argv[1], ios::binary);
  //ofstream out(Name_out.c_str(), ios::binary);
  uchar readed;
  int count = 0, maxi = 0;
  while(in.read((char *)&readed, sizeof(char))) {
    //printf("%d\n", (int)readed);
    maxi = max((int)readed, maxi);
    //out << reverse(readed);
    count++;
  }
  cout<<maxi<<endl;
  cout<<count<<endl;
  in.close();
  return 0;
}
