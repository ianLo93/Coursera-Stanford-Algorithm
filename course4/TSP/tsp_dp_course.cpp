#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<vector<float> > FLOAT_VEC;
float eu_dist (pair<float, float> &v1, pair<float, float> &v2);
float tsp_dp (int n, int head, FLOAT_VEC &graph_d, FLOAT_VEC &dist);

int main (int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Command Error" << endl;
    return 1;
  }
  ifstream input (argv[1]);
  if (!input) {
    cerr << "open() failed.." << endl;
    return 1;
  }

  int n;
  float x, y;
  input >> n;
  FLOAT_VEC dist(1 << n, vector<float>(n, (float)INT_MAX));

  vector<pair<float, float> > coords;
  while (input >> x) {
    input >> y;
    coords.push_back( make_pair(x, y) );
  } // Get the coordinates
  FLOAT_VEC graph_d(n, vector<float>(n, 0));
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (i != j) graph_d[i][j] = eu_dist(coords[i], coords[j]);
    }
  } // Get the graph map

  float min_d = tsp_dp (n, 0, graph_d, dist);
  cout << min_d << endl;

  return 0;
}

float eu_dist (pair<float, float> &v1, pair<float, float> &v2) {
  float x = v1.first-v2.first;
  float y = v1.second-v2.second;
  return sqrt(x*x + y*y);
}

float tsp_dp (int n, int head, FLOAT_VEC &graph_d, FLOAT_VEC &dist)
{
  queue<int> fringe;
  fringe.push(1 << head);
  dist[1 << head][head] = 0;
  int cover, check = 1;
  float min_d;
  while ( 1 ) {
    cover = fringe.front();
    if (cover >= 1 << check) {
      cout << "Phase " << check << endl;
      cout << "fringe: " << fringe.size() << endl;
      check++;
    }
    fringe.pop();
    if ( cover == (1 << n) - 1 )
      break;
    for (int j=1; j < n; j++) {
      int cover_ = cover | (1 << j);
      if (cover_ == cover) continue;
      min_d = (float)INT_MAX;
      for (int k=0; k < n; k++) {
        if (k == j) continue;
        if ( (cover | (1 << k)) == cover ) {
          float d = dist[cover][k] + graph_d[k][j];
          if (d < min_d) min_d = d;
        } // Check if k is in the set
      } // Get the minimum dist
      dist[cover_][j] = min_d;
      fringe.push(cover_);
    }
  } // When it runs out of fringe, we had the table filled

  min_d = (float)INT_MAX;
  for (int k=0; k<n; k++) {
    if (dist[(1 << n)-1][k] + graph_d[k][head] < min_d)
      min_d = dist[(1 << n)-1][k] + graph_d[k][head];
  }

  return min_d;
}
