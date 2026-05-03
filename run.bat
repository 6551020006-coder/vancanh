@echo off
title Build & Run Game
echo ========================================
echo   Dang build game...
echo ========================================

set RAYLIB=%USERPROFILE%\Downloads\raylib-5.0\raylib-5.0_win64_mingw-w64
set GPP=C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64\bin\g++.exe

"%GPP%" src/main.cpp src/game1.cpp src/spaceship.cpp src/laser.cpp src/boss.cpp src/powerup.cpp src/audio.cpp ^
    -o game1.exe ^
    -I"%RAYLIB%\include" ^
    -L"%RAYLIB%\lib" ^
    -lraylib -lopengl32 -lgdi32 -lwinmm ^
    -std=c++14

if %ERRORLEVEL% == 0 (
    echo [OK] Build thanh cong! Dang khoi dong game...
    echo ========================================
    start "" game1.exe
) else (
    echo.
    echo [LOI] Build that bai! Kiem tra code.
    pause
)
