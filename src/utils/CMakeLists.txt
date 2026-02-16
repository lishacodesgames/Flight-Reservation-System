# set source variable
set(UTILS_SOURCES
   ParseUtils.cpp
   VectorUtils.cpp
)

# define library for this folder
add_library(module_utils ${UTILS_SOURCES})

# redirect to include
target_include_directories(module_utils PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
)