@echo off
setlocal enabledelayedexpansion

REM Get the source file path (full path)
set SOURCE_FILE=%1
set SOURCE_FILE=%SOURCE_FILE:"=%

REM Extract directory, filename and extension
set SOURCE_DIR=%~dp1
set SOURCE_DIR=%SOURCE_DIR:~0,-1%
set FILENAME=%~n1
set EXTENSION=%~x1

echo ========================================
echo Building: %FILENAME%%EXTENSION%
echo Location: %SOURCE_DIR%
echo ========================================
echo.

REM Change to source directory
cd /d "%SOURCE_DIR%"

REM Set Visual Studio environment
echo Setting up Visual Studio 2022 environment...
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul 2>&1

if %errorlevel% neq 0 (
    echo [ERROR] Failed to setup Visual Studio environment!
    echo.
    pause
    exit /b 1
)

echo Environment setup successful.
echo.

REM Compile and link with MPI
echo Compiling...
cl /I "C:\Program Files (x86)\Microsoft SDKs\MPI\Include" "%SOURCE_FILE%" /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib /Fe:"%SOURCE_DIR%\%FILENAME%.exe"

if %errorlevel% equ 0 (
    echo.
    echo ========================================
    echo [SUCCESS] Build completed successfully!
    echo Executable: %SOURCE_DIR%\%FILENAME%.exe
    echo Object file: %SOURCE_DIR%\%FILENAME%.obj
    echo ========================================
) else (
    echo.
    echo ========================================
    echo [ERROR] Build failed with error code: %errorlevel%
    echo ========================================
)

echo.
pause