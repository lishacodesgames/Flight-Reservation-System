:: WINDOWS BATCH FILE
:: Full-line comment = preceeded by '::'
:: In-line comment = preceeded by '& REM'

:: STILL NOT WORKING BCZ OF THE * !!!!

@echo off & REM To stop the echo of each command

cls
echo Building Air Route System ...
:: add sleep for 300ms and 1 more echo
::   ../src/core/*.cpp ^ //since not needed yet

g++ -std=c++17 ^
   ../src/main.cpp ^
   ../src/services/*.cpp ^
   ../src/storage/*.cpp ^
   ../src/ui/*.cpp ^
   ../src/utils/*.cpp ^
   -I../include ^
   -o AirRouteSystem.exe

if %ERRORLEVEL% equ 0 (
   echo Build successful!
) else (
   echo Build failed with error code %ERRORLEVEL%.
)

pause
cls