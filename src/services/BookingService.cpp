#include "services/BookingService.h"
#include "core/Flight.h"
#include "storage/FlightStorage.h"
#include "ui/BookingView.h"

/// @todo TODO fix storage declarations

#include <iostream> /// @todo TODO REMOVE!
void BookingService::bookFlight() {
   std::string ID = displayBookingOptions();
   if (ID == "" || ID == "0")
      std::cout << "FLIGHT WAS NOT BOOKED.";
   else 
      std::cout << "FLIGHT BOOKED: " << ID;
}

/// @return originFlights
std::vector<std::string> BookingService::getValidFlights(std::string depCity) {
   FlightStorage storage;
   Flight f;
   std::vector<std::string> allFlights = storage.getFlightIDs();

   std::vector<std::string> originFlights = {};
   for (std::string id : allFlights) {
      storage.getFlightInfo(id, f);
      if (f.origin == depCity)
         originFlights.push_back(id);
   }

   return originFlights;
}

/// @return destinationFlights
std::vector<std::string> BookingService::getValidFlights(std::string depCity, std::string arrCity) {
   FlightStorage storage;
   Flight f;
   std::vector<std::string> allFlights = storage.getFlightIDs();
   std::vector<std::string> originFlights = getValidFlights(depCity);

   std::vector<std::string> destinationFlights = {};
   for (std::string id : originFlights) {
      storage.getFlightInfo(id, f);
      if (f.destination == arrCity)
         destinationFlights.push_back(id);
   }

   return destinationFlights;
}