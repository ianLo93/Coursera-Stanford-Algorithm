#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <queue>

using namespace std;

class Status {
public:
  Status (int cover_, int head_, int tail_)
  {
    cover = cover_; head = head_; tail = tail_;
  }
  int cover;
  int head;
  int tail;
};

float eu_dist (pair<float, float> &v1, pair<float, float> &v2);
float tsp_dp (int n, vector<vector<vector<float> > > &dist, vector<vector<float> > &graph_d);

int main (int argc, char* argv[]) {
  ifstream input ("tsp1.txt");
  if (!input) {
    cerr << "file 1 open() failed.." << endl;
    return 1;
  }

  int n;
  float x, y;
  input >> n;
  vector<pair<float, float> > coords_1;
  while (input >> x) {
    input >> y;
    coords_1.push_back(make_pair(x, y));
  }
  vector<vector<float> > graph_d1(n, vector<float>(n, 0));
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (i != j) graph_d1[i][j] = eu_dist(coords_1[i], coords_1[j]);
    }
  }
  cout << "Graph_1 map set up success" << endl;

  vector<vector<vector<float> > > dist_1(1 << n, vector<vector<float> >(n, vector<float>(n, (float)INT_MAX)));
  cout << "Table_1 set up success" << endl;
  float min_d1 = tsp_dp(n, dist_1, graph_d1);
  cout << min_d1 << endl;

  input.close();

  cout << "First file complete" << endl;

  // ----------------------- First file complete -------------------------------------

  input.open("tsp2.txt");
  if (!input) {
    cerr << "file 2 open() failed.." << endl;
    return 1;
  }

  input >> n;
  vector<pair<float, float> > coords_2;
  while (input >> x) {
    input >> y;
    coords_2.push_back(make_pair(x, y));
  }
  vector<vector<float> > graph_d2(n, vector<float>(n, 0));
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (i != j) graph_d2[i][j] = eu_dist(coords_2[i], coords_2[j]);
    }
  }
  cout << "Graph_2 map set up success" << endl;

  vector<vector<vector<float> > > dist_2(1 << n, vector<vector<float> >(n, vector<float>(n, (float)INT_MAX)));
  cout << "Table_2 set up success" << endl;

  float min_d2 = tsp_dp(n, dist_2, graph_d2);
  cout << min_d2 << endl;
  input.close();
  cout << "Second file complete" << endl;

  float min_d = min_d1 + min_d2 - 2*graph_d2[0][1];
  cout << (int)min_d << endl;

  return 0;
}

float eu_dist (pair<float, float> &v1, pair<float, float> &v2) {
  float x = v1.first-v2.first;
  float y = v1.second-v2.second;
  return sqrt(x*x + y*y);
}

float tsp_dp (int n, vector<vector<vector<float> > > &dist, vector<vector<float> > &graph_d) {
  queue<Status> fringe;
  for (int i=0; i<n; i++) {
    dist[1 << i][i][i] = 0;
    fringe.push(Status(1 << i, i, i));
  }

  int cover, head, tail;
  float d;
  while ( !fringe.empty() ) {
    cover = fringe.front().cover;
    head = fringe.front().head;
    tail = fringe.front().tail;
    fringe.pop();
    if (cover == (1 << n) - 1) continue;
    d = dist[cover][head][tail];
    for (int i=0; i<n; i++) {
      if (i == tail || i == head) continue; // No need to calculate self repeatedly
      int cover_ = cover | (1 << i);
      if (cover_ == cover) continue;
      if (d+graph_d[tail][i] < dist[cover_][head][i]) {
        dist[cover_][head][i] = d+graph_d[tail][i];
        fringe.push(Status(cover_, head, i));
      } // The new dist is smaller
    } // Check next position, extend tails
  }

  float min_d = (float)INT_MAX;
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (i == j) continue;
      d = dist[(1<<n)-1][i][j] + graph_d[j][i];
      if (d < min_d) min_d = d;
    }
  }

  return min_d;
}
