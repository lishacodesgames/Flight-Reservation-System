#pragma once
#include "core/Flight.h"
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

class FlightStorage {
   static std::filesystem::path textFiles;
public:
   FlightStorage();
   FlightStorage(const std::string& BASE_PATH);
   void initTextFiles(std::filesystem::path& BASE);

   std::vector<std::string> getFlightIDs();
   std::vector<std::string> getCities();
   void saveFlight(Flight& flight);
   std::optional<Flight> getFlightInfo(const std::string& ID);
};