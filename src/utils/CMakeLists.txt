# list all .cpp sources in subdirectory into one variable
set(UTILS_SOURCES
   ParseUtils.cpp
   VectorUtils.cpp
)

# Define a library for this folder (Static library is default)
# We name it "module_<name>" to avoid conflicts with system libraries
add_library(module_utils ${UTILS_SOURCES})

# CRITICAL STEP:
   # We must tell CMake where the headers for this library live.
   # ${PROJECT_SOURCE_DIR} points to the root 'MyProject' folder.
target_include_directories(module_utils PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
)