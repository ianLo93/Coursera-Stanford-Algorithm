#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Command error.." << endl;
    return 1;
  }

  FILE* input = fopen(argv[1], "r");
  if (!input) {
    cerr << "open() failed.." << endl;
    return 1;
  }

  int num;
  fscanf(input, "%d", &num);
  map<float, vector<float> > data;
  float w, t;
  int k = 0;
  while (fscanf(input, "%f %f", &w, &t) > 0) {
    data[(t/w)].push_back(-w);
  }

  int compTime = 0;
  long wCompTime = 0;
  map<float, vector<float> >::iterator it=data.begin();
  for (; it != data.end(); it++) {
    sort((it->second).begin(), (it->second).end());
    for (int i=0; i<it->second.size(); i++) {
      float ftime = (it->first)*(it->second[i])*(-1);
      // cout << ftime << endl;
      compTime += ftime;
      wCompTime += (-1) * (int)(it->second[i]) * compTime;
    }
  }

  cout << wCompTime << endl;

  return 0;
}
