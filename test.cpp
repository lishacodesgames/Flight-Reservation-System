#include <iostream>
#include <fstream>
using namespace std;

int main() {
  cout<<"\033c";
  
  ofstream out("test.txt");
  out << "ABCD";
  out.close();

  string A;
  ifstream in("test.txt");
  getline(in, A, 'A');
  //doesn't get the char
  
  string B;
  getline(in, B);

  in.close();
  cout << A << " " << B;

  cout<<'\n';
  return 0;
}