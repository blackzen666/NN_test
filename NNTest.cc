#include <bits/stdc++.h>
#include <armadillo>

using namespace std;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
#define endl '\n'

vec train(vec inputs, vec outputs) {
  vec res = feed_forward(inputs);

  vec deltaOutput = res*(1 - res) * (answer - result);
}

int main(){__
  int hidden_neurons = 40, hidden_layer = 1;
  vec Inputs = ones<vec>(785); // 28 x 28 + bias
  vec Hidden = randu<vec>(hidden_neurons);
  vec output = zeros<vec>(10);

  vec tmp = zeros<vec>(Hidden.n_elemn);
  for(int i = 0; i < hidden_neurons; i++) {
    tmp[i] = sum(Inputs * Hidden[i]);
  }

  return 0;
}
