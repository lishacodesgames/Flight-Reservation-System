#include "ui/MenuUI.h"
#include "utils/ParseUtils.h"
#include <iostream>
#include <string>

void printTitle() {
   #if defined(_WIN32)
      system("cls");
   #elif defined(__APPLE__)
      std::cout << "\033c";
   #endif

   std::cout << "===============================\n";
   std::cout << "  WELCOME TO LISHA'S AIRPORT!  \n";
   std::cout << "===============================\n";
}

std::pair<bool, int> validMenuInput(std::string input, std::pair<int, int> range) {
   std::pair< std::optional<int>, intErrorCode > choice;
   
   // X error1: input not a number
   choice = parseInt(input);

   if(!choice.first) {
      printTitle();

      if(choice.second == intErrorCode::InvalidArg)
         std::cout << "\nPlease enter a number.\n";
      else if(choice.second == intErrorCode::OutOfRange)
         std::cout << "\nWhy would you do that?\n";

      return {false, -1};
   }

   return {true, choice.first.value()};
}

int MainMenu() {
   std::string input;
   std::pair <bool, int> choice;
   
   printTitle();
   do {
      std::cout << "===============================\n";
      std::cout << "[0] Exit\n";
      std::cout << "[1] Book a flight\n";
      std::cout << "[2] View flight information\n";
      std::cout << "[3] View boarding pass\n";
      std::cout << "[4] View all flights\n";
      std::cout << "===============================\n";
      std::cout << "Enter your choice: ";
      getline(std::cin, input);

      choice = validMenuInput(input, {0, 4});
   } while (!choice.first);

   return choice.second;
}

std::string getIDforShow() {
   std::string id;
   printTitle();
   std::cout << "Enter flight ID: ";
   getline(std::cin, id);

   return id;
}

bool promptTryAgain() {
   std::string ans;
   std::cout << "\nInvalid input.";
   std::cout << "\nTry again? (y/n) ";
   getline(std::cin, ans);

   for(char& ch : ans) {
      ch = std::toupper(static_cast<unsigned char>(ch)); // to avoid undefined behaviour with non-ASCII characters
   }

   if (ans == "Y" || ans == "YES") 
      return true;
   else if (ans == "N" || ans == "NO")
      return false;
   else
      return promptTryAgain();
}

bool promptTryAgain(std::string prompt) {
   std::string ans;
   std::cout << prompt << "\nTry again? (y/n) ";
   getline(std::cin, ans);

   for(char& ch : ans) {
      ch = std::toupper(static_cast<unsigned char>(ch)); // to avoid undefined behaviour with non-ASCII characters
   }

   if (ans == "Y" || ans == "YES") 
      return true;
   else if (ans == "N" || ans == "NO")
      return false;
   else
      return promptTryAgain(prompt);
}