// Perfectly solve the 25 locations TSP problem from "tsp.txt"!
#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <queue>

using namespace std;
typedef vector<vector<float> > FLOAT_VEC;

class Status {
public:
  Status (int cover_, int tail_) { cover = cover_; tail = tail_; }
  int cover;
  int tail;
};

float eu_dist (pair<float, float> &v1, pair<float, float> &v2);
float tsp_dp (int n, int head, FLOAT_VEC &dist, FLOAT_VEC &graph_d, queue<Status>& fringe);

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
  cout << "Graph map setup succeeded" << endl;

  FLOAT_VEC dist(1 << n, vector<float>(n, (float)INT_MAX));
  cout << "Table setup succeeded" << endl;

  queue<Status> fringe;
  int head = 0; // Can be any nodes in the graph
  dist[1 << head][head] = 0;
  fringe.push(Status(1 << head, head));
  float min_d = tsp_dp(n, 0, dist, graph_d, fringe);

  input.close();

  cout << "File complete" << endl;

  cout << "The shortest TSP path length(Round down to integer): "
        << (int)min_d << endl;

  return 0;
}

float eu_dist (pair<float, float> &v1, pair<float, float> &v2) {
  float x = v1.first-v2.first;
  float y = v1.second-v2.second;
  return sqrt(x*x + y*y);
}

float tsp_dp (int n, int head, FLOAT_VEC &dist, FLOAT_VEC &graph_d, queue<Status>& fringe) {
  int cover, tail, check=1;
  float d;
  // Dynamically get the value from subroutines
  while ( 1 ) {
    cover = fringe.front().cover;
    tail = fringe.front().tail;
    if (cover >= 1 << check) {
      cout << "Phase " << check << " completed" << endl;
      check++;
    }
    if (cover == (1 << n) - 1) break;
    fringe.pop();
    d = dist[cover][tail];
    for (int i=0; i<n; i++) {
      int cover_ = cover | (1 << i);
      if (cover_ == cover) continue;
      if (d+graph_d[tail][i] < dist[cover_][i]) {
        dist[cover_][i] = d+graph_d[tail][i];
        fringe.push(Status(cover_, i));
      } // The new dist is smaller
    } // Check next position, extend tails
  }
  // Finish the rest fringe and get the results
  float min_d = (float)INT_MAX;
  while (!fringe.empty()) {
    cover = fringe.front().cover;
    tail = fringe.front().tail;
    fringe.pop();
    d = dist[cover][tail] + graph_d[tail][head];
    if (d < min_d) min_d = d;
  }

  return min_d;
}
