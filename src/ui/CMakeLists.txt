# list all .cpp sources in subdirectory into one variable
set(UI_SOURCES
   BookingUI.cpp
   FlightUI.cpp
   MenuUI.cpp
   PassengerUI.cpp
)

# Define a library for this folder (Static library is default)
# We name it "module_<name>" to avoid conflicts with system libraries
add_library(module_ui ${UI_SOURCES})

# CRITICAL STEP:
   # We must tell CMake where the headers for this library live.
   # ${PROJECT_SOURCE_DIR} points to the root 'MyProject' folder.
target_include_directories(module_ui PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
)