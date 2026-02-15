#!/bin/bash

clear
echo "Building Air Route System"
echo 

# Detect location
if [ -f "src/main.cpp" ]; then # root directory
   echo "Compiling from repo root directory."
   BASE="."
   OUT="build/Mac/AirRouteSystem"
elif [ -f "../src/main.cpp" ]; then
   echo "Compiling from build directory."
   BASE=".."
   OUT="Mac/AirRouteSystem"
elif [ -f "../../src/main.cpp" ]; then
   echo "Compiling from build/Mac directory."
   BASE="../.."
   OUT="AirRouteSystem"
else
   echo "Error: main.cpp not found in src directory."
   read -n 1 -s -r -p "Press any key to continue..."
   exit 1
fi

# Detect if appended "quick" aka skip the semantics and just compile it in one go
MODE="$1"
if [ "$MODE" == "quick" ]; then
   echo
   echo QUICK MODE ENABLED: skipping detailed compilation steps.
   # services storage ui and utils
   g++ -std=c++17 \
      "$BASE/src/main.cpp" \
      "$BASE/src/services/"*.cpp \
      "$BASE/src/storage/"*.cpp \
      "$BASE/src/ui/"*.cpp \
      "$BASE/src/utils/"*.cpp \
      -I"$BASE/include" \
      -o "$OUT"
   
   if [ $? -eq 0 ]; then
      clear
      echo "Build successful in quick mode!"
   else
      echo
      echo "Build failed in quick mode with error code $?"
   fi
   read -n 1 -s -r -p "Press any key to continue..."
   exit 1
fi

# Compile
mkdir -p "$BASE/build/Mac/obj"

#services
echo
echo "Compiling SERVICES"
for f in "$BASE/src/services/"*.cpp; do
   echo "Compiling $(basename "$f")..."
done
g++ -std=c++17 -c "$BASE/src/services/"*.cpp -I"$BASE/include" -o "$BASE/build/Mac/obj/services.o"
if [ $? -ne 0 ]; then
   echo "Compilation failed for services with error code $?"
   read -n 1 -s -r -p "Press any key to continue..."
   exit 1
fi

#storage
echo
echo "Compiling STORAGE"
for f in "$BASE/src/storage/"*.cpp; do
   echo "Compiling $(basename "$f")..."
done
g++ -std=c++17 -c "$BASE/src/storage/"*.cpp -I"$BASE/include" -o "$BASE/build/Mac/obj/storage.o"
if [ $? -ne 0 ]; then
   echo "Compilation failed for storage with error code $?"
   read -n 1 -s -r -p "Press any key to continue..."
   exit 1
fi

#ui
echo
echo "Compiling UI"
for f in "$BASE/src/ui/"*.cpp; do
   echo "Compiling $(basename "$f")..."
done
g++ -std=c++17 -c "$BASE/src/ui/"*.cpp -I"$BASE/include" -o "$BASE/build/Mac/obj/ui.o"
if [ $? -ne 0 ]; then
   echo "Compilation failed for ui with error code $?"
   read -n 1 -s -r -p "Press any key to continue..."
   exit 1
fi

#utils
echo
echo "Compiling UTILS"
for f in "$BASE/src/utils/"*.cpp; do
   echo "Compiling $(basename "$f")..."
done
g++ -std=c++17 -c "$BASE/src/utils/"*.cpp -I"$BASE/include" -o "$BASE/build/Mac/obj/utils.o"
if [ $? -ne 0 ]; then
   echo "Compilation failed for utils with error code $?"
   read -n 1 -s -r -p "Press any key to continue..."
   exit 1
fi

#MAIN
clear
echo "Compiling MAIN"
g++ -std=c++17 -c "$BASE/src/main.cpp" -I"$BASE/include" -o "$BASE/build/Mac/obj/main.o"
if [ $? -ne 0 ]; then
   echo "Compilation failed for main.cpp with error code $?"
   read -n 1 -s -r -p "Press any key to continue..."
   exit 1
fi

# Link
echo
echo "Linking objects into executable..."
g++ -std=c++17 "$BASE/build/Mac/obj/"*.o -o "$OUT"

if [ $? -eq 0 ]; then
   rm -f "$BASE/build/Mac/obj/"*.o
   clear
   echo "Build successful!"
else
   echo
   echo "Build failed with error code $?"
fi

read -n 1 -s -r -p "Press any key to continue..."
clear