#include "services/FlightGenerator.h"
#include "core/Flight.h"
#include "storage/FlightStorage.h"
#include <vector>
#include <string>
/// @test layering ✔

Flight FlightGenerator::generateRandom() {
   Flight flight;

   // ID
   flight.ID = (char)(65 + rand() % 26) + std::to_string(100 + rand() % 900);

   // cities
   std::vector<std::string> cities = storage.getCities();
   flight.origin = cities[rand() % cities.size()];
   do {
      flight.destination = cities[rand() % cities.size()];
   } while (flight.origin == flight.destination);

   // seats
   flight.totalSeats = 10 * ((rand() % (flight.MAX_SEATS/10 - flight.MIN_SEATS/10)) + flight.MIN_SEATS/10); // ∈ [MIN_SEATS, MAX_SEATS] as a multiple of 10
   flight.emptySeats = rand() % flight.totalSeats;

   // departure time
   std::string minuteIncrements[4] = {"00", "15", "30", "45"};
   std::string hour = std::to_string(rand() % 24);
   if(hour.size() == 1)
      hour = "0" + hour;

   flight.departureTime = hour + ":" + minuteIncrements[rand() % 4];

   //gate & terminal
   flight.gate = (char)(65 + rand() % 26);
   flight.terminal = 1 + rand() % 5;

   return flight;
}