#pragma once
#include <iostream>
#include <string>
#include <optional>

void printTitle();

/// @param range checks if input ∈ [range.first, range.second]
/// @retval bool: IF value is valid
/// @retval -1 IF not valid, parsed integer value if valid
std::pair<bool, int> validMenuInput(std::string input, std::pair<int, int> range);

int MainMenu();
std::string getIDforShow();

/// @attention starts with \\n
bool promptTryAgain();

/// @attention starts with \\n
/// @param prompt (must NOT end with \\n) What the user will be shown before asking (y/n)?
bool promptTryAgain(std::string prompt);