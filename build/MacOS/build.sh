#!/bin/bash
# TESTED base X
# TESTED raylib X (not implemented yet, so no build errors, but also no graphics)

# ----------------
# DETECT LOCATION
# ----------------

# get script directory
SCRIPT_DIR="$( cd "$( dirname "${BASE_SOURCE[0]}" )" && pwd )"
# currently in Windows\, go up ..\.. to root repo
BASE="$( realpath "$SCRIPT_DIR/../.." )"

if [ ! -f "$BASE/src/main.cpp" ]; then
   echo "Error: main.cpp not found in src directory."
   exit 1
fi

# Set output executable name & location
OUT="$BASE/build/Mac/AirRouteSystem"
if [ if "$OUT" ]; then
   rm "$OUT"
fi

clear
echo "Building Air Route System"
echo "Project Directory: $BASE"
echo "Output File: $OUT"

# -----------
# QUICK MODE
# -----------

MODE="$1"
if [ "$MODE" == "quick" ]; then
   echo
   echo QUICK MODE ENABLED: skipping detailed compilation steps.
   # services storage ui and utils
   g++ -std=c++17 \
      "$BASE/src/services/"*.cpp \
      "$BASE/src/storage/"*.cpp \
      "$BASE/src/ui/"*.cpp \
      "$BASE/src/utils/"*.cpp \
      "$BASE/src/main.cpp" \
      -I"$BASE/include" \
      -o "$OUT"
   
   if [ $? -eq 0 ]; then
      clear
      echo "Build successful in quick mode!"
      exit 0
   else
      echo
      echo "Build failed in quick mode with error code $?"
      exit 1
   fi
fi

# ../src/core/*.cpp   not needed yet, as it's empty for now
# ../src/frontend/*.cpp   not needed yet, as raylib not implemented yet

# ----------
# COMPILING
# ----------

# make obj folder
OBJ_DIR="$BASE/build/Mac/obj"
if [ -d "$OBJ_DIR"]; then
   rm -rf "$OBJ_DIR"
   if [ -d "$OBJ_DIR" ]; then
      echo "failed to remove existed build\Windows\obj\ directory!"
   fi
fi
mkdir -p "$OBJ_DIR"

# temporarily make current directory = obj to contain *.o
pushd "$OBJ_DIR" > /dev/null

echo
echo "----------SERVICES----------"
for f in "$BASE/src/services"*.cpp; do
   echo "Compiling $(basename "$f")..."
done
g++ -std=c++17 -c "$BASE/src/services/"*.cpp -I"$BASE/include"
if [ $? -ne 0 ]; then
   echo "Compilation failed for services with error code $?."
   popd > /dev/null
   exit 1
fi

echo
echo "-----------STORAGE----------"
for f in "$BASE/src/storage"*.cpp; do
   echo "Compiling $(basename "$f")..."
done
g++ -std=c++17 -c "$BASE/src/storage/"*.cpp -I"$BASE/include"
if [ $? -ne 0 ]; then
   echo "Compilation failed for storage with error code $?."
   popd > /dev/null
   exit 1
fi

echo
echo "-------------UI-------------"
for f in "$BASE/src/ui"*.cpp; do
   echo "Compiling $(basename "$f")..."
done
g++ -std=c++17 -c "$BASE/src/ui/"*.cpp -I"$BASE/include"
if [ $? -ne 0 ]; then
   echo "Compilation failed for ui with error code $?."
   popd > /dev/null
   exit 1
fi

echo
echo "-----------UTILS------------"
for f in "$BASE/src/utils"*.cpp; do
   echo "Compiling $(basename "$f")..."
done
g++ -std=c++17 -c "$BASE/src/utils/"*.cpp -I"$BASE/include"
if [ $? -ne 0 ]; then
   echo "Compilation failed for utils with error code $?."
   popd > /dev/null
   exit 1
fi

# MAIN
clear
echo "Compiling MAIN"
g++ -std=c++17 -c "$BASE/src/main.cpp" -I"$BASE/include"
if [ $? -ne 0 ]; then
   echo "Compilation failed for main.cpp with error code $?"
   popd > /dev/null
   exit 1
fi

# ---------------------------------
# Creating binary and deleting *.o
# ---------------------------------
echo
echo "Linking objects files..."
g++ *.o -o "$OUT"

popd > /dev/null
rm -rf "$OBJ_DIR"

if [ $? -eq 0 ]; then
   echo
   echo "Build successful!!"
   echo
   read -n 1 -s -r -p "Tap any key to run program . . ."

    # 2 args to run program: .exe, root path for storage access
   "$OUT" "$BASE"

   read
else
   echo
   echo "Build failed with error code $?"
fi

read -n 1 -s -r -p "Press any key to continue..."
clear