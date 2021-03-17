#include<iostream> 
#include<cmath> 
using namespace std;
  
int fib(int n) { 
  double phi = (1 + sqrt(5)) / 2; 
  return round(pow(phi, n) / sqrt(5)); 
} 
  
// Driver Code 
int main () 
{ 
  int n = 9; 
  cout << fib(n) << endl; 
  return 0; 
} 
