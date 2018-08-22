#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Command Error.." << endl;
    return 1;
  }

  ifstream input(argv[1]);
  if (!input) {
    cerr << "open() failed.." << endl;
    return 1;
  }

  int nodes, edges;
  input >> nodes >> edges;
  int **first = new int*[nodes];
  int **second = new int*[nodes];
  for (int i=0; i<nodes; i++) {
    first[i] = new int[nodes];
    second[i] = new int[nodes];
  }
  for (int i=0; i<nodes; i++) {
    for (int j=0; j<nodes; j++) {
      if (i == j) first[i][j] = 0;
      else first[i][j] = INT_MAX;
    }
  }

  int v1, v2, c;
  while (input >> v1) {
    input >> v2 >> c;
    first[v1-1][v2-1] = c;
  }

  for (int k=0; k<nodes; k++) {
    for (int i=0; i<nodes; i++) {
      for (int j=0; j<nodes; j++) {
        int c1, c2, val;
        c1 = first[i][j];
        if (first[i][k] != INT_MAX && first[k][j] != INT_MAX)
          c2 = first[i][k] + first[k][j];
        else c2 = INT_MAX;
        if (c1 < c2) val = c1;
        else val = c2;
        second[i][j] = val;
      }
    } // Update the first
    int **p_tmp = first;
    first = second;
    second = p_tmp;
  } // V(k) is allowed

  int min_v = first[0][0];
  for (int i=0; i<nodes; i++) {
    if (first[i][i] < 0) {
      min_v = INT_MIN;
      break;
    }
    for (int j=0; j<nodes; j++) {
      if (first[i][j] < min_v) min_v = first[i][j];
      // cout << first[i][j] << " ";
    }
    // cout << endl;
  } // Get the minimum path val;

  if (min_v == INT_MIN) cout << "NEGATIVE CYCLE DETECTED" << endl;
  else cout << min_v << endl;

  return 0;
}
