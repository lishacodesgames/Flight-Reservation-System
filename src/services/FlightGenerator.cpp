#include "services/FlightGenerator.h"
#include "core/Flight.h"
#include "storage/FlightStorage.h"
#include <vector>
#include <string>

Flight FlightGenerator::generateRandom() {
   Flight f;
   FlightStorage storage;

   // ID
   f.ID = (char)(65 + rand() % 26) + std::to_string(100 + rand() % 900);

   // cities
   std::vector<std::string> cities = storage.getCities();
   f.origin = cities[rand() % cities.size()];
   do {
      f.destination = cities[rand() % cities.size()];
   } while (f.origin == f.destination);

   // seats
   f.totalSeats = 10 * ((rand() % (f.MAX_SEATS/10 - f.MIN_SEATS/10)) + f.MIN_SEATS/10); // ∈ [MIN_SEATS, MAX_SEATS] as a multiple of 10
   f.emptySeats = rand() % f.totalSeats;

   // departure time
   std::string minuteIncrements[4] = {"00", "15", "30", "45"};
   std::string hour = std::to_string(rand() % 24);
   if(hour.size() == 1)
      hour = "0" + hour;

   f.departureTime = hour + ":" + minuteIncrements[rand() % 4];

   //gate & terminal
   f.gate = (char)(65 + rand() % 26);
   f.terminal = 1 + rand() % 5;

   return f;
}