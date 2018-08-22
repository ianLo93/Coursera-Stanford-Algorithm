#include <iostream>
#include <string>
#include <math.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <climits>
#include <typeinfo>

using namespace std;

string add(string& a, string& b) {
  string ans;
  int k = 0;
  int i=a.size()-1, j=b.size()-1;
  for(; i>=0 || j>=0; i--, j--) {
    int c = 0, n = 0;
    if (i>=0) c = a[i]-'0';
    if (j>=0) n = b[j]-'0';
    int m = c + n + k;
    if (m >= 10) {
      m -= 10;
      k=1;
    }
    else k=0;
    ans.insert( ans.begin(), 1, char(m+'0') );
  }
  if (k==1) ans.insert( ans.begin(), 1, '1' );
  return ans;
}

string multiplication(string& a, string& b) {
  int n = a.size();
  if (n==1) return to_string( atoi(a.c_str()) * atoi(b.c_str()) );
  string a1 = a.substr(0, n/2);
  string a2 = a.substr(n/2, n/2);
  string b1 = b.substr(0, n/2);
  string b2 = b.substr(n/2, n/2);
  string item1 = multiplication(a1, b1) + string(n, '0');
  string item2 = multiplication(a2, b2);
  string item31 = multiplication(a1, b2);
  string item32 = multiplication(a2, b1);
  string item3 = add(item31, item32)+string(n/2, '0');
  string item4 = add(item1, item3);
  return add( item4, item2 );
}

int main() {
  string a = "3141592653589793238462643383279502884197169399375105820974944592";
  string b = "2718281828459045235360287471352662497757247093699959574966967627";
  cout << multiplication(a, b) << endl;
}
