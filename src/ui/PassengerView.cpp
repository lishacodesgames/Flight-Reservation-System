#include "ui/PassengerView.h"
#include "ui/Menu.h"
#include "core/Passenger.h"
#include "core/Flight.h"
#include "storage/PassengerStorage.h"
#include "storage/FlightStorage.h"
#include <iostream>

bool displayBoardingPass() {
   std::string temp, name;
   PassengerStorage Pstorage;
   FlightStorage Fstorage;
   Passenger p;
   Flight f;
   
   printTitle();
   std::cout << "Enter name of passenger: ";
   getline(std::cin, name);

   bool passengerExists = Pstorage.getPassengerInfo(name, p);

   if(!passengerExists) {
      printTitle();
      std::cout << "\"" << name << "\" does not have a boarding pass.\n";
      return false;
   }

   Fstorage.getFlightInfo(p.bookedFlight, f);
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