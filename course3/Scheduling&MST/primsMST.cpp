#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <vector>

using namespace std;

vector<pair<bool, int> > heap_pos;

void percolate_up (vector<pair<int, int> >& v_heap, int pos);
void percolate_down (vector<pair<int, int> >& v_heap, int pos);
void insert (vector<pair<int, int> >& v_heap, pair<int, int>& val);
pair<int, int> pop (vector<pair<int, int> >& v_heap);
void del (vector<pair<int, int> >& v_heap, int node);
void printG (vector<vector<pair<int, int> > >& data);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Command error.." << endl;
    return 1;
  }

  FILE* input = fopen(argv[1], "r");
  if (!input) {
    cerr << "open() failed.." << endl;
    return 1;
  }

  int v, e;
  fscanf(input, "%d %d", &v, &e);
  int v1, v2, cost;
  vector<pair<int, int> > temp;
  vector<vector<pair<int, int> > > data(v, temp);
  while (fscanf(input, "%d %d %d", &v1, &v2, &cost) > 0) {
    data[v1-1].push_back(make_pair(v2-1, cost));
    data[v2-1].push_back(make_pair(v1-1, cost));
  }

  // printG(data);
  long mstCost = 0;
  vector<pair<int, int> > v_heap;
  for (int i=0; i<v; i++) heap_pos.push_back(make_pair(false, -1));
  pair<int, int> val = make_pair(0, 0);
  insert(v_heap, val);

  int k = 0;
  while (k != v) {
    pair<int,int> ans = pop(v_heap);
    int c = ans.second;
    int n = ans.first;
    // cout << n << endl;
    for (int j=0; j<data[n].size(); j++) {
      int next_n = data[n][j].first;
      int next_c = data[n][j].second;
      if (heap_pos[next_n].first) {
        // cout << n << " " << next_n << endl;
        continue;
      }
      int next_pos = heap_pos[next_n].second;
      val = make_pair(next_n, next_c);
      if (heap_pos[next_n].second == -1) insert(v_heap, val);
      else if (next_c < v_heap[next_pos].second) {
        del (v_heap, next_pos);
        insert (v_heap, val);
      }
      else {}
    }
    // for (int i=0; i<v_heap.size(); i++) {
    //   cout << v_heap[i].first << "," << v_heap[i].second << " ";
    // }
    // cout << endl;
    // pop(v_heap);
    // cout << v_heap[0].first << " " << v_heap[0].second << endl;
    mstCost += c;
    k++;
  }

  cout << mstCost << endl;

  return 0;
}

void printG (vector<vector<pair<int, int> > >& data) {
  for (int i=0; i<data.size(); i++) {
    cout << i << " ";
    for (int j=0; j<data[i].size(); j++) {
      cout << data[i][j].first << "," << data[i][j].second << " ";
    }
    cout << endl;
  }
}

void percolate_up (vector<pair<int,int> >& v_heap, int pos) {
  if (pos == 0) return;
  while ( v_heap[(pos-1)/2].second > v_heap[pos].second ) {
    heap_pos[v_heap[pos].first].second = (pos-1)/2;
    heap_pos[v_heap[(pos-1)/2].first].second = pos;
    swap (v_heap[pos], v_heap[(pos-1)/2]);
    pos = (pos-1)/2;
    if (pos == 0) break;
  }
}

void percolate_down (vector<pair<int, int> >& v_heap, int pos) {
  int child;
  while (2*pos+1 < v_heap.size()) {
    if (2*pos+2 < v_heap.size() && v_heap[2*pos+2].second < v_heap[2*pos+1].second)
      child = 2*pos+2;
    else
      child = 2*pos+1;
    if (v_heap[pos].second > v_heap[child].second) {
      heap_pos[v_heap[pos].first].second = child;
      heap_pos[v_heap[child].first].second = pos;
      swap (v_heap[pos], v_heap[child]);
      pos = child;
    }
    else break;
  }
}

void insert (vector<pair<int, int> >& v_heap, pair<int, int>& val) {
  v_heap.push_back(val);
  int pos = v_heap.size()-1;
  heap_pos[val.first].second = pos;
  percolate_up (v_heap, pos);
}

pair<int, int> pop (vector<pair<int, int> >& v_heap) {
  pair<int, int> ans = v_heap[0];
  heap_pos[v_heap[0].first].first = true;
  int last = v_heap.size()-1;
  heap_pos[v_heap[last].first].second = 0;
  swap(v_heap[0], v_heap[last]);
  v_heap.pop_back();
  // cout << v_heap[0].first << " ";
  percolate_down(v_heap, 0);
  // cout << v_heap[0].first << endl;
  return ans;
}

void del (vector<pair<int, int> >& v_heap, int pos) {
  int last = v_heap.size()-1;
  heap_pos[v_heap[last].first].second = pos;
  swap(v_heap[pos], v_heap[last]);
  v_heap.pop_back();
  percolate_up(v_heap, pos);
  percolate_down(v_heap, pos);
}
