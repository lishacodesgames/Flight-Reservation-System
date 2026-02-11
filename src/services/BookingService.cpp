#include "services/BookingService.h"
#include "core/Flight.h"
#include "storage/FlightStorage.h"
#include "ui/BookingView.h"
#include <string>
#include <vector>

#include <iostream> //REMOVE REMOVE TODO TODO ATTENTIONS
void BookingService::bookFlight() {
   std::string ID = displayBookingOptions();
   if(ID == "" || ID == "0")
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