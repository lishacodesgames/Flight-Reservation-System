#include "storage/PassengerStorage.h"
#include "core/Passenger.h"
#include <string>
#include <fstream>

bool PassengerStorage::getPassengerInfo(std::string name, Passenger& outputP) {
   std::string temp;
   bool passengerExists = false;
   
   std::ifstream passengers("../text-files/passengers.txt");
   while(getline(passengers, outputP.name, ',')) {
      if(outputP.name != name) {
         getline(passengers, temp);
      }
      else {
         passengerExists = true;

         getline(passengers, temp, ',');
         outputP.age = std::stoi(temp);
         getline(passengers, outputP.bookedFlight, ',');
         getline(passengers, outputP.seat);
         break;
      }
   }
   passengers.close();

   if (!passengerExists)
      return false;
   else
      return true;
}