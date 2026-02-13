#include "ui/Menu.h"
#include "utils/ParseUtils.h"
#include <iostream>

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

int MainMenu() {
   std::string input;
   int choice = -1;
   bool invalidChoice;
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

      // error1: input not a number
      choice = parseInt(input);
      if (choice == -100 || choice == 100) {
         printTitle();
         std::cout << (choice == -100 ? "\nPlease enter a number.\n" : "\nWhy would you do that?\n");
         invalidChoice = true;
         continue;
      }

      //error2: incorrect number
      invalidChoice = (choice < 0 || choice > 4);
      if (invalidChoice) {
         printTitle();
         std::cout << "\nInvalid choice.\n";
      }
   } while (invalidChoice);

   return choice;
}

std::string getIDforShow() {
   std::string id;
   printTitle();
   std::cout << "Enter flight ID: ";
   getline(std::cin, id);

   return id;
}

/// @attention starts with \\n
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

/// @param prompt (must end with \\n) What the user will be shown before asking (y\n)?
bool promptTryAgain(std::string prompt) {
   std::string ans;
   std::cout << prompt << "Try again? (y/n) ";
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