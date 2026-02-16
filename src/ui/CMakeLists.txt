# set source variable
set(UI_SOURCES
   BookingView.cpp
   FlightView.cpp
   Menu.cpp
   PassengerView.cpp
)

# define library for this folder
add_library(module_ui ${UI_SOURCES})

# redirect to include
target_include_directories(module_ui PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
)