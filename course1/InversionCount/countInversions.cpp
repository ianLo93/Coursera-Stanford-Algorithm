#include <iostream>
#include <string>
#include <math.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <climits>
#include <fstream>
#include <typeinfo>

using namespace std;

void merge_sort(vector<int>& nums, int start, int end, long long int& record) {
  if (start >= end) return;
  int mid = (start+end)/2;
  // cout << mid << endl;
  merge_sort(nums, start, mid, record);
  merge_sort(nums, mid+1, end, record);
  int n = end-start;
  int temp[n+1];
  int i = start;
  int j = mid+1;
  for (int k=0; k<=n; k++) {
    if (i>mid) {
      temp[k] = nums[j];
      j++;
      continue;
    }
    if (j>end) {
      temp[k] = nums[i];
      i++;
      continue;
    }
    if (nums[i]<=nums[j]) {
      temp[k] = nums[i];
      i++;
    }
    else {
      temp[k] = nums[j];
      j++;
      record += mid+1-i;
    }
  }
  for (int k=start; k<=end; k++) {
    nums[k] = temp[k-start];
  }
}

long long int merge_sort(vector<int>& nums) {
  long long int record=0;
  merge_sort(nums, 0, nums.size()-1, record);
  return record;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "command failed.." << endl;
    return 1;
  }
  vector<int> a;
  ifstream input(argv[1]);
  if (!input) {
    cerr << "open() failed.." << endl;
    return 1;
  }
  int num;
  while (input >> num)
    a.push_back(num);

  long long int k = merge_sort(a);
  cout << k << endl;
  return 0;

}
