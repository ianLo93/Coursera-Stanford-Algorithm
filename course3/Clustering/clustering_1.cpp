#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

#define K 4
using namespace std;
typedef vector<pair<int, int> > VEC_P;
typedef map<int, VEC_P> EDGE_MAP;

int p_find (VEC_P& pr, int node);
void c_union (VEC_P& pr, int r1, int r2);

int main (int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Command Error..." << endl;
    return 1;
  }

  FILE* input = fopen(argv[1], "r");
  if (!input) {
    cerr << "open() failed.." << endl;
    return 1;
  }

  int nodes;
  fscanf(input, "%d", &nodes);
  pair<int, int> temp;
  VEC_P pr(nodes, temp);
  for (int i=0; i<nodes; i++) {
    pr[i].first = i;
    pr[i].second = 0;
  }
  int v1, v2, cost;
  EDGE_MAP edges;

  while (fscanf(input, "%d %d %d", &v1, &v2, &cost) > 0) {
    edges[cost].push_back(make_pair(v1-1, v2-1));
  }

  EDGE_MAP::iterator it = edges.begin();

  bool fin = false;
  int max_space = -1;
  for (; it != edges.end(); it++) {
    for (int i=0; i<it->second.size(); i++) {
      int r1 = p_find(pr, it->second[i].first);
      int r2 = p_find(pr, it->second[i].second);
      if (r1 == r2) continue;
      if (fin) {
        max_space = it->first;
        break;
      } else {
        c_union (pr, r1, r2);
        nodes--;
        if (nodes == K) fin = true;
      }
    }
    if (max_space != -1) break;
  }

  cout << max_space << endl;

  return 0;
}

int p_find (VEC_P& pr, int node) {
  int root;
  if (pr[node].first != node) {
    root = p_find(pr, pr[node].first);
    pr[node].first = root;
  }
  else
    root = node;
  return root;
}

void c_union (VEC_P& pr, int r1, int r2) {
  if (pr[r1].second > pr[r2].second)
    pr[r2].first = r1;
  else if (pr[r1].second < pr[r2].second)
    pr[r1].first = r2;
  else {
    pr[r1].second++;
    pr[r2].first = r1;
  }
}
