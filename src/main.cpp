#include "ui/Menu.h"
#include "ui/FlightView.h"
#include "ui/PassengerView.h"
#include "services/BookingService.h"
#include "storage/FlightStorage.h"
#include "storage/PassengerStorage.h"
#include "core/Flight.h"
#include <cstdlib>
#include <ctime>
#include <iostream> // for invalid args

/// @todo TODO fix storage declarations

enum class Choice {Exit, Book, ViewFlight, ViewBoardingPass, ViewAllFlights};

int main(int argc, char* argv[]) {
   if(argc < 2) {
      std::cout << "\nBase path not provided!\n";
      return 1;
   }
   std::string BASE_PATH = argv[1];
   FlightStorage storage(BASE_PATH);

   std::srand(time(0));
   //declarations TODO
   Choice choice;

   while(true) {
      choice = static_cast<Choice>(MainMenu());

      switch(choice) {
         case Choice::Exit: 
            return 0;

         case Choice::Book: {
            BookingService booker;
            booker.bookFlight();
            std::cin.get();
            break;
         }

         case Choice::ViewFlight: {
            FlightStorage storage(BASE_PATH);
            Flight f;
            bool success, shouldContinue = true;
            std::string id;

            while(shouldContinue) {
               id = getIDforShow();
               success = storage.getFlightInfo(id, f);
               if(success) {
                  printTitle();
                  printFlightInfo(f);
                  std::cin.get();
                  shouldContinue = false;
               }
               else
                  shouldContinue = promptTryAgain();
            }

            break;
         }

         case Choice::ViewBoardingPass: {
            bool success, shouldContinue = true;
            while (shouldContinue) {
               success = displayBoardingPass();
               
               if(success) {
                  std::cin.get();
                  shouldContinue = false;
               }
               else
                  shouldContinue = promptTryAgain();
            }

            break;
         }

         case Choice::ViewAllFlights: {
            displayAllFlights(storage);
            std::cin.get();
            break;
         }
      }
   }

   return 0;
}