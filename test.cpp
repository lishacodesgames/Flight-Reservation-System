#include <iostream>
#include <fstream>
using namespace std;


int main() {
  cout<<"\033c";
  srand(time(0));

  vector<string> flightList;
  vector<string> Cities = {"Mumbai", "Delhi"};
  
  string ID, City1, City2;
  int totalSeats, emptySeats, depTime;
  char gate;
  short terminal;

  // id
  char idLetter = rand() % 26 + 65;
  int idNumber = rand() % 1000;

  ID = idLetter + to_string(idNumber);
  flightList.push_back(ID);

  // cities
  City1 = Cities[rand() % Cities.size()];
  do {
    City2 = Cities[rand() % Cities.size()];
  }while(City1 == City2);

  // seats
  totalSeats = rand() % 20 + 1;
  emptySeats = rand() % (totalSeats + 1);

  // time
  int hour = rand() % 24; //! MAKE IT SHOW 0 PREFIX FOR SINGLE DIGIT HOURS
  int minutes = rand() % 60; //! SAME: 0 PREFIX
  depTime = stoi(to_string(hour) + to_string(minutes));

  // gate & terminal
  gate = rand() % 26 + 65;
  terminal = rand() % 9 + 1; // no 0

  ofstream flights("flights.txt", ios::app);

  flights << ID << ',' << City1 << ',' << City2 << ',' << emptySeats << '/' << totalSeats << ',';
  flights << setw(2) << setfill('0') << hour << minutes;
  flights << ',' << gate << ',' << terminal << '\n';

  flights.close();
  cout<<'\n';
  return 0;
}