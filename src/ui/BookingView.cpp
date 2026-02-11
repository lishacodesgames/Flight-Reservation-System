#include "ui/BookingView.h"
#include "ui/FlightView.h"
#include "ui/Menu.h"
#include "core/Flight.h"
#include "services/BookingService.h"
#include "storage/FlightStorage.h"
#include "utils/ParseUtils.h"
#include "utils/VectorUtils.h"
#include <iostream>
#include <string>
#include <vector>

/// @param type "origin" OR "destination" gets printed in the prompt
std::string getCity(std::string type) {
   std::string city;
   int index;
   FlightStorage storage;
   bool repeat = false;

   printTitle();
   std::cout << "Enter your " + type + " city: ";
   getline(std::cin, city);

   index = getIndex(city, storage.getCities());

   if(index == -1) {
      repeat = promptTryAgain(city + " does not exist.\n");
      return repeat ? getCity(type) : "";
   }
   else 
      return city;
}

int BookingMenu() {
   std::string input;
   int choice;
   bool invalidChoice;

   printTitle();
   do {
      std::cout << "===============================\n";
      std::cout << "[0] Go back\n";
      std::cout << "[1] Choose a flight by ID\n";
      std::cout << "[2] Book from Origin city\n";
      std::cout << "===============================\n";
      std::cout << "Enter your choice: ";
      getline(std::cin, input);

      // error1: input not a number
      choice = parseInt(input);
      if (choice == -100 || choice == 100) {
         printTitle();
         std::cout << (choice == -100 ? "\nPlease enter a number.\n" : "\nWhy would you do that?\n");
         invalidChoice = true;
         continue;
      }

      //error2: incorrect number
      invalidChoice = (choice < 0 || choice > 4);
      if (invalidChoice) {
         printTitle();
         std::cout << "\nInvalid choice.\n";
      }
   } while (invalidChoice);

   return choice;
}

int OriginChoiceMenu() {
   std::string input;
   int choice;
   bool invalidChoice;

   do {
      std::cout << "===============================\n";
      std::cout << "[0] Go back\n";
      std::cout << "[1] Choose a flight by ID\n";
      std::cout << "[2] Book from Destination city\n";
      std::cout << "===============================\n";
      std::cout << "Enter your choice: ";
      getline(std::cin, input);

      // error1: input not a number
      choice = parseInt(input);
      if (choice == -100 || choice == 100) {
         printTitle();
         std::cout << (choice == -100 ? "\nPlease enter a number.\n" : "\nWhy would you do that?\n");
         invalidChoice = true;
         continue;
      }

      //error2: incorrect number
      invalidChoice = (choice < 0 || choice > 4);
      if (invalidChoice) {
         printTitle();
         std::cout << "\nInvalid choice.\n";
      }
   } while (invalidChoice);

   if (choice == 2)
      return 3; // bcz BookingChoice::byDestination == 3
   else
      return choice;
}

///@param prompt "departing from origin" OR "going from origin -> destination"
int OneFlightMenu(std::string prompt, std::string flightID) {
   std::string input;
   int choice;
   bool invalidChoice = true;
   printTitle();
   do {   
      std::cout << "There is 1 flight " + prompt << "\n";
      std::cout << "===============================\n";
      std::cout << "[0] Go back\n";
      std::cout << "[1] See flight details\n";
      std::cout << "[2] Book the flight\n";
      std::cout << "===============================\n";
      std::cout << "Enter your choice: ";
      getline(std::cin, input);

      // error1: input not a number
      choice = parseInt(input);
      if (choice == -100 || choice == 100) {
         printTitle();
         std::cout << (choice == -100 ? "\nPlease enter a number.\n" : "\nWhy would you do that?\n");
         invalidChoice = true;
         continue;
      }

      //error2: incorrect number
      invalidChoice = (choice < 0 || choice > 4);
      if (invalidChoice) {
         printTitle();
         std::cout << "\nInvalid choice.\n";
      }
   } while (invalidChoice);

   return choice;
}

std::string displayBookingOptions() {
   BookingChoice choice = static_cast<BookingChoice>(BookingMenu());

   switch (choice) {
      case BookingChoice::GoBack:
         return "";
      case BookingChoice::byID: {
         FlightStorage storage;
         return getID(storage.getFlightIDs());
      }
      case BookingChoice::byOrigin: {
         std::string depCity = getCity("origin"); // departure city
         if (depCity == "") // user decided to quit
            return "";
         
         BookingService booker;
         std::vector<std::string> originFlights = booker.getValidFlights(depCity);

         switch(originFlights.size()) {
            case 0:
               std::cout << "There are 0 flights departing from " << depCity << "...";
               std::cin.get();
               return "0";
            
            case 1: {
               int menuChoice = OneFlightMenu("departing from " + depCity, originFlights[0]);
               bool toContinue;

               while (true) {
                  switch (menuChoice) {
                     case 0:
                        return displayBookingOptions();
                     
                     case 1: {
                        FlightStorage storage;
                        Flight f;
                        std::string input;

                        printTitle();
                        storage.getFlightInfo(originFlights[0], f);
                        printFlightInfo(f);
                        std::cin.get();
                        while (true) {
                           std::cout << "Would you like to book this flight? (y/n) ";
                           getline(std::cin, input);

                           if (input == "y")
                              return originFlights[0];
                           else if (input == "n")
                              return displayBookingOptions();
                           else {
                              std::cout << "Invalid input.\n";
                           }
                        }
                        break;
                     }

                     case 2:
                        return originFlights[0];
                     }
                  };
                  break;
               }
            default:
               printTitle();
               std::cout << "There are " << originFlights.size() << " flights departing from " << depCity << ".\n";
               break;
         }

         choice = static_cast<BookingChoice>(OriginChoiceMenu());

         switch (choice) {
            case BookingChoice::GoBack: 
               return displayBookingOptions(); // loop back

            case BookingChoice::byID: {
               FlightStorage storage;
               Flight f;

               printTitle();
               return getID(originFlights);
            }
            case BookingChoice::byDestination: {
               std::string arrCity = getCity("destination"); // arrival city
               if (arrCity == "") // user decided to quit
                  return "";
               
               std::vector<std::string> destinationFlights = booker.getValidFlights(depCity, arrCity);

               switch(destinationFlights.size()) {
                  case 0:
                     std::cout << "There are 0 flights going from " << depCity << " -> " << arrCity << ".\n";
                     std::cin.get();
                     return "0";
            
                  case 1: {
                     int menuChoice = OneFlightMenu("going from " + depCity + " -> " + arrCity, destinationFlights[0]);
                     bool toContinue;

                     while (true) {
                        switch (menuChoice) {
                           case 0:
                              return displayBookingOptions();
                           
                           case 1: {
                              FlightStorage storage;
                              Flight f;
                              std::string input;

                              printTitle();
                              storage.getFlightInfo(destinationFlights[0], f);
                              printFlightInfo(f);
                              std::cin.get();
                              while (true) {
                                 std::cout << "Would you like to book this flight? (y/n) ";
                                 getline(std::cin, input);

                                 if (input == "y") {
                                    return destinationFlights[0];
                                 }
                                 else if (input == "n") {
                                    return displayBookingOptions();
                                 }
                                 else {
                                    std::cout << "Invalid input.\n";
                                 }
                              }
                              break;
                           }

                           case 2:
                              return originFlights[0];
                        }
                     };
                     break;
                  }
                  default:
                     printTitle();
                     std::cout << "There are " << destinationFlights.size() << " flights going from " << depCity << " -> " << arrCity << ".\n";
                     std::cout << "===============================\n";
                     break;
               }

               printTitle();
               return getID(destinationFlights);
            }
         }

         break;
      }
   }

   return "";
}

/**
 * @brief 1. if ID valid, return it
 * @brief 2. if ID exists but not in validFlights, prompt user "book anyways?"
 * @brief 3. if ID doesn't exist, recursive call to re-prompt ID 
 */
std::string getID(std::vector<std::string> validFlights) {
   if(validFlights.size() == 0) {
      std::cout << "Something went wrong.\n";
      std::cin.get();
      return displayBookingOptions();
   }
   
   // print flights
   FlightStorage storage;
   Flight f;
   
   if(validFlights == storage.getFlightIDs()) 
      displayAllFlights();
   else {
      for (std::string id : validFlights) {
         storage.getFlightInfo(id, f);
         printFlightInfo(f);
      }
   }
   
   std::string ID;
   // flight list ends with "===\n"
   std::cout << "===============================\n";
   std::cout << "Enter flight ID: ";
   getline(std::cin, ID);

   int validIndex = getIndex(ID, validFlights);
   if (validIndex != -1) // valid ID
      return ID;

   std::string temp;
   std::vector<std::string> allFlights = storage.getFlightIDs();
   if(validFlights != allFlights) {
      int flightIndex = getIndex(ID, allFlights);

      if(flightIndex != -1) { // ID doesn't match criteria but it exists
         std::cout << "\nFlight " << ID << " does not match the selected criteria.\n";
         std::cout << "Would you like to book flight " << ID << " anyways? (y/n) ";
         getline(std::cin, temp);
         if (temp == "y")
            return ID;
         else if (temp == "n")
            return displayBookingOptions();
         else {
            printTitle();
            std::cout << "Invalid input.\n";
            return getID(validFlights);
         }
      }
   }

   // flight doesn't exist
   bool tryAgain = promptTryAgain("\nFlight " + ID + " does not exist.");

   if(tryAgain) {
      printTitle();
      return getID(validFlights);
   }
   else
      return displayBookingOptions();
}