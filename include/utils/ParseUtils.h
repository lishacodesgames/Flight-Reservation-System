#pragma once
#include <string>
#include <optional>

enum class intErrorCode {NoError = 0, InvalidArg = -100, OutOfRange = 100};

/// @retval -100 if input not a number
/// @retval  100 if input number out of range
std::pair< std::optional<int>, intErrorCode > parseInt(std::string input);