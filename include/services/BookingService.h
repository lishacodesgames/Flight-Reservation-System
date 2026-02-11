#pragma once
#include <string>
#include <vector>

class BookingService {
public:
   void bookFlight();
   std::vector<std::string> getValidFlights(std::string depCity);
   std::vector<std::string> getValidFlights(std::string depCity, std::string arrCity);
};