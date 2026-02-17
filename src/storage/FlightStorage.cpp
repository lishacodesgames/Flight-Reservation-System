#include "storage/FlightStorage.h"
#include "utils/VectorUtils.h"
#include <vector>
#include <string>
#include <fstream>
#include <optional>
#include <filesystem>

static std::filesystem::path repoPath;

FlightStorage::FlightStorage(){}
FlightStorage::FlightStorage(const std::string& BASE_PATH){
   std::filesystem::path BASE{BASE_PATH};
   repoPath = BASE;
   initTextFiles(BASE);
}
void FlightStorage::initTextFiles(std::filesystem::path& BASE){
   textFiles = BASE / "text-files";
}

std::filesystem::path FlightStorage::textFiles = repoPath / "text-files";

/// @return vector of string IDs
std::vector<std::string> FlightStorage::getFlightIDs() {
   std::string ID;
   std::vector<std::string> flights = {};

   std::ifstream txtFlights(textFiles / "flights.txt");
   while(getline(txtFlights, ID)) {
      flights.push_back(ID);
   }
   txtFlights.close();

   return flights;
}

std::vector<std::string> FlightStorage::getCities() {
   std::string city;
   std::vector<std::string> cities = {};

   std::ifstream txtCities(textFiles / "cities.txt");
   while(getline(txtCities, city)) {
      cities.push_back(city);
   }
   txtCities.close();

   return cities;
}

void FlightStorage::saveFlight(Flight& flight) {
   std::ofstream txtFlights(textFiles / "flights.txt", std::ios::app);
   txtFlights << "\n" << flight.ID;
   txtFlights.close();

   std::ofstream txtFlightsInfo(textFiles / "flightsInfo.txt", std::ios::app);
   txtFlightsInfo << "\n" << flight.ID << "|" 
   << flight.origin << "," << flight.destination << "|" 
   << flight.emptySeats << "/" << flight.totalSeats << "|" 
   << flight.departureTime << "|" << flight.gate << "|" << flight.terminal;
   txtFlightsInfo.close();
}

std::optional<Flight> FlightStorage::getFlightInfo(const std::string& ID) {
   //confirm ID
   int index = getIndex(ID, getFlightIDs());
   if (index == -1)
      return std::nullopt;

   //show ID
   Flight f;
   std::string temp;
   std::ifstream txtFlights(textFiles / "flightsInfo.txt");
   
   for(int i = 0; i < index; i++) {
      getline(txtFlights, temp);
   }

   getline(txtFlights, f.ID, '|');
   getline(txtFlights, f.origin, ',');
   getline(txtFlights, f.destination, '|');
   getline(txtFlights, temp, '/');
   f.emptySeats = stoi(temp);
   getline(txtFlights, temp, '|');
   f.totalSeats = stoi(temp);
   getline(txtFlights, f.departureTime, '|');
   getline(txtFlights, temp, '|');
   f.gate = temp[0];
   getline(txtFlights, temp);
   f.terminal = stoi(temp);

   txtFlights.close();

   return f;
}