#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int n, t = 0;
vector<int> nodeOrder;

void TWOSAT (ifstream &input);
bool DFS (vector<vector<int> > &g, bool rev);
void DFS_rev (vector<vector<int> > &grev, int node, vector<bool> &checked);
bool DFS (vector<vector<int> > &g, int node, vector<bool> &checked, unordered_set<int> &hash);

int main (int argc, char *argv[]) {
  string path;
  string pre = "2sat";
  string post = ".txt";
  ifstream input;
  for (int i=1; i<=6; i++) {
    path = pre + to_string(i) + post;
    cout << path << endl;
    input.open(path);
    if (!input) {
      cerr << path << " open() failed" << endl;
      return 1;
    }
    TWOSAT (input);
    input.close();
  }
  // ifstream input ("test.txt");
  // TWOSAT (input);

  return 0;
}

bool DFS (vector<vector<int> > &g, bool rev) {
  vector<bool> checked = vector<bool>(n+n, false);
  // Compute reverse graph node order
  if (rev) {
    for (int i=0; i<n+n; i++) {
      if ( !checked[i] )
        DFS_rev(g, i, checked);
    }
  }
  // Compute SCC and check nodes in scc
  else {
    unordered_set<int> hash;
    for (int i=n+n-1; i>=0; i--) {
      if ( !checked[nodeOrder[i]] ) {
        hash.clear();
        if ( !DFS(g, nodeOrder[i], checked, hash) )
          return false;
      }
    } // Start from the last finished node
  }
  return true;
}

void DFS_rev(vector<vector<int> > &grev, int node, vector<bool> &checked) {
  checked[node] = true;
  for (unsigned i=0; i<grev[node].size(); i++) {
    if ( !checked[grev[node][i]] )
      DFS_rev (grev, grev[node][i], checked);
  }
  nodeOrder[t] = node;
  t++;
}

bool DFS (vector<vector<int> > &g, int node, vector<bool> &checked, unordered_set<int> &hash) {
  checked[node] = true;
  int xRev;
  if (node >= n) xRev = node-n;
  else xRev = node+n;
  if ( hash.find(xRev) != hash.end() ) {
    return false;
  }
  hash.insert(node);
  for (unsigned i=0; i<g[node].size(); i++) {
    if ( !checked[g[node][i]] ) {
      if ( !DFS (g, g[node][i], checked, hash) )
        return false;
    }
  }
  return true;
}

void TWOSAT (ifstream &input) {
  int x1, x2, y1, y2;
  t = 0;
  input >> n;
  vector<vector<int> > g (n+n, vector<int>());
  vector<vector<int> > grev (n+n, vector<int>());
  while (input >> x1) {
    input >> x2;
    if (x1 < 0) {
      y1 = x1*(-1) - 1;
      x1 = y1 + n;
    } else {
      y1 = x1 + n - 1;
      x1 = x1 - 1;
    }
    if (x2 < 0) {
      y2 = x2*(-1) - 1;
      x2 = y2 + n;
    } else {
      y2 = x2 + n - 1;
      x2 = x2 - 1;
    }
    g[y1].push_back(x2);
    grev[x2].push_back(y1);
    g[y2].push_back(x1);
    grev[x1].push_back(y2);
  }

  nodeOrder = vector<int>(n+n, -1);

  bool rev = true;
  // Compute order of complete in reverse graph
  DFS(grev, rev);
  rev = false;
  // Compute SCC
  bool sat = DFS(g, rev);
  cout << sat << endl;
}
