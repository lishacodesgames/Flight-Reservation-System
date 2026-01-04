#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;
vector<string> Cities = {"Mumbai", "Delhi", "New York", "Dallas", "DC", "Paris",  "Tokyo", "London",   "Rome",   "Sikkim"};

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

struct Airport {
  vector<string> flightList;

  Airport() { getFlights(); }

  void getFlights() {
    string parsedID;
    string unwanted;
    ifstream flights("flights.txt");
    
    while (getline(flights, parsedID, '|')) {
      flightList.push_back(parsedID);
      getline(flights, unwanted);
    }

    flights.close();
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
    int idNumber = rand() % 900 + 100; // 100 -> 999

    ID = idLetter + to_string(idNumber);

    // cities
    City1 = Cities[rand() % Cities.size()];
    do { City2 = Cities[rand() % Cities.size()]; } while (City1 == City2);

    // seats
    totalSeats = rand() % 20 + 1;
    emptySeats = rand() % (totalSeats + 1);

    // time
    int hour = rand() % 24;
    int minutes = rand() % 60;

    ofstream outTime("temp_time.txt");
    outTime << setfill('0') << setw(2) << hour;
    outTime << setfill('0') << setw(2) << minutes;
    outTime.close();

    ifstream inTime("temp_time.txt");
    getline(inTime, depTime);
    inTime.close();

    // gate & terminal
    gate = rand() % 26 + 65;
    terminal = rand() % 9 + 1;  // no 0

    // file output
    ofstream flights("flights.txt", ios::app);

    flights << ID << '|' << City1 << ',' << City2 << '|' << emptySeats << '/' << totalSeats << '|' << depTime << '|' << gate << '|' << terminal << '\n';

    flights.close();
  }
  
  void printFlightInfo(string ID) {
    ifstream flights("flights.txt");
    string unwanted;

    while(getline(flights, this->ID, '|')) {
      if(this->ID != ID) getline(flights, unwanted);
      else {
        #pragma region parsing
        string tempStr;
        getline(flights, City1, ',');
        getline(flights, City2, '|');
        getline(flights, tempStr, '/'); emptySeats = stoi(tempStr);
        getline(flights, tempStr, '|'); totalSeats = stoi(tempStr);
        getline(flights, depTime, '|');
        getline(flights, tempStr, '|'); gate = tempStr[0];
        getline(flights, tempStr); terminal = stoi(tempStr);
        #pragma endregion

        cout << "Flight " << this->ID << '\n';
        cout << City1 << " -> " << City2 << '\n';
        cout << "Seats Available: " << emptySeats << '/' << totalSeats << '\n';
        cout << "Departing at: " << depTime << '\n';
      }
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

  flight.printFlightInfo("V311");

  cout << '\n';
  for(string flight : lisha.flightList) {
    cout << flight << " ";
  }

  cout << '\n';
  return 0;
}