#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

long wis_dp (vector<int> &w, vector<long> &mem, int r);
vector<bool> retrieve (vector<long> &mem, vector<int> &w);

int main (int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Command error.." << endl;
    return 1;
  }
  ifstream input (argv[1]);
  if (!input) {
    cerr << "open() failed.." << endl;
    return 1;
  }

  vector<int> weights;
  int val, num;
  input >> num;
  while (input >> val) {
    weights.push_back(val);
  }

  vector<long> mem(num, -1);
  wis_dp(weights, mem, weights.size()-1);
  vector<bool> ans = retrieve (mem, weights);
  vector<int> index = {1, 2, 3, 4, 17, 117, 517, 997};
  for (int i=0; i<index.size(); i++) {
    cout << ans[index[i]-1];
  }
  cout << endl;

  return 0;
}

long wis_dp (vector<int> &w, vector<long> &mem, int r) {
  if (r == 0) {
    mem[0] = w[0];
    return w[0];
  }
  long first = 0, second = w[r];
  if (r-1 >= 0) {
    if (mem[r-1] != -1) first = mem[r-1];
    else first = wis_dp (w, mem, r-1);
  }
  if (r-2 >= 0) {
    if (mem[r-2] != -1) second += mem[r-2];
    else second += wis_dp (w, mem, r-2);
  }
  if (first > second) {
    mem[r] = first;
    return first;
  }
  else {
    mem[r] = second;
    return second;
  }
}

vector<bool> retrieve (vector<long> &mem, vector<int> &w) {
  vector<bool> ans(mem.size(), 0);
  int i = mem.size()-1;
  while (i > 1) {
    if (mem[i-1] >= mem[i-2] + w[i])
      i--;
    else {
      ans[i] = 1;
      i -= 2;
    }
  }
  if (i == 1 && mem[i] == mem[i-1]) ans[0] = true;
  else if (i == 1) ans[1] = true;
  else ans[0] = true;

  return ans;
}
