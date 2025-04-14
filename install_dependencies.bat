@echo off
echo Installing dependencies for LLMK on Windows...

:: Check if Chocolatey is installed by attempting to run it.
choco -v >nul 2>&1
if errorlevel 1 (
    echo Chocolatey not found. Installing Chocolatey...
    @powershell -NoProfile -ExecutionPolicy Bypass -Command ^
      "Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"
    
    echo Chocolatey installation complete. Refreshing environment variables...
    if exist "%ProgramData%\chocolatey\bin\refreshenv.cmd" (
        call "%ProgramData%\chocolatey\bin\refreshenv.cmd"
    ) else (
        echo refreshenv.cmd not found. Please close and reopen your shell before proceeding.
    )
)

:: Install ARM GCC toolchain
choco install -y gcc-arm-embedded

:: Install CMake
choco install -y cmake

:: Install optional tools for flashing (if user wants them)
echo Do you want to install STM32CubeProgrammer? (Y/N)
set /p install_programmer=
if /i "%install_programmer%"=="Y" (
    echo Please download and install STM32CubeProgrammer from:
    echo https://www.st.com/en/development-tools/stm32cubeprog.html
    echo This requires a free ST account.
)

echo Dependencies installed successfully.
pause

