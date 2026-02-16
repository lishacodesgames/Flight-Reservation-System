#include "ui/PassengerUI.h"
#include "ui/MenuUI.h"
#include "core/Passenger.h"
#include "core/Flight.h"
#include "storage/PassengerStorage.h"
#include "storage/FlightStorage.h"
#include <iostream>
#include <optional>

bool displayBoardingPass() {
   std::string temp;
   std::string name;
   PassengerStorage Pstorage;
   FlightStorage Fstorage;
   Passenger p;
   Flight f;
   
   printTitle();
   std::cout << "Enter name of passenger: ";
   getline(std::cin, name);

   std::optional<Passenger> passenger = Pstorage.getPassengerInfo(name);

   if(!passenger) {
      printTitle();
      std::cout << "\"" << name << "\" does not have a boarding pass.\n";
      return false;
   }

   f = Fstorage.getFlightInfo(passenger.value().bookedFlight).value();
   printTitle();
   std::cout 
   << "NAME OF PASSENGER: " << p.name << "\t AGE: " << p.age << "\n"
   << "SEAT NO. " << p.seat << "\n"
   << "TO: " << f.destination << "\t FROM: " << f.origin << "\n"
   << "TIME: " << f.departureTime << "\n"
   << "FLIGHT: " << p.bookedFlight << "\n"
   << "GATE " << f.gate << "\t TERMINAL " << f.terminal << "\n";
   std::cout << "===============================\n";
   
   return true;
}