#include "ui/Menu.h"
#include "ui/FlightView.h"
#include "ui/PassengerView.h"
#include "storage/FlightStorage.h"
#include "storage/PassengerStorage.h"
#include "core/Flight.h"
#include <cstdlib>
#include <ctime>

enum class Choice {Exit, Book, ViewFlight, ViewBoardingPass, ViewAllFlights}; // own class?

int main() {
   std::srand(time(0));
   //declarations TODO
   Choice choice;
   int rawChoice;

   while(true) {
      rawChoice = MainMenu();
      choice = static_cast<Choice>(rawChoice);

      switch(choice) {
         case Choice::Exit: 
            return 0;

         case Choice::Book: {
            //TODO
            break;
         }

         case Choice::ViewFlight: {
            FlightStorage storage;
            Flight f;
            bool success, shouldContinue = true;
            std::string id;

            while(shouldContinue) {
               id = getIDforShow();
               success = storage.getFlightInfo(id, f);
               std::cin.get();
               if(success) {
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
               std::cin.get();

               if(success)
                  shouldContinue = false;
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