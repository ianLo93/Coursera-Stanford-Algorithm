#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void quick_sort (vector<int>& a, int start, int end, int& num) {
  if (start >= end) return;
  num += end-start;
  int mid = (end+start)/2;
  map<int, int> comparison;
  comparison[a[start]] = start;
  comparison[a[mid]] = mid;
  comparison[a[end]] = end;
  map<int, int>::iterator it = comparison.begin();
  // for (; it!=comparison.end(); it++)
  //   cout << "a[i]: " << it->first << " i: " << it->second << endl;
  it++;
  swap(a[it->second], a[start]);
  int pivot = a[start];
  int i = start+1, j = start+1;
  for (; j<=end; j++) {
    if (a[j] < pivot) {
      swap(a[i], a[j]);
      i++;
    }
  }
  swap(a[start], a[i-1]);
  quick_sort (a, start, i-2, num);
  quick_sort (a, i, end, num);
}

int count_quick_sort (vector<int>& a) {
  int num = 0;
  quick_sort (a, 0, a.size()-1, num);
  return num;
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

  vector<int> a;
  int num;
  while (input >> num) a.push_back(num);
  num = count_quick_sort(a);
  cout << num << endl;
  // for (int i=0; i<a.size(); i++) cout << a[i] << " ";
  // cout << endl;

  return 0;
}
