#pragma once

#include <string>

struct Flight {
   static constexpr int MIN_SEATS = 50;
   static constexpr int MAX_SEATS = 500;

   std::string ID;
   std::string origin, destination;
   int emptySeats, totalSeats;
   std::string departureTime;
   char gate;
   short terminal;
};