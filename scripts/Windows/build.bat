@echo off
REM ====================================================
REM Build script for LLMK (run from LLMK/scripts/Windows)
REM This script switches to the project root (two directories up),
REM removes any existing build folder, creates a new one,
REM configures CMake with the Ninja generator and the ARM toolchain,
REM and then builds the project.
REM ====================================================

REM Switch to the project root (assumed to be two levels up from this script).
pushd "%~dp0..\.."
set PROJECT_ROOT=%CD%
echo Project root is: %PROJECT_ROOT%

REM Remove the existing build folder if it exists.
IF EXIST build (
    echo Removing existing build folder...
    rmdir /s /q build
)

REM Create a new build folder.
echo Creating build folder...
mkdir build
cd build

REM Configure the project with CMake.
REM The source directory is the project root.
REM Use the Ninja generator for a clean cross-compilation environment.
echo Configuring project with CMake...
cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE="%PROJECT_ROOT%\arm-gcc-toolchain.cmake" "%PROJECT_ROOT%"

IF %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed.
    pause
    popd
    exit /b %ERRORLEVEL%
)

REM Build the project.
echo Building project...
cmake --build .

IF %ERRORLEVEL% NEQ 0 (
    echo Build failed.
    pause
    popd
    exit /b %ERRORLEVEL%
)

echo Build succeeded.
pause
popd
