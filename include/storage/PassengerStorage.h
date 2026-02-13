#pragma once
#include "core/Passenger.h"
#include <string>
#include <filesystem>

class PassengerStorage {
   std::filesystem::path textFiles;
public:
   PassengerStorage(const std::filesystem::path& BASE);
   bool getPassengerInfo(std::string name, Passenger& outputP);
};