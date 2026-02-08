#include <iostream>

void printTitle() {
   #if defined(_WIN32)
      system("cls");
   #elif defined(__APPLE__)
      std::cout << "\033c";
   #endif

   std::cout << "===============================\n";
   std::cout << "  WELCOME TO LISHA'S AIRPORT!  \n";
   std::cout << "===============================\n\n";
}