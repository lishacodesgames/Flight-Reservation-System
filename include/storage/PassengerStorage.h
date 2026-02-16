#pragma once
#include "core/Passenger.h"
#include <string>
#include <filesystem>
#include <optional>

class PassengerStorage {
   static std::filesystem::path TxtPassengers;
public:
   PassengerStorage();
   PassengerStorage(const std::string& BASE_PATH);

   void initTextPassengers(std::filesystem::path& BASE);
   std::optional<Passenger> getPassengerInfo(std::string inputName);
};