// 1.0: I screwed it
// 2.0: I make it!!! But it's very slow
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <queue>

using namespace std;

typedef vector<vector<float> > FLOAT_VEC;
typedef unordered_map<int, FLOAT_VEC> BIT_MAP;

float eu_dist (pair<float, float> &v1, pair<float, float> &v2);
float tsp_dp (int n, BIT_MAP* dist, FLOAT_VEC &graph_d);

int main (int argc, char* argv[]) {
  ifstream input (argv[1]);
  if (!input) {
    cerr << "file 1 open() failed.." << endl;
    return 1;
  }

  int n;
  float x, y;
  input >> n;
  vector<pair<float, float> > coords;
  while (input >> x) {
    input >> y;
    coords.push_back(make_pair(x, y));
  }

  FLOAT_VEC graph_d(n, vector<float>(n, 0));
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (i != j) graph_d[i][j] = eu_dist(coords[i], coords[j]);
    }
  }
  cout << "Graph map set up succeeded" << endl;

  BIT_MAP* dist = new BIT_MAP;
  // Base case: Head and tail are the same node, only one node sets in the table
  for (int i=0; i<n; i++) {
    (*dist)[1 << i] = FLOAT_VEC(n, vector<float>(n, -1.0));
    (*dist)[1 << i][i][i] = 0;
  }
  cout << "Base case set up succeeded" << endl;

  float min_d = tsp_dp(n, dist, graph_d);
  cout << min_d << endl;

  input.close();

  cout << "File completed" << endl;

  cout << (int)min_d << endl;

  return 0;
}

float eu_dist (pair<float, float> &v1, pair<float, float> &v2) {
  float x = v1.first-v2.first;
  float y = v1.second-v2.second;
  return sqrt(x*x + y*y);
}

float tsp_dp (int n, BIT_MAP* dist, FLOAT_VEC &graph_d) {
  int cover, check = 1;
  float d;
  while ( 1 ) {
    BIT_MAP::iterator it = (*dist).begin();
    cout << "Phase check " << check << " completed" << endl;
    // cout << "The cover: " << it->first << " we want: " << (1 << n) - 1 << endl;
    check++;
    if (it->first == (1 << n) - 1) break;

    BIT_MAP* second = new BIT_MAP;
    for (; it != (*dist).end(); it++) {
      cover = it->first;
      for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
          if ((*dist)[cover][i][j] >= 0) {
            float d = (*dist)[cover][i][j];
            for (int k=0; k<n; k++) {
              int cover_ = cover | (1 << k);
              if (cover_ == cover) continue;
              if ((*second).find(cover_) == (*second).end()) {
                (*second)[cover_] = FLOAT_VEC(n, vector<float>(n, -1.0));
                (*second)[cover_][i][k] = d+graph_d[j][k];
              } // The path is not there
              else {
                float old_d = (*second)[cover_][i][k];
                if (d+graph_d[j][k] < old_d || old_d < 0.0)
                  (*second)[cover_][i][k] = d+graph_d[j][k];
              } // The path is already there
            } // k
          } // If the value is not define, skip
        } // j
      } // i
    } // Extend paths
    // Now we swap the pointers, the dist is now useless, release the memory
    BIT_MAP *p = dist;
    dist = second;
    delete p;
  }

  float min_d = (float)INT_MAX;
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (i == j) continue;
      d = (*dist)[(1<<n)-1][i][j] + graph_d[j][i];
      if (d < min_d) min_d = d;
    }
  }

  return min_d;
}
