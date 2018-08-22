#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class Symbol {
public:
  Symbol(int num, int f) {
    left = right = NULL;
    freq = f;
    data = num;
  }
  int data;
  int freq;
  Symbol *left;
  Symbol *right;
};

class Compare {
public:
  bool operator() (Symbol* s1, Symbol* s2){
    return s1->freq > s2->freq;
  }
};

int findMax (Symbol* root);
int findMin (Symbol* root);

int main (int argc, char* argv[])
{
  if (argc != 2) {
    cerr << "Command error.." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  if (!input) {
    cerr << "open() failed" << endl;
    return 1;
  }

  priority_queue<Symbol*, vector<Symbol*>, Compare> freqs;
  int val, num = 0;
  input >> val;
  while (input >> val) {
    freqs.push( new Symbol(num, val) );
    num++;
  }

  Symbol *left, *right, *top;
  while (freqs.size() != 1) {
    left = freqs.top();
    freqs.pop();

    right = freqs.top();
    freqs.pop();

    top = new Symbol(num, left->freq + right->freq);
    num++;
    top->left = left;
    top->right = right;

    freqs.push(top);
  }

  cout << findMax(top) - 1 << endl;
  cout << findMin(top) << endl;

  return 0;
}

int findMax (Symbol* root) {
  if (!root) return 0;
  int left = findMax (root->left);
  int right = findMax (root->right);
  if (left > right) return left+1;
  else return right+1;
}

int findMin (Symbol* root) {
  vector<Symbol*> first;
  int k = 0;
  first.push_back(root);
  while (1) {
    vector<Symbol*> second;
    for (int i=0; i<first.size(); i++) {
      if (!first[i]->left) return k;
      second.push_back(first[i]->left);
      second.push_back(first[i]->right);
    }
    first = second;
    k++;
  }
  return 0;
}
