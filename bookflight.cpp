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
  int choice;
  cout << "******************* LISHA'S AMAZING AIRPORT *******************\n";
  while(true) {
    cout << "\n0. Exit";
    cout << "\n1. Book a flight";
    cout << "\n2. Show flight details";
    cout << "\nWhat would you like to do? ";
    cin >> choice;

    switch(choice) {
      case 0: exit(0); 

      case 1: break;
      
      case 2: break;

      default: cout << "Invalid choice.\n"; break;
    }
  }
  
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