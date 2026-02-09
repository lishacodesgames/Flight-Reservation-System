:: WINDOWS BATCH FILE
:: Full-line comment = preceeded by '::'
:: In-line comment = preceeded by '& REM'

:: STILL NOT WORKING BCZ OF THE * !!!!

@echo off & REM To stop the echo of each command
echo Building Air Route System ...
:: add sleep for 300ms and 1 more echo

g++ -std=c++17 ^
   ../src/main.cpp ^
   ../src/core/*.cpp ^
   ../src/services/*.cpp ^
   ../src/storage/*.cpp ^
   ../src/ui/*.cpp ^
   ../src/utils/*.cpp ^
   -I../include ^
   -o AirRouteSystem.exe

if %ERRORLEVEL% equ 0 (
   echo Build successful!
   pause
) else (
   echo Build failed with error code %ERRORLEVEL%.
)