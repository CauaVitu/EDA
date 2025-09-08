@echo off
title The Epic Battle Between Batch and MSYS2
color 0A
echo.
echo ╔══════════════════════════════════════════════════════════════╗
echo ║                    🚀 COMPILATION WIZARD 🚀                  ║
echo ╚══════════════════════════════════════════════════════════════╝
echo.
if "%1"=="" (
    echo Usage: build_and_run.bat [structure_type] [filename]
    echo Structure types: 1=AVLTREE, 2=RBTREE, 3=OPENHASH, 4=CHAINEDHASH
    echo Example: build_and_run.bat AVLTREE test.txt
    echo Running without arguments will show usage message...
) else if "%2"=="" (
    echo Usage: build_and_run.bat [structure_type] [filename]
    echo Structure type provided: %1
    echo Missing filename! Example: build_and_run.bat %1 test.txt
    echo Running with structure type only to show usage...
) else (
    echo Building and running with structure type: %1 and file: %2
)
echo.
echo [PHASE 1] Summoning the MSYS2 spirits...
timeout /t 1 /nobreak >nul

REM Let's try the nuclear option - direct MinGW call
set PATH=C:\msys64\mingw64\bin;%PATH%
echo [PHASE 2] Invoking g++ directly from the shadow realm...
g++.exe -Wall main.cpp -o freq $(pkg-config --cflags --libs icu-uc icu-i18n)

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✅ SUCCESS! The compilation gods smile upon us!
    echo.
    echo [PHASE 3] Executing the magical executable...
    echo ════════════════════════════════════════════════════════════
    if "%1"=="" (
        echo No arguments provided. Running with default usage message...
        main.exe
    ) else if "%2"=="" (
        echo Only structure type provided. Running to show usage...
        main.exe %1
    ) else (
        main.exe %1 %2
    )
    echo ════════════════════════════════════════════════════════════
    echo.
    echo 🎉 Mission accomplished! Your code has been successfully executed!
) else (
    echo.
    echo ❌ FAILURE! The compilation demons have won this round...
    echo Error code: %ERRORLEVEL%
    echo.
    echo Let's try a different incantation...
    echo [BACKUP PLAN] Using the ancient PowerShell scrolls...
    if "%1"=="" (
        powershell -Command "$currentDir = (Get-Location).Path -replace '\\\\', '/' -replace 'C:', '/c'; & 'C:\msys64\msys2_shell.cmd' -mingw64 -c \"cd '$currentDir' && g++ -std=c++17 main.cpp -o main.exe -licuuc\"; if (Test-Path 'main.exe') { Write-Host 'Backup plan successful!' -ForegroundColor Green; .\main.exe } else { Write-Host 'Even the backup plan failed!' -ForegroundColor Red }"
    ) else if "%2"=="" (
        powershell -Command "$currentDir = (Get-Location).Path -replace '\\\\', '/' -replace 'C:', '/c'; & 'C:\msys64\msys2_shell.cmd' -mingw64 -c \"cd '$currentDir' && g++ -std=c++17 main.cpp -o main.exe -licuuc\"; if (Test-Path 'main.exe') { Write-Host 'Backup plan successful with %1!' -ForegroundColor Green; .\main.exe %1 } else { Write-Host 'Even the backup plan failed!' -ForegroundColor Red }"
    ) else (
        powershell -Command "$currentDir = (Get-Location).Path -replace '\\\\', '/' -replace 'C:', '/c'; & 'C:\msys64\msys2_shell.cmd' -mingw64 -c \"cd '$currentDir' && g++ -std=c++17 main.cpp -o main.exe -licuuc\"; if (Test-Path 'main.exe') { Write-Host 'Backup plan successful with %1 and %2!' -ForegroundColor Green; .\main.exe %1 %2 } else { Write-Host 'Even the backup plan failed!' -ForegroundColor Red }"
    )
)

echo.
echo Press any key to return to the mortal realm...
pause >nul
