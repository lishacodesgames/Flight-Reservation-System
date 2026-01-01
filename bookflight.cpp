#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;
void printTitle() { // to avoid having to manually replace \033c when i'm on windows
  cout << "\033c";
  cout << "******************* LISHA'S AMAZING AIRPORT *******************\n";  
}


class Flights {
  string ID, City1, City2;
  int takenSeats, totalSeats;

  vector<string> FlightIDs = {};
  vector<string> Cities = {"Mumbai", "Delhi", "New York", "Rome", "Paris"};
  
public:

  Flights() { // 3 flights at the start
    generateFlight(); 
    generateFlight(); 
    generateFlight(); 
  }
  void generateFlight();
};


int main() {
  srand(time(0));
  printTitle();
  
  Flights flight;
  int choice;

  while(true) {
    cout << "\n0. Exit";
    cout << "\n1. Book a flight";
    cout << "\n2. Show flight details";
    cout << "\nWhat would you like to do? ";
    cin >> choice;

    switch(choice) {
      case 0: exit(0); 

      case 1: 

        break;
      
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

void Flights::generateFlight() {
  Flights flight;
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