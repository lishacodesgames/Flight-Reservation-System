#include "services/BookingService.h"
#include "storage/FlightStorage.h"
#include "ui/BookingUI.h"
#include "utils/VectorUtils.h"
#include <string>
#include <vector>
#include <optional>

#include <iostream> //REMOVE 
void BookingService::bookFlight() {
   std::string ID = displayBookingOptions();
   if(ID == "" || ID == "0")
      std::cout << "FLIGHT WAS NOT BOOKED.";
   else 
      std::cout << "FLIGHT BOOKED: " << ID;
}

/// @return originFlights
std::vector<std::string> BookingService::getValidFlights(std::string depCity) {
   std::vector<std::string> allFlights = storage.getFlightIDs();

   std::vector<std::string> originFlights = {};
   for (std::string id : allFlights) {
      flight = storage.getFlightInfo(id).value();
      if (flight.origin == depCity)
         originFlights.push_back(id);
   }

   return originFlights;
}
/// @return destinationFlights
std::vector<std::string> BookingService::getValidFlights(std::string depCity, std::string arrCity) {
   std::vector<std::string> allFlights = storage.getFlightIDs();
   std::vector<std::string> originFlights = getValidFlights(depCity);

   std::vector<std::string> destinationFlights = {};
   for (std::string id : originFlights) {
      flight = storage.getFlightInfo(id).value();
      if (flight.destination == arrCity)
         destinationFlights.push_back(id);
   }

   return destinationFlights;
}

std::vector<std::string> BookingService::getAllFlights() {
   return storage.getFlightIDs();
}

std::optional<Flight> BookingService::getFlight(std::string ID) {
   return storage.getFlightInfo(ID);
}

bool isValidCity(std::string city, BookingService& booker) {
   int index = getIndex(city, booker.storage.getCities());
   return index == -1 ? false : true;
}