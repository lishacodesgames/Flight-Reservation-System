#include "storage/PassengerStorage.h"
#include "core/Passenger.h"
#include <string>
#include <fstream>

PassengerStorage::PassengerStorage(){}
PassengerStorage::PassengerStorage(const std::string& BASE_PATH) {
   std::filesystem::path BASE{BASE_PATH};
   initTextPassengers(BASE);
}
void PassengerStorage::initTextPassengers(std::filesystem::path& BASE) {
   TxtPassengers = BASE / "text-files" / "passengers.txt";
}

std::optional<Passenger> PassengerStorage::getPassengerInfo(std::string inputName) {
   std::string temp;
   bool passengerExists = false;
   Passenger p;
   
   std::ifstream passengers(TxtPassengers);
   while(getline(passengers, p.name, ',')) {
      if(p.name != inputName) {
         getline(passengers, temp);
      }
      else {
         passengerExists = true;

         getline(passengers, temp, ',');
         p.age = std::stoi(temp);
         getline(passengers, p.bookedFlight, ',');
         getline(passengers, p.seat);
         break;
      }
   }
   passengers.close();

   if (!passengerExists)
      return std::nullopt;
   else
      return p;
}