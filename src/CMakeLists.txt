# sub-directories
add_subdirectory(services)
add_subdirectory(storage)
add_subdirectory(ui)
add_subdirectory(utils)

# define libraries that don't have .cpp correspondance in src/
add_library(module_core INTERFACE)

# attach the include directory to it
   # Note: We use INTERFACE here, not PUBLIC. 
   # "INTERFACE" means: "I don't use this, but consumers of this lib do."
target_include_directories(module_core INTERFACE 
    "${PROJECT_SOURCE_DIR}/include"
)

# define main executable and its name
add_executable(AirRouteSystem main.cpp)

# link libraries to executable
target_link_libraries(AirRouteSystem PRIVATE
   module_core
   module_services
   module_storage
   module_ui
   module_utils
)