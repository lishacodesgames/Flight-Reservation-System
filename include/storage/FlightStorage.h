#pragma once
#include <vector>
#include <string>
#include <filesystem>

class FlightStorage {
   std::filesystem::path textFiles;
public:
   FlightStorage(const std::filesystem::path& BASE);
   std::vector<std::string> getFlightIDs();
   std::vector<std::string> getCities();
   void saveFlight(Flight& flight);
   bool getFlightInfo(const std::string& ID, Flight& outputFlight);
};