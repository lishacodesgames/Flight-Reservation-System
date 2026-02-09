#include "storage/FlightStorage.h"
#include "core/Flight.h"
#include "utils/VectorUtils.h"
#include <vector>
#include <string>
#include <fstream>

   std::vector<std::string> FlightStorage::getFlightIDs() {
      std::string ID;
      std::vector<std::string> flights = {};

      std::ifstream txtFlights("../text-files/flights.txt");
      while(getline(txtFlights, ID)) {
         flights.push_back(ID);
      }
      txtFlights.close();

      return flights;
   }

   std::vector<std::string> FlightStorage::getCities() {
      std::string city;
      std::vector<std::string> cities = {};

      std::ifstream txtCities("../text-files/cities.txt");
      while(getline(txtCities, city)) {
         cities.push_back(city);
      }
      txtCities.close();

      return cities;
   }

   void FlightStorage::saveFlight(Flight& flight) {
      std::ofstream txtFlights("../text-files/flights.txt", std::ios::app); //?
      txtFlights << "\n" << flight.ID;
      txtFlights.close();

      std::ofstream txtFlightsInfo("../text-files/flightsInfo.txt", std::ios::app); //?
      txtFlightsInfo << "\n" << flight.ID << "|" 
      << flight.origin << "," << flight.destination << "|" 
      << flight.emptySeats << "/" << flight.totalSeats << "|" 
      << flight.departureTime << "|" << flight.gate << "|" << flight.terminal;
      txtFlightsInfo.close();
   }

   bool FlightStorage::getFlightInfo(const std::string& ID, Flight& outputFlight) {
      //confirm ID
      int index = getIndex(ID, getFlightIDs());
      if (index == -1)
         return false;

      std::string temp;
      std::ifstream txtFlights("../text-files/flightsInfo.txt");
      
      for(int i = 0; i < index; i++) {
         getline(txtFlights, temp);
      }

      getline(txtFlights, outputFlight.ID, '|');
      getline(txtFlights, outputFlight.origin, ',');
      getline(txtFlights, outputFlight.destination, '|');
      getline(txtFlights, temp, '/');
      outputFlight.emptySeats = stoi(temp);
      getline(txtFlights, temp, '|');
      outputFlight.totalSeats = stoi(temp);
      getline(txtFlights, outputFlight.departureTime, '|');
      getline(txtFlights, temp, '|');
      outputFlight.gate = temp[0];
      getline(txtFlights, temp);
      outputFlight.terminal = stoi(temp);

      txtFlights.close();

      return true;
   }