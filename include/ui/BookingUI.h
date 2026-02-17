#pragma once
#include "services/BookingService.h"
#include <string>
#include <vector>
#include <optional>

enum class BookingChoice {GoBack, byID, byOrigin, byDestination};

class BookingUI {
  BookingService booker;
public:
  /// @param type "origin" OR "destination" gets printed in the prompt
	std::optional<std::string> getCity(std::string type);
	
	int BookingMenu();
	int OriginChoiceMenu();

  	/// @param prompt "departing from origin" OR "going from origin -> destination"
	int OneFlightMenu(std::string prompt, std::string flightID);

	std::string displayBookingOptions();
	std::string getID(std::vector<std::string> validFlights);
};
