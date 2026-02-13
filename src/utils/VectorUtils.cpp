#include "utils/VectorUtils.h"

int getIndex(const std::string& element, const std::vector<std::string>& vec) {
   for (int i = 0; i < vec.size(); i++) {
      if (vec[i] == element)
         return i;
   }

   return -1;
}