#include "utils/ParseUtils.h"
#include <stdexcept>
#include <iostream> //bad?

/**
 * @retval -100 if input not a number
 * @retval  100 if input number out of range
 */
int parseInt(std::string input) {
   int output;

   try {
      output = std::stoi(input);
   } catch(const std::invalid_argument& e) {
      std::cout << "\nInvalid input.\n";
      return static_cast<int>(intErrorCode::InvalidArg);
   } catch(const std::out_of_range& e) {
      std::cout << "\nWhy would you do that?\n";
      return static_cast<int>(intErrorCode::OutOfRange);
   }

   return output;
}