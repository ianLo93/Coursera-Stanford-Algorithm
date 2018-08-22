#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <queue>

using namespace std;
typedef pair<int, double> VT;

class Compare {
public:
  bool operator() (VT &p1, VT &p2) {
    return p1.second > p2.second ||
          (p1.second == p2.second && p1.first > p2.first);
  }
};

double eu_dist_sq(pair<double, double> &p1, pair<double, double> &p2);
VT closestNode(unordered_map<int, pair<double, double> > &vertices, int k);

int main ( int argc, char* argv[] ) {
  if (argc != 2) {
    cerr << "Command Error" << endl;
    return 1;
  }
  ifstream input(argv[1]);
  if (!input) {
    cerr << "open() failed" << endl;
    return 1;
  }

  // Read vertices
  int n, v = 0;
  input >> n;
  double x, y;
  unordered_map<int, pair<double, double> > vertices;
  while (input >> v) {
    input >> x >> y;
    auto tmp = make_pair(x, y);
    vertices[v] = tmp;
  }

  // Computes closest vertex not in previous tour
  pair<double, double> start = vertices[1];
  int k = 1;
  double c = 0;
  while (vertices.size() > 1) {
    auto p = closestNode(vertices, k);
    k = p.first;
    c += sqrt(p.second);
  }
  pair<double, double> end = vertices[k];
  double d = eu_dist_sq(start, end);
  c += sqrt(d);

  cout << (long)c << endl;
  cout << c << endl;

  return 0;
}

double eu_dist_sq(pair<double, double> &p1, pair<double, double> &p2) {
  double x = p1.first-p2.first;
  double y = p1.second-p2.second;
  return x*x+y*y;
}

VT closestNode(unordered_map<int, pair<double, double> > &vertices, int k) {
  auto it = vertices.find(k);
  double x = it->second.first;
  double y = it->second.second;
  auto p = make_pair(x, y);
  vertices.erase(it);
  priority_queue<VT, vector<VT>, Compare> q;
  it = vertices.begin();
  for (; it != vertices.end(); it++) {
    double d = eu_dist_sq(p, it->second);
    // cout << d << endl;
    auto tmp = make_pair(it->first, d);
    q.push(tmp);
  }
  // cout << "Boil down to: " << q.top().second << endl;
  return q.top();
}
