:: WINDOWS BATCH FILE
:: Full-line comment = preceeded by '::'
:: In-line comment = preceeded by '& REM'

:: echo. = blank line 

:: To stop the echo of each command
@echo off
setlocal EnableDelayedExpansion

cls
echo Building Air Route System

::   ../src/core/*.cpp ^ //not needed yet, as it's empty for now
::   ../src/frontend/*.cpp ^ //not needed yet, as raylib not implemented yet

:: Detect location
if exist src/main.cpp (
   echo Compiling from repo root directory.
   set "BASE=."
   set "OUT=build/AirRouteSystem.exe"
) else if exist ../src/main.cpp (
   echo Compiling from build directory.
   set "BASE=.."
   set "OUT=AirRouteSystem.exe"
) else (
   echo Error: main.cpp not found in src directory.
   pause
   exit /b 1
)
:: Detect if appended "quick" aka skip the semantics and just compile it in one go
set "MODE=%1"
if "%MODE%"=="quick" (
   echo.
   echo QUICK MODE ENABLED: skipping detailed compilation steps.
   g++ -std=c++17 %BASE%\src\services\*.cpp %BASE%\src\storage\*.cpp %BASE%\src\ui\*.cpp %BASE%\src\utils\*.cpp %BASE%\src\main.cpp -I%BASE%\include -o %OUT%
   if %ERRORLEVEL% equ 0 (
      cls
      echo Build successful in quick mode!
   ) else (
      echo.
      echo Build failed in quick mode with error code %ERRORLEVEL%.
   )
   pause
   exit /b 0
)

timeout /t 1 >nul

:: Compile

:: services
echo.
echo Compiling SERVICES
for %%f in (%BASE%\src\services\*.cpp) do (
   echo Compiling %%~nxf ...
)
g++ -std=c++17 -c %BASE%\src\services\*.cpp -I%BASE%\include
if %ERRORLEVEL% neq 0 (
   echo Compilation failed for services with error code %ERRORLEVEL%.
   pause
   exit /b 1
)

:: storage
echo.
echo Compiling STORAGE
for %%f in (%BASE%\src\storage\*.cpp) do (
   echo Compiling %%~nxf ...
)
g++ -std=c++17 -c %BASE%\src\storage\*.cpp -I%BASE%\include
if %ERRORLEVEL% neq 0 (
   echo Compilation failed for storage with error code %ERRORLEVEL%.
   pause
   exit /b 1
)

:: ui
echo.
echo Compiling UI
for %%f in (%BASE%\src\ui\*.cpp) do (
   echo Compiling %%~nxf ...
)
g++ -std=c++17 -c %BASE%\src\ui\*.cpp -I%BASE%\include
if %ERRORLEVEL% neq 0 (
   echo Compilation failed for ui with error code %ERRORLEVEL%.
   pause
   exit /b 1
)

:: utils
echo.
echo Compiling UTILS
for %%f in (%BASE%\src\utils\*.cpp) do (
   echo Compiling %%~nxf ...
)
g++ -std=c++17 -c %BASE%\src\utils\*.cpp -I%BASE%\include
if %ERRORLEVEL% neq 0 (
   echo Compilation failed for utils with error code %ERRORLEVEL%.
   pause
   exit /b 1
)

:: MAIN.CPP
cls
echo Compiling MAIN
g++ -std=c++17 -c %BASE%\src\main.cpp -I%BASE%\include
if %ERRORLEVEL% neq 0 (
   echo Compilation failed for main.cpp with error code %ERRORLEVEL%.
   pause
   exit /b 1
)

:: Creating .exe and deleting *.o
echo.
echo Linking object files ...
g++ *.o -o %OUT%

if %ERRORLEVEL% equ 0 (
   :: Redirect stdout >nul and stderr 2>nul to suppress unwanted echos
   del *.o >nul 2>nul
   cls
   echo Build successful!
) else (
   echo.
   echo Build failed with error code %ERRORLEVEL%.
)

pause
cls