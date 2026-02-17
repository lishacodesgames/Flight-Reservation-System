#pragma once
#include "core/Flight.h"
#include "storage/FlightStorage.h"

/// @test layering ✔
class FlightGenerator {
   FlightStorage storage;
   public:
   Flight generateRandom();
};