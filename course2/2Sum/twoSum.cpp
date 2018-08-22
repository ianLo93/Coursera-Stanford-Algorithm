#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <climits>

using namespace std;

int LOW = -10000;
int HIGH = 10000;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Command error.." << endl;
    return 1;
  }

  fstream input(argv[1]);
  if (!input) {
    cerr << "open() failed.." << endl;
    return 1;
  }

  vector<long> data;
  unordered_set<long> hash_table;
  long num;
  while (input >> num) {
    data.push_back(num);
    hash_table.insert(num);
  }

  int count = 0;
  for (int t=LOW; t<=HIGH; t++) {
    for (int i=0; i<data.size(); i++) {
      long k = data[i];
      long target = t-k;
      auto it = hash_table.find(target);
      if (it != hash_table.end() && *it != k) {
        count++;
        break;
      }
    }
  }
  cout << count << endl;

  return 0;
}
