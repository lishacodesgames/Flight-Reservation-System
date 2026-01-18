#include <ctime>
#include <fstream>
#include <iomanip>  //for std::setfill() & setw()
#include <iostream>
#include <vector>
using namespace std;

#pragma region Globals

vector<string> Cities = {"Mumbai", "Delhi", "New York", "Dallas", "DC",
                         "Paris",  "Tokyo", "London",   "Rome",   "Sikkim"};

#pragma endregion

#pragma region functions

void clrscr() {
#if defined(_WIN32)
  system("cls");
#elif defined(__APPLE__)
  cout << "\033c";
#endif
  cout << "*************** LISHA'S AMAZING AIRPORT ***************\n\n";
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
 protected:
  string ID, City1, City2;
  int emptySeats, totalSeats;  // emptySeats ≤ totalSeats ∈ [1,20]
  string depTime;
  char gate;       // ∈ [A, Z]
  short terminal;  // ∈ [1, 9]

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
    int idNumber = rand() % 900 + 100;  // ∈ [100,999]
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
    outTime << setfill('0') << setw(2) << hour;
    outTime << setfill('0') << setw(2) << minutes;
    outTime.close();

    ifstream inTime("temp_time.txt");
    getline(inTime, depTime);
    inTime.close();

    // gate & terminal
    gate = rand() % 26 + 65;
    terminal = rand() % 9 + 1;

    // file output
    ofstream flights("flights.txt", ios::app);

    flights << ID << '|' << City1 << ',' << City2 << '|' << emptySeats << '/'
            << totalSeats << '|' << depTime << '|' << gate << '|' << terminal
            << '\n';

    flights.close();
  }

  void printFlightInfo(string ID) {
    string unwanted;
    ifstream flights("flights.txt");

    while (getline(flights, this->ID, '|')) {
      if (this->ID != ID)
        getline(flights, unwanted);
      else {
#pragma region parsing
        string tempStr;
        getline(flights, City1, ',');
        getline(flights, City2, '|');
        getline(flights, tempStr, '/');
        emptySeats = stoi(tempStr);
        getline(flights, tempStr, '|');
        totalSeats = stoi(tempStr);
        getline(flights, depTime, '|');
        getline(flights, tempStr, '|');
        gate = tempStr[0];
        getline(flights, tempStr);
        terminal = stoi(tempStr);
#pragma endregion

        cout << "Flight " << this->ID << '\n';
        cout << City1 << " -> " << City2 << '\n';
        cout << "Seats Available: " << emptySeats << '/' << totalSeats << '\n';
        cout << "Departing at: " << depTime << '\n';
        break;
      }
    }

    flights.close();
  }

  // TODO add logic
  void book(string how) {
    vector<string> validFlights;

    if(how == "City") {
      while(true) {
        string userOrigin;
        cout << "What is your origin city? ";
        cin >> userOrigin; cin.ignore();

        string tempStr;
        ifstream flights("flights.txt");

        while(getline(flights, tempStr, '|')) {
          ID = tempStr;
          getline(flights, City1, ',');

          if(userOrigin != City1) {
            getline(flights, tempStr);
            continue;
          }

          clrscr();
          validFlights.push_back(ID);
          printFlightInfo(ID); cout << '\n';
        }

        if(validFlights.size() == 0) {
          cout << "Sorry! There is no flight from this city.\n";
          flights.close(); // close before breaking
          break;
        }

        if(flights.eof()) {
          flights.close();
          break;
        }

      }
    }
    else if(how == "ID") {

    }
    else {

    }
  }
};

class User : private Flight {
  string firstName, lastName, bookedFlight, seatNumber;

 public:
  void displayBoardingPass(string fullName) {
    bool userFound = false;
    string tempStr;

    // name
    size_t space = fullName.find(' ');  // position of space in string
    firstName = fullName.substr(0, space);
    lastName = fullName.substr(space + 1, string::npos);

    // parse User
    ifstream passengers("passengers.txt");

    while (getline(passengers, tempStr, ',')) {
      if (tempStr != firstName) {
        getline(passengers, tempStr);
        continue;
      }

      getline(passengers, tempStr, ',');

      if (tempStr != lastName) {
        getline(passengers, tempStr);
        continue;
      }

      userFound = true;
      getline(passengers, bookedFlight, ',');
      getline(passengers, seatNumber);
      break;
    }

    passengers.close();

    if (!userFound) {
      clrscr();
      cout << "Sorry, " << fullName << " is not a passenger on our flight.\n";
    }

    // parse Flight
    ifstream flights("flights.txt");

    while (getline(flights, ID, '|')) {
      if (ID != bookedFlight)
        getline(flights, tempStr);
      else {
        #pragma region parsing
          getline(flights, City1, ',');
          getline(flights, City2, '|');
          getline(flights, tempStr, '/'); emptySeats = stoi(tempStr);
          getline(flights, tempStr, '|'); totalSeats = stoi(tempStr);
          getline(flights, depTime, '|');
          getline(flights, tempStr, '|'); gate = tempStr[0];
          getline(flights, tempStr); terminal = stoi(tempStr);
        #pragma endregion

        clrscr();
        cout << "NAME OF PASSENGER: " << fullName << '\t' << "SEAT NO. " << seatNumber << '\n';
        cout << "TO: " << City2 << '\t' << "FROM: " << City1 << '\n';
        cout << "TIME: " << depTime.substr(0, 2) << ':' << depTime.substr(2, string::npos);
        cout << "\n\n";
        cout << "FLIGHT: " << bookedFlight << "\n";
        cout << "GATE " << gate << "\t" << "TERMINAL " << terminal << '\n';
      }
    }

    flights.close();
  }
};

#pragma endregion

//* MAIN FUNCTION
int main() {
  srand(time(0));
  clrscr();
  
  Flight flight;
  Airport lisha;
  User user;
  
  while(true) {
    int choice;
    cout << "0. Exit Program\n";
    cout << "1. Book Flight\n";
    cout << "2. Display Flight Info\n";
    cout << "What would you like to do? ";
    cin >> choice;

    clrscr();

    switch(choice) {
      case 0: 
        cout << "Thank you for booking with us!\n";
        exit(0);

      // FIXME loop not working
      case 1: 
        book:
        cout << "0. Go back\n";
        cout << "1. Book from City Route\n";
        cout << "2. Book from Flight ID\n";
        cout << "What would you like to do? ";
        cin >> choice;

        clrscr();

        switch(choice) {
          case 0:
            break;

          // TODO add logic
          case 1:
            flight.book("City");
            break;

          // TODO add logic
          case 2:
            flight.book("ID");
            break;

          default:
            cout << "Invalid choice. Please choose again.\n\n";
            goto book;
        }

        break;
      
      // TODO add display logic
      case 2:
        cout << "2";
        break;
      
      default:
        cout << "Invalid choice. Please choose again.\n\n";
        break;
    }
  }

  cout << '\n';
  return 0;
}