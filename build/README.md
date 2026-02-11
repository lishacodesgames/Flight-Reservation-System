# How to Build ?
## Windows
Run the build.bat file
<br>
Can run only from repo or from build directory

#### 2 ways to run batch file:
<ol>
   <li> Normal Mode: Will show the files compiling as they compile </li>
   <li> Quick Mode: append " quick" to normal run command to enable quick mode, will skip the outputs and directly compile into AirRouteSystem.exe </li>
</ol>

**Both work just fine. Depends on your patience / trust in your compiler**

#### Skip the Batch file and directly run:
`g++ -std=c++17 ..\src\services\*.cpp ..\src\storage\*.cpp ..\src\ui\*.cpp ..\src\utils\*.cpp ..\src\main.cpp -I..\include -o AirRouteSystem.exe`
<br>
(From build directory)
<br> OR <br>

`g++ -std=c++17 src\services\*.cpp src\storage\*.cpp src\ui\*.cpp src\utils\*.cpp src\main.cpp -Iinclude -o AirRouteSystem.exe`
<br>
(From repo root directory)