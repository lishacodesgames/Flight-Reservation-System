/* WELCOME TO AIR ROUTE SYSTEM */
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

// TODO separate all fstream work into their own functions
// TODO in generating flights & passengers, check if starting from \n and never leaving extra \n behind
/** @help
 * where does FlightStorage::getFlight() get index from? 
 */

#pragma region FUNCTIONS

int getIndex(string& element, vector<string>& vec) { // done
   for(int i = 0; i < vec.size(); i++){
      if(element == vec[i]) 
         return i;
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

class Airport { //done
protected:
   vector<string> flights = {};
   vector<string> cities = {};
public:
   Airport() {
      flights = getFlights();
      cities = getCities();
   }

   vector<string> getFlights() { //done
      string id;
      vector<string> flights;

      ifstream txtFlights("text-files/flights.txt");
      while(getline(txtFlights, id)) {
         flights.push_back(id);
      }
      txtFlights.close();

      return flights;
   }

   vector<string> getCities() { //done
      string city;
      vector<string> cities;

      ifstream txtCities("text-files/cities.txt");
      while(getline(txtCities, city)) {
         cities.push_back(city);
      }
      txtCities.close();

      return cities;
   }
};

class Flight : public Airport {
   protected: //done
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
      ID = (char)(65 + rand() % 26) + to_string(rand() % 900 + 100);

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

      #pragma region fileManagement //done
      flights.push_back(ID);
      ofstream txtFlights("text-files/flights.txt", ios::app);
      txtFlights << "\n" << ID;
      txtFlights.close();

      txtFlights.open("text-files/flightsInfo.txt", ios::app);
      txtFlights << "\n" << ID << "|" 
      << origin << "," << destination << "|" 
      << emptySeats << "/" << totalSeats << "|" 
      << departureTime << "|" << gate << "|" << terminal;
      txtFlights.close();
      #pragma endregion
   }

   /** @brief
    * gets index of flight by ID
    * goes to that line in flightsInfo.txt
    * reads all values
    * prints them in a nice format (if needed)
    */
   //TODO add a way to filter flight with origin/destination/time
   bool getFlightInfo(string id, bool toBePrinted) { //done
      #pragma region confirmID
      int index = getIndex(id, flights);
      if(index == -1) {
         printTitle();
         cout << "Flight " << id << " does not exist.\n";
         return false;
      }
      #pragma endregion

      string tempString;

      #pragma region readValues
      ifstream flightsInfo("text-files/flightsInfo.txt");

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
      getline(flightsInfo, tempString);
      terminal = stoi(tempString);

      flightsInfo.close();
      #pragma endregion

      if(toBePrinted)
         printFlightInfo();

      return true;
   }
   
   /// @brief prints just-parsed flight info in a nice format
   void printFlightInfo() {
      cout << "Flight " << ID << "\n";
      cout << origin << " -> " << destination << "\n";
      cout << "Seats available: " << emptySeats << "/" << totalSeats << "\n";
      cout << "Departing at " << departureTime << "\n";
      cout << "Gate " << gate << "\t Terminal " << terminal << "\n\n";
   }

   //TODO add ways to filter flights by origin/destination/time
   void displayAllFlights() {
      for(string flightID : flights) {
         getFlightInfo(flightID, true);
      }
   }
};

class Passenger {
protected:
   string name;
   int age; // ∈ [1, 99]
   string bookedFlight;
   string seat; // 2-digit number <= totalSeats/5 + CHAR(A-E)
};

class Viewer : public Flight, public Passenger {
public:
   bool displayBoardingPass() {
      string tempString, nameInput;
      printTitle();
      cout << "Enter name of passenger: ";
      cin >> nameInput;

      #pragma region getPassengerInfo
      bool passengerExists = false;
      ifstream passengers("text-files/passengers.txt");
      while(getline(passengers, this->name, ',')){
         if(name != nameInput) {
            getline(passengers, tempString);
            continue;
         }

         passengerExists = true;
         getline(passengers, tempString, ',');
         age = stoi(tempString);
         getline(passengers, bookedFlight, ',');
         getline(passengers, seat);
         break;
      }

      passengers.close();
      #pragma endregion

      if(!passengerExists) {
         printTitle();
         cout << nameInput << " does not have a boarding pass.\n";
         return false;
      }

      #pragma region printInfo
      getFlightInfo(bookedFlight, false);

      printTitle();
      cout << "NAME OF PASSENGER: " << name << "\t AGE: " << age << "\n";
      cout << "SEAT NO. " << seat << "\n";
      cout << "TO: " << destination << "\t FROM: " << origin << "\n";
      cout << "TIME: " << departureTime << "\n";
      cout << "FLIGHT: " << bookedFlight << "\n";
      cout << "GATE " << gate << "\t TERMINAL " << terminal << "\n";
      #pragma endregion
      
      return true;
   }
};

// TODO replace cin with getline() wherever getting cities. For Rio de Janeiro
// TODO add feedback when displayOptions() returns with ""
// TODO move not-needed functions to private/protected
// TODO EVERYWHERE add do-while for (y/n) validation
// TODO what to do if no flights?

class Booker : public Flight, public Passenger {
private:
   string getCity(string type) {
      string city;
      int index;
      char temp;

      while(true) {
         printTitle();
         cout << "Please enter your " << type << " city: ";
         cin >> city;

         index = getIndex(city, cities);

         if(index == -1) {
            printTitle();
            cout << city << " does not exist.\n";
            cout << "Would you like to try again? (y/n) ";
            cin >> temp;

            if(temp == 'n')
               return "";
         } else break;
      }
      return city;
   }
public:
   void bookFlight() {
      cout << "\nBooked Flight: " << displayOptions() << "\n";
   }

   string displayOptions() {
      int choice;
      string temp;

      printTitle();
      do {
         cout << "===============================\n";
         cout << "[0] Go back\n";
         cout << "[1] Choose a flight by ID\n";
         cout << "[2] Book from Origin city\n";
         cout << "===============================\n";
         cout << "Enter your choice: ";
         cin >> choice;

         if(choice < 0 || choice > 2) {
            printTitle();
            cout << "Invalid choice.\n";
         }
      }while(choice < 0 || choice > 2);

      if(choice == 0) {
         return "";
      } else if (choice == 1) {
         printTitle();  
         displayAllFlights();
         return getID(flights);
      } else if (choice == 2) {
         #pragma region origin
         string depCity = getCity("origin"); // departure city
         if(depCity == "")
            return "";
         
         // vector work
         vector<string> originFlights = {};
         int count = 0;
         for(string flightID : flights) {
            getFlightInfo(flightID, false);
            if(origin == depCity) {
               originFlights.push_back(flightID);
               count++;
            }
         }

         //print info
         printTitle();
         do {
            // TODO if only 1 flight exists, change the prompt to "Would you like to book <flight>?"
            cout << "There are " << count << " flights departing from " << depCity << ".\n";
            cout << "===============================\n";
            cout << "[0] Go back\n";
            cout << "[1] Choose a flight by ID\n";
            cout << "[2] Book from Destination city\n";
            cout << "===============================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if(choice < 0 || choice > 2) {
               printTitle();
               cout << "Invalid choice.\n";
            }
         } while(choice < 0 || choice > 2);

         if(choice == 0) {
            return displayOptions();
         } else if (choice == 1) {
            printTitle();
            for(string flightID : originFlights) {
               getFlightInfo(flightID, true);
            }
            return getID(originFlights);
         } 
         #pragma endregion
         #pragma region destination
         else if (choice == 2) {
            string arrCity = getCity("destination"); // arrival city
            if (arrCity == "")
               return "";
            
            // vector work
            vector<string> destinationFlights = {};
            count = 0;
            for(string flightID : originFlights) {
               getFlightInfo(flightID, false);
               if (destination == arrCity) {
                  destinationFlights.push_back(flightID);
                  count++;
               }
            }

            // print info
            printTitle();
            // TODO if only 1 flight exists, change the prompt to "Would you like to book <flight>?"
            cout << "There are " << count << " flights going from " << depCity << " -> " << arrCity << ".\n";
            cout << "===============================\n";
            for (string flightID : destinationFlights) {
               getFlightInfo(flightID, true);
            }
            return getID(destinationFlights);
            #pragma endregion
         }
      }

      return "";
   }  

   /** @brief
    * GET ID
    * if ID valid, return it
    *if ID not in validFlights, check if it's in flights
    * if ID not in both, display invalid message and somehow loop back without erasing display of all flights
    * if ID not in validFliths but in flights, display message + "would you like to book flight <ID> anyways? (y/n)" if yes, return ID, if no, loop back
    */
   string getID (vector<string>& validFlights) {
      cout << "\n===============================";
      cout << "\nEnter flight ID: ";
      cin >> ID;
      int validIndex = getIndex(ID, validFlights);
      if (validIndex != -1) // valid ID
         return ID;
      
      char temp;
      if (validFlights != flights) {
         int flightIndex = getIndex(ID, flights);
         if (flightIndex != -1) { // ID exists but doesn't match criteria
            cout << "\nFlight " << ID << " does not match the selected criteria.\n";
            cout << "Would you like to book flight " << ID << " anyways? (y/n) ";
            cin >> temp;
            if (temp == 'y')
               return ID;
            else
               return displayOptions();
         }
      }

      // flight doesn't exist
      cout << "Flight " << ID << " does not exist.\n";
      cout << "Would you like to try again? (y/n) "; 
      cin >> temp;
      if (temp == 'n')
         return displayOptions();
      
      cout << "\n";
      return getID(validFlights);
   }
};

#pragma region MAIN
int main() {
   srand(time(0));
   Viewer program;
   Booker manager;
   printTitle();
   
   int choice;
   while(true) {
      printTitle();
      cout << "===============================\n";
      cout << "[0] Exit\n";
      cout << "[1] Book a flight\n";
      cout << "[2] View flight information\n";
      cout << "[3] View boarding pass\n";
      cout << "[4] View all flights\n";
      cout << "===============================\n";
      cout << "Enter your choice: ";
      cin >> choice;

      string temp;
      bool success;
      switch(choice){
         case 0: return 0;

         case 1:
            printTitle();
            manager.bookFlight();
            cout << "\nBooking a flight..."; // TODO
            cin.get(); cin.get();
            break;

         case 2:
            while(true){
               printTitle();
               cout << "Enter flight ID: ";
               cin >> temp;
               cin.ignore();
               
               printTitle();
               success = program.getFlightInfo(temp, true);
               cin.get(); cin.get();
               if(success)
                  break;
               cout << "Try again? (y/n) ";
               cin >> temp; 
               if(temp == "n")
                  break;
            }
            break;

         case 3:
            while(true){
               printTitle();
               success = program.displayBoardingPass();
               cin.get(); cin.get();
               if(success)
                  break;
               cout << "Try again? (y/n) ";
               cin >> temp;
               if(temp == "n")
                  break;
            }
            break;

         case 4:
            printTitle();  
            program.displayAllFlights();
            cin.get(); cin.get();
            break;
         default:
            printTitle();
            cout << "Invalid Choice.";
            cin.get(); cin.get();
            break;
      }
   }
   
   cout << "\n\n";
   return 0;
}