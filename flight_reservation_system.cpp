#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

#pragma region functions

void printTitle() {
#if defined(_WIN32)
  system("cls");
#elif defined(__APPLE__)
  cout << "\033c";
#endif
  cout << "*************** LISHA'S AMAZING AIRPORT ***************\n";
}

#pragma endregion

#pragma region Classes

vector<string> Cities = {"Mumbai", "Delhi", "New York", "Dallas", "DC", "Paris",  "Tokyo", "London",   "Rome",   "Sikkim"};
struct Airport {
  vector<string> flightList;
  Airport() {
    getFlights();
  }
  void getFlights() {
    ifstream flights("flights.txt");
  }
};

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

  /// @brief Generates random value for each member & adds it in flights.txt
  void generateRandomFlight() {
    // id
    char idLetter = rand() % 26 + 65;
    int idNumber = rand() % 1000;

    ID = idLetter + to_string(idNumber);

    // cities
    City1 = Cities[rand() % Cities.size()];
    do {
      City2 = Cities[rand() % Cities.size()];
    } while (City1 == City2);

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
    terminal = rand() % 9 + 1;  // no 0

    // file output
    ofstream flights("flights.txt", ios::app);

    flights << ID << '|' << City1 << ',' << City2 << '|' << emptySeats << '/'
            << totalSeats << '|';
    flights << setw(2) << setfill('0') << hour << minutes;
    flights << '|' << gate << '|' << terminal << '\n';

    flights.close();
  }
  
  void printFlightInfo(string ID) {
    ifstream flights("flights.txt");

    getline(flights, this->ID);
    if (this->ID == ID) {
      cout << "Flight " << this->ID << '\n';
      cout << City1 << " -> " << City2 << '\n';
      cout << "Seats Available: " << emptySeats << '/' << totalSeats << '\n';
      cout << "Departing at: " << depTime << '\n';
    }

    flights.close();
  }
};

#pragma endregion

//* MAIN FUNCTION
int main() {
  srand(time(0));
  printTitle();

  Flight flight;
  Airport lisha;

  flight.printFlightInfo("A123");

  for(string flight : lisha.flightList) {
    cout << flight << " ";
  }

  cout << '\n';
  return 0;
}