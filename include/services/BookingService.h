#pragma once
#include "core/Flight.h"
#include "storage/FlightStorage.h"
#include <string>
#include <vector>
#include <optional>

class BookingService {
   Flight flight;
   FlightStorage storage;
public:
   void bookFlight();
   std::vector<std::string> getValidFlights(std::string depCity);
   std::vector<std::string> getValidFlights(std::string depCity, std::string arrCity);
   std::vector<std::string> getAllFlights();

   std::optional<Flight> getFlight(std::string ID);

   friend bool isValidCity(std::string city, BookingService& booker);
};