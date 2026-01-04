#include <iostream>
#include <fstream>
using namespace std;

int main() {
  cout<<"\033c";
  srand(time(0));
  string firstName, lastName, bookedFlight, seatNumber;
  string fullName = "Lisha Patil";

  size_t space = fullName.find(' ');

  firstName = fullName.substr(0, space);
  lastName = fullName.substr(space+1, string::npos);

  cout << fullName << '\n';
  cout << firstName << " " << lastName << '\n';

  cout<<'\n';
  return 0;
}