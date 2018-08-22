#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <cstdio>
#include <set>
#include <vector>

using namespace std;

int SIZE = 875714;
unordered_map<int, int> f;
bool visited[875714] = { false };
int t = 0;

void finDFS(vector<vector<int> >& grev, int node) {
  visited[node] = true;
  for (unsigned int i=0; i<grev[node].size(); i++) {
    if (!visited[grev[node][i]]) finDFS(grev, grev[node][i]);
  }
  f[t] = node;
  t++;
}

void finishTime(vector<vector<int> >& grev) {
  for (int i=SIZE-1; i>=0; i--) {
    if (!visited[i]) finDFS(grev, i);
  }
}

void exploreSCC(vector<vector<int> >& g, int node) {
  if (visited[node]) return;
  t++;
  visited[node] = true;
  for (unsigned int i=0; i<g[node].size(); i++) {
    if (!visited[g[node][i]]) exploreSCC(g, g[node][i]);
  }
}

set<int> findSCC(vector<vector<int> >& g) {
  set<int> sccSize;
  for (int i=SIZE-1; i>=0; i--) {
    if (!visited[f[i]]) {
      t = 0;
      exploreSCC(g, f[i]);
      sccSize.insert(t);
    }
  }
  return sccSize;
}


int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Command error.." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  if (!input) {
    cerr << "open() failed.." << endl;
    return 1;
  }

  vector<vector<int> > g;
  vector<vector<int> > grev;

  for (int i=0; i<SIZE; i++) {
    vector<int> temp;
    g.push_back(temp);
    grev.push_back(temp);
  }

  int tail;
  int head;
  while (input >> tail) {
    input >> head;
    g[tail-1].push_back(head-1);
    grev[head-1].push_back(tail-1);
  }
  finishTime(grev);
  memset(visited, false, sizeof(visited));

  set<int> ans = findSCC(g);
  for (set<int>::iterator it = ans.begin(); it != ans.end(); it++) cout << *it << " ";
  cout << endl;

  return 0;
}
