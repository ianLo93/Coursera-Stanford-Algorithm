#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <unordered_set>

using namespace std;

const int LOW = -10000;
const int HIGH = 10000;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Command error.." << endl;
    return 1;
  }

  fstream input(argv[1]);
  if (!input) {
    cerr << "open() failed.." << endl;
    return 1;
  }

  set<long> data;
  long num;
  while (input >> num)
    data.insert(num);

  // cout << data.size() << endl;
  set<long>::iterator i=data.begin(), j=data.end();
  j--;
  // int count = 0;
  unordered_set<long> ts;
  while (i != j) {
    if ( *i + *j > HIGH ) j--;
    else if ( *i + *j < LOW) i++;
    else {
      for (set<long>::iterator k=j; *k + *i>=LOW && k != i; k--) {
        if (*k+*i > HIGH) {
          j--;
          continue;
        }
        cout << *k+*i << endl;
        ts.insert(*k+*i);
      }
      i++;
    }
  }
  cout << ts.size() << endl;

  return 0;
}
