/* Better dynamic programming:
Throw away redundant caching works to reduce memory and running time */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Command error" << endl;
    return 1;
  }
  ifstream input(argv[1]);
  if (!input) {
    cerr << "open() failed.." << endl;
    return 1;
  }

  int k_size, n_items, w = 0, i = 0;
  long long val, weight;
  input >> k_size >> n_items;
  // Create two memorizing array to cache
  int *first = new int[k_size+1];
  int *second = new int[k_size+1];

  // Item loop
  while (input >> val) {
    input >> weight;
    // Weight loop
    for (w = 0; w<k_size+1; w++) {
      int v1 = 0, v2 = 0, v;
      v1 = first[w];
      if (w >= weight) v2 = first[w-weight] + val;
      if (v1 > v2) v = v1;
      else v = v2;
      second[w] = v;
    }
    // Swap the two array
    int *pt_tmp = first;
    first = second;
    second = pt_tmp;
  }

  cout << first[k_size] << endl;

  return 0;
}
