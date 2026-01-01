#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

# pragma region functions

void printTitle() { // to avoid having to manually replace \033c when i'm on windows
  cout << "\033c";
  cout << "******************* LISHA'S AMAZING AIRPORT *******************\n";  
}
bool flightExists(vector<string> FlightIDs, string id) {
  for (string ID : FlightIDs) {
    if(id == ID) return true;
  }

  return false;
}
bool validCity(vector<string> Cities, string city) {
  for(string CITY : Cities) {
    if(city == CITY) return true;
  }
  return false;
}

#pragma endregion

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
  void book(string how);
  void parseFlight();
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

      case 1: {
        printTitle();
        bool validChoice = true;
        
        while(validChoice) {
          int choice;
          cout << "\n0. Go back";
          cout << "\n1. Choose from City Route";
          cout << "\n2. Choose from Flight Number";
          cout << "\nHow would you like to book? ";
          cin >> choice;
          
          switch(choice) {
            case 0: validChoice = false; printTitle(); break;
            
            case 1: flight.book("City"); break;
            
            case 2: break;
            
            default: cout << "\nInvalid choice"; break;
          }
        }
        break;
      }
      
      case 2: break;

      default: printTitle(); cout << "\nInvalid choice.\n"; break;
    }
  }
  
  cout<<'\n';
  return 0;
}

// functions 
void Flights::generateFlight() {
  do {
    char letter = rand() % 26 + 65; //uppercase letter
    int number = rand() % 1000;

    ID = letter + to_string(number);
  } while(flightExists(FlightIDs, ID));

  City1 = Cities[rand() % Cities.size()];
  do {
    City2 = Cities[rand() % Cities.size()];
  } while(City1 == City2);

  totalSeats = rand() % 15 + 1;
  takenSeats = rand() % totalSeats;

  ofstream flights("flights.txt", ios::app);

  flights << ID << "||" << City1 << "->" << City2 << "||" << takenSeats << "/" << totalSeats<<endl;

  flights.close();
}

void Flights::book(string how) {
  if(how == "City") {
    printTitle();
    while(true) {
      cout << "Which city are you departing from? ";
      cin >> City1;

      if(validCity(Cities, City1)) break;
      else {printTitle(); cout << "Invalid City.\n";}
    }

    printTitle();
    cout << "City of Departure: " << City1;

    ifstream flights("flights.txt");
    cin.ignore();
    
    while(getline(flights, ID, '|')) {
      flights.seekg(1, ios::cur); // moves cursor ahead by 1 char
      
      string tempCity1;
      string tempSeats;

      getline(flights, tempCity1, '-'); flights.seekg(1, ios::cur);

      getline(flights, City2, '|'); flights.seekg(1, ios::cur);

      getline(flights, tempSeats, '/');
      takenSeats = stoi(tempSeats);
      getline(flights, tempSeats);
      totalSeats = stoi(tempSeats);

      if(tempCity1 == City1) {
        cout << "\n\nFlight " << ID << "\n";
        cout << City1 << " -> " << City2 << "\n";
        cout << "Seats available: " << totalSeats-takenSeats << "/" << totalSeats;
      }
    }

    flights.close();
  }

  else {
    ifstream flights("flights.txt");

    

    flights.close();
  }
}

void Flights::parseFlight() {
  
}