/* WELCOME TO AIR ROUTE SYSTEM */
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

#pragma region FUNCTIONS

int getIndex(string& element, vector<string>& vec) {
   for(int i = 0; i < vec.size(); i++){
      if(element == vec[i]) return i;
   }
   return -1;
}

void printTitle() {
   #if defined(_WIN32)
      system("cls");
   #elif defined(__APPLE__)
      cout << "\033c";
   #endif

   cout << "===============================\n";
   cout << "  WELCOME TO LISHA'S AIRPORT!  \n";
   cout << "===============================\n\n";
}

#pragma endregion

class Airport {
protected:
   vector<string> flights = {};
   vector<string> cities = {};
public:
   Airport() {
      flights = getFlights();
      cities = getCities();
   }

   vector<string> getFlights() {
      string id;
      vector<string> flights;

      ifstream txtFlights("flights.txt");
      while(getline(txtFlights, id)) {
         flights.push_back(id);
      }
      txtFlights.close();

      return flights;
   }

   vector<string> getCities() {
      string city;
      vector<string> cities;

      ifstream txtCities("cities.txt");
      while(getline(txtCities, city)) {
         cities.push_back(city);
      }
      txtCities.close();

      return cities;
   }
};

class Flight : public Airport {
protected:
   const int MIN_SEATS = 50;
   const int MAX_SEATS = 500;

   string ID;
   string origin, destination;
   int emptySeats, totalSeats;
   string departureTime;
   char gate;
   short terminal;
public:
   void generateRandomFlight() {
      #pragma region generateValues
      // ID
      ID = (char)(65 + rand()%26) + to_string(rand() % 900 + 100);

      // cities
      origin = cities[rand() % cities.size()];
      do {
         destination = cities[rand() % cities.size()];
      }while(origin == destination);

      // seats
      totalSeats = 10 * ((rand() % (MAX_SEATS/10 - MIN_SEATS/10)) + MIN_SEATS/10); // ∈ [MIN_SEATS, MAX_SEATS] as a multiple of 10
      emptySeats = rand() % totalSeats;

      // departure time
      string minuteIncrements[4] = {"00", "15", "30", "45"};
      string hour = to_string(rand() % 24);
      if(hour.size() == 1)
         hour = "0" + hour;

      departureTime = hour + ":" + minuteIncrements[rand() % 4];

      //gate & terminal
      gate = (char)(65 + rand() % 26);
      terminal = rand() % 5 + 1;
      #pragma endregion

      #pragma region fileManagement
      flights.push_back(ID);
      ofstream txtFlights("flights.txt", ios::app);
      txtFlights << ID << "\n";
      txtFlights.close();

      txtFlights.open("flightsInfo.txt", ios::app);
      txtFlights << ID << "|" << origin << "," << destination << "|" << emptySeats << "/" << totalSeats << "|" << departureTime << "|" << gate << "|" << terminal << "\n";
      txtFlights.close();
      #pragma endregion
   }

   void getFlightInfo(string id, bool toBePrinted) {
      #pragma region confirmID
      int index = getIndex(id, flights);
      if(index == -1) {
         printTitle();
         cout << "Flight " << id << " does not exist.\n";
         return;
      }
      #pragma endregion

      string tempString;

      #pragma region readValues
      ifstream flightsInfo("flightsInfo.txt");

      for(int i = 0; i < index; i++) {
         getline(flightsInfo, tempString);
      }

      getline(flightsInfo, ID, '|');
      getline(flightsInfo, origin, ',');
      getline(flightsInfo, destination, '|');
      getline(flightsInfo, tempString, '/');
      emptySeats = stoi(tempString);
      getline(flightsInfo, tempString, '|');
      totalSeats = stoi(tempString);
      getline(flightsInfo, departureTime, '|');
      getline(flightsInfo, tempString, '|');
      gate = tempString[0];
      getline(flightsInfo, tempString, '|');
      terminal = stoi(tempString);
      flightsInfo.close();
      #pragma endregion

      if(toBePrinted)
         printFlightInfo();
   }
   
   void printFlightInfo() {
      cout << "Flight " << ID << "\n";
      cout << origin << " -> " << destination << "\n";
      cout << "Seats available: " << emptySeats << "/" << totalSeats << "\n";
      cout << "Departing at " << departureTime << "\n";
      cout << "Gate " << gate << "\t Terminal " << terminal;
   }

   void displayAllFlights() {
      for(string flightID : flights) {
         getFlightInfo(flightID, true);
         cout << "\n\n";
      }
   }
};

int main() {
   srand(time(0));
   Flight flight;
   system("cls");
   
   flight.displayAllFlights();
   
   cout << "\n\n";
   return 0;
}