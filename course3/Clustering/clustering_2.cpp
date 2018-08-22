#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
typedef vector<pair<int, int> > VEC_P;
typedef unordered_map<string, vector<int> > DICT;

int r_find (VEC_P& clusters, int node)
{
  int root, parent = clusters[node].first;
  if (parent != node) {
    root = r_find (clusters, parent);
    clusters[node].first = root;
    return root;
  }
  else return node;
}

void c_union (VEC_P& clusters, int r1, int r2)
{
  if (clusters[r1].second < clusters[r2].second) {
    clusters[r1].first = r2;
  } else if (clusters[r1].second > clusters[r2].second){
    clusters[r2].first = r1;
  } else {
    clusters[r1].second++;
    clusters[r2].first = r1;
  }
}

int main (int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Command Error..." << endl;
    return 1;
  }

  ifstream input(argv[1]);
  if (!input) {
    cerr << "open() failed..." << endl;
    return 1;
  }

  int nodes, n_bits;
  input >> nodes;
  input >> n_bits;

  string code;
  char c;
  DICT table;
  int node = 0;
  pair<int, int> temp;
  VEC_P clusters(nodes, temp);

  while (input >> c)
  {
    code.push_back(c);
    for (int i=0; i<n_bits-1; i++) {
      input >> c;
      code.push_back(c);
    }
    table[code].push_back(node);
    clusters[node].first = node;
    clusters[node].second = 0;
    node++;
    code.clear();
  }

  DICT::iterator it = table.begin();
  while ( table.size() )
  {
    int r1, r2;
    for (int i=1; i<it->second.size(); i++) {
      r1 = r_find (clusters, it->second[0]);
      r2 = r_find (clusters, it->second[i]);
      if (r1 != r2) {
        c_union (clusters, r1, r2);
        nodes--;
      }
    }
    for (int i=0; i<n_bits; i++) {
      string m_code = it->first;
      if (m_code[i] == '0') m_code[i] = '1';
      else m_code[i] = '0';
      DICT::iterator it1 = table.find(m_code);
      if ( it1 != table.end() ) {
        for (int j=0; j<it1->second.size(); j++) {
          r1 = r_find (clusters, it->second[0]);
          r2 = r_find (clusters, it1->second[j]);
          if (r1 != r2) {
            c_union (clusters, r1, r2);
            nodes--;
          }
        } // Unite all nodes of the first modified code
      } // The code doesn't exist, check 2 differ
      for (int j=i+1; j<n_bits; j++) {
        string m1_code = m_code;
        if (m1_code[j] == '0') m1_code[j] = '1';
        else m1_code[j] = '0';
        DICT::iterator it2 = table.find(m1_code);
        if ( it2 == table.end() ) continue;
        for (int k=0; k<it2->second.size(); k++) {
          r1 = r_find (clusters, it->second[0]);
          r2 = r_find (clusters, it2->second[k]);
          if (r1 != r2) {
            c_union (clusters, r1, r2);
            nodes--;
          }
        } // Unite all nodes of the second modified code
      } // Dist 2
    } // Dist 1
    it = table.erase(it);
  }

  cout << nodes << endl;

  return 0;
}
