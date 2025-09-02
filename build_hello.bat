@echo off 
rmdir /s /q .\build
cmake -G "MinGW Makefiles" -B .\build
cmake --build .\build