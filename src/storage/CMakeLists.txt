# set source variable
set(STORAGE_SOURCES
   FlightStorage.cpp
   PassengerStorage.cpp
)

# define library for this folder
add_library(module_storage ${STORAGE_SOURCES})

# redirect to include
target_include_directories(module_storage PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
)