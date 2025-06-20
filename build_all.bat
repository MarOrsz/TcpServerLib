@echo off
cmake --preset debug
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
cmake --build --preset build-debug
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
cmake --preset release
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
cmake --build --preset build-release
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
echo Build completed successfully!
cmake --preset debug
cmake --install build --config debug
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
cmake --preset release
cmake --install build --config release
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
echo Library installation completed successfully!