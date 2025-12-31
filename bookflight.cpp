#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

struct Flight {
  string ID, City1, City2;
  int takenSeats, totalSeats;
};

class Airport {
  vector<string> FlightIDs = {};
  vector<string> Cities = {"Mumbai", "Delhi", "New York", "Rome", "Paris"};
  
public:

  Airport() { // 3 flights at the start
    generateFlight(); 
    generateFlight(); 
    generateFlight(); 
  }
  void generateFlight();
};

int main() {
  srand(time(0));
  cout<<"\033c";
  
  Airport flight;
  
  cout<<'\n';
  return 0;
}

// functions 
bool flightExists(vector<string> FlightIDs, string id) {
  for (string ID : FlightIDs) {
    if(id == ID) return true;
  }

  return false;
}

void Airport::generateFlight() {
  Flight flight;
  do {
    char letter = rand() % 26 + 65; //uppercase letter
    int number = rand() % 1000;

    flight.ID = letter + to_string(number);
  } while(flightExists(FlightIDs, flight.ID));

  flight.City1 = Cities[rand() % Cities.size()];
  do {
    flight.City2 = Cities[rand() % Cities.size()];
  } while(flight.City1 == flight.City2);

  flight.totalSeats = rand() % 15 + 1;
  flight.takenSeats = rand() % flight.totalSeats;

  ofstream flights("flights.txt", ios::app);

  flights << flight.ID << "||" << flight.City1 << "->" << flight.City2 << "||" << flight.takenSeats << "/" << flight.totalSeats<<endl;

  flights.close();
}