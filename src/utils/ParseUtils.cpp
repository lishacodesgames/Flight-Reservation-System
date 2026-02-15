#include "utils/ParseUtils.h"
#include <iostream> // ik it's bad.
#include <stdexcept>

std::pair<std::optional<int>, intErrorCode> parseInt(std::string input) {
   int output;

   try {
      output = std::stoi(input);
   } catch(const std::invalid_argument& e) {
      return {std::nullopt, intErrorCode::InvalidArg};
   } catch(const std::out_of_range& e) {
      return {std::nullopt, intErrorCode::OutOfRange};
   }

   return {output, intErrorCode::NoError};
}