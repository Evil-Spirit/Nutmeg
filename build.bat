@echo off
setlocal EnableDelayedExpansion

set BUILD_DIR=build
set BUILD_TYPE=Release

:: ------------------------------------------------------------
:: 1. Check Conan is installed
:: ------------------------------------------------------------
where conan >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Conan is not installed.
    echo        Install it with:  pip install "conan>=2.1"
    exit /b 1
)

for /f "tokens=*" %%v in ('conan --version 2^>nul') do echo Found %%v

:: ------------------------------------------------------------
:: 2. Ensure a default Conan profile exists
:: ------------------------------------------------------------
conan profile list 2>nul | findstr /c:"default" >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo Creating default Conan profile...
    conan profile detect
    if %ERRORLEVEL% NEQ 0 exit /b 1
)

:: ------------------------------------------------------------
:: 3. Ensure ConanCenter remote is configured
:: ------------------------------------------------------------
conan remote list 2>nul | findstr /b /c:"conancenter " >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo Adding ConanCenter remote...
    conan remote add conancenter --force https://center2.conan.io
)

:: ------------------------------------------------------------
:: 4. Install dependencies via Conan
:: ------------------------------------------------------------
echo.
echo Installing dependencies via Conan...
conan install . --build=missing --output-folder=%BUILD_DIR% -s build_type=%BUILD_TYPE%
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: conan install failed.
    exit /b 1
)

:: ------------------------------------------------------------
:: 5. Configure CMake
:: ------------------------------------------------------------
echo.
echo Configuring CMake...
cmake -B %BUILD_DIR% ^
    -DCMAKE_TOOLCHAIN_FILE=%BUILD_DIR%\conan_toolchain.cmake ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake configuration failed.
    exit /b 1
)

:: ------------------------------------------------------------
:: 6. Build
:: ------------------------------------------------------------
echo.
echo Building...
cmake --build %BUILD_DIR% --config %BUILD_TYPE%
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed.
    exit /b 1
)

echo.
echo Build completed successfully.
echo Outputs are in %BUILD_DIR%\
