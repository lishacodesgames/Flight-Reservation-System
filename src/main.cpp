#include "ui/MenuUI.h"
#include "ui/FlightUI.h"
#include "ui/PassengerUI.h"
#include "services/BookingService.h"
#include "storage/FlightStorage.h"
#include "storage/PassengerStorage.h"
#include "core/Flight.h"
#include <cstdlib>
#include <ctime>

//rule of thumb: MAIN SHOULD NEVER CALL ANYTHING BUT UI

enum class Choice {Exit, Book, ViewFlight, ViewBoardingPass, ViewAllFlights};

int main(int argc, char* argv[]) {
   if(argc < 2) {
      std::cout << "\nBase path not provided!\n";
      return 1;
   }
   std::string BASE_PATH = argv[1];
   FlightStorage storage(BASE_PATH);
   PassengerStorage storage(BASE_PATH);
   BookingService booker;

   std::srand(time(0));
   Choice choice;

   while(true) {
      choice = static_cast<Choice>(MainMenu());

      switch(choice) {
         case Choice::Exit: 
            return 0;

         case Choice::Book: {
            booker.bookFlight();
            std::cin.get();
            break;
         }

         case Choice::ViewFlight: {
            Flight f;
            std::optional<Flight> success;
            bool shouldContinue = true;
            std::string id;

            while(shouldContinue) {
               id = getIDforShow();
               success = storage.getFlightInfo(id);
               if(success) {
                  printTitle();
                  f = success.value();
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
            displayAllFlights();
            std::cin.get();
            break;
         }
      }
   }

   return 0;
}