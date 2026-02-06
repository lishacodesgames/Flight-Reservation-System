/* WELCOME TO AIR ROUTE SYSTEM */
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

class Airport {
protected:
   vector<string> flights = {};
   vector<string> cities = {};
public:
   Airport() {
      flights = getFlights();
      cities = getCities();
   }

   vector<string> getFlights() {
      string id;
      vector<string> flights;

      ifstream txtFlights("flights.txt");
      while(getline(txtFlights, id)) {
         flights.push_back(id);
      }
      txtFlights.close();

      return flights;
   }

   vector<string> getCities() {
      string city;
      vector<string> cities;

      ifstream txtCities("cities.txt");
      while(getline(txtCities, city)) {
         cities.push_back(city);
      }
      txtCities.close();

      return cities;
   }
};

int main() {
   srand(time(0));

   
   cout << "\n\n";
   return 0;
}