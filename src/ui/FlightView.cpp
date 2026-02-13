#include "ui/FlightView.h"
#include "ui/Menu.h"
#include "storage/FlightStorage.h"
#include <vector>
#include <string>
#include <iostream>

/// @todo TODO fix storage declarations

void printFlightInfo(Flight& f) {
   std::cout << "Flight " << f.ID << "\n"
   << f.origin << " -> " << f.destination << "\n"
   << "Seats available: " << f.emptySeats << "/" << f.totalSeats << "\n"
   << "Departing at " << f.departureTime << "\n"
   << "Gate " << f.gate << "\t Terminal " << f.terminal << "\n";
   std::cout << "===============================\n";
}

void displayAllFlights(FlightStorage& storage) {
   Flight f;
   std::vector<std::string> flights = storage.getFlightIDs();

   printTitle();
   for(std::string id : flights) {
      storage.getFlightInfo(id, f);
      printFlightInfo(f);
   }
}