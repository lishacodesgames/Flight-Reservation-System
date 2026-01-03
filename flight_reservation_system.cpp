#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

#pragma region functions

void printTitle() {
  #if defined(_WIN32) 
    system("cls");
  #elif defined(__APPLE__)
    cout << "\033c";
  #endif
  cout << "******************* LISHA'S AMAZING AIRPORT *******************\n";  
}

#pragma endregion

#pragma region Classes

struct Airport {
  vector<string> flightList;
  vector<string> Cities = {"Mumbai", "Delhi", "New York", "Dallas", "DC", "Paris", "Tokyo", "London", "Rome", "Sikkim"};
}lisha;

class Flight {
  string ID, City1, City2;
  int emptySeats, totalSeats;
  string depTime;
  char gate;
  short terminal;

public:
  Flight() {
    generateRandomFlight(); 
    generateRandomFlight(); 
    generateRandomFlight(); 
  }
  // todo TEST IN TEST BRANCH WITH TERMINAL OUTPUT
  void generateRandomFlight() {
    // id
  char idLetter = rand() % 26 + 65;
  int idNumber = rand() % 1000;

  ID = idLetter + to_string(idNumber);
  lisha.flightList.push_back(ID);

  // cities
  City1 = lisha.Cities[rand() % lisha.Cities.size()];
  do {
    City2 = lisha.Cities[rand() % lisha.Cities.size()];
  }while(City1 == City2);

  // seats
  totalSeats = rand() % 20 + 1;
  emptySeats = rand() % (totalSeats + 1);

  // time
  int hour = rand() % 24;
  int minutes = rand() % 60;
  
  ofstream outTime("temp_time.txt");
  outTime << setw(2) << setfill('0') << hour << minutes;
  outTime.close();

  ifstream inTime("temp_time.txt");
  getline(inTime, depTime);
  inTime.close();

  // gate & terminal
  gate = rand() % 26 + 65;
  terminal = rand() % 9 + 1; // no 0

  ofstream flights("flights.txt", ios::app);

  flights << ID << ',' << City1 << ',' << City2 << ',' << emptySeats << '/' << totalSeats << ',';
  flights << setw(2) << setfill('0') << hour << minutes;
  flights << ',' << gate << ',' << terminal << '\n';

  flights.close();
  }
};

#pragma endregion

//* MAIN FUNCTION
int main() {
  srand(time(0));
  printTitle();  
  
  Flight flight;
  
  cout<<'\n';
  return 0;
}