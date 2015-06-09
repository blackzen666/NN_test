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
  Name_out += "_swapped_endianness";
  ifstream in(argv[1], ios::binary);
  ofstream out(Name_out.c_str(), ios::binary);
  uchar readed;

  while(in >> readed)
    out << reverse(readed);

  in.close();
  out.close();
  /*
  in >> magic;// >> items;

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 8; j++) {
      if(magic[i] & 1 << j) cout<<"1";
      else cout<<"0";
    }
    cout<< " ";
  }
  cout<<endl;

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 8; j++) {
      if(reverse(magic[i]) & 1 << j) cout<<"1";
      else cout<<"0";
    }
    cout<< " ";
  }
  cout<<endl;
  */
  return 0;
}
