#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

void percolate_up (vector<int> & data, int pos);
void percolate_down (vector<int> & data, int pos);
int pop (vector<int> & data);
void push (vector<int> & data, int val);

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

  vector<int> max_heap;
  vector<int> min_heap;

  int num=0, sum=0;
  input >> num;
  max_heap.push_back(num*(-1));
  sum += num;
  while (input >> num) {
    if (num > max_heap[0]*(-1)) push(min_heap, num);
    else push(max_heap, num*(-1));
    int s1 = max_heap.size();
    int s2 = min_heap.size();
    if ( abs(s1 - s2) >= 2 ) {
      int temp;
      if (s1 > s2) {
        temp = pop(max_heap)*(-1);
        push(min_heap, temp);
      } else {
        temp = pop(min_heap)*(-1);
        push(max_heap, temp);
      }
    }
    s1 = max_heap.size();
    s2 = min_heap.size();
    int g;
    if (s1 >= s2)
      g = max_heap[0]*(-1);
    else g = min_heap[0];
    sum += g;
  }
  cout << sum%10000 << endl;

  return 0;
}

void percolate_up (vector<int>& data, int pos) {
  if (pos == 0) return;
  while (data[(pos-1)/2] > data[pos]) {
    swap (data[(pos-1)/2], data[pos]);
    pos = (pos-1)/2;
    if (pos == 0) break;
  }
}

void percolate_down (vector<int>& data, int pos) {
  while (2*pos+1 < data.size()) {
    int child;
    if (2*pos+2 < data.size() && data[2*pos+2] < data[2*pos+1])
      child = 2*pos+2;
    else child = 2*pos+1;
    if (data[child] < data[pos]) {
      swap (data[child], data[pos]);
      pos = child;
    } else break;
  }
}

int pop(vector<int>& data) {
  int ans = data[0];
  swap(data[0], data[data.size()-1]);
  data.pop_back();
  percolate_down(data, 0);
  return ans;
}

void push(vector<int>& data, int val) {
  int n = data.size();
  data.push_back(val);
  percolate_up(data, n);
}
