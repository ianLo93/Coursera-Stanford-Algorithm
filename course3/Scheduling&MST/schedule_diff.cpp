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
  int f = 0;
  while (fscanf(input, "%f %f", &w, &t) > 0) {
    data[(w-t)].push_back(w);
  }

  int compTime = 0;
  long wCompTime = 0;
  map<float, vector<float> >::reverse_iterator it=data.rbegin();
  for (; it != data.rend(); it++) {
    // cout << it->first << " ";
    sort((it->second).begin(), (it->second).end());
    int n = it->second.size();
    for (int i=n-1; i>=0; i--) {
      int ftime = (it->first - it->second[i]) * (-1);
      // cout << ftime << endl;
      compTime += ftime;
      wCompTime += (int)(it->second)[i] * compTime;
      // cout << f << " " << wCompTime << " " << compTime << " " << it->second[i] << endl;
      f++;
      // cout << it->second[i] << "," << ftime << " ";
    }
    // cout << endl;
  }

  cout << wCompTime << endl;

  return 0;
}
