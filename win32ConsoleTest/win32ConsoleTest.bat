set BAT_PATH=%~dp0

set GLEW_DLL_PATH=%BAT_PATH%\..\..\env\glew-1.12.0-win32\glew-1.12.0\bin\Release\Win32
set GLUT_DLL_PATH=%BAT_PATH%\..\..\env\freeglut-3.0.0\build\bin\Debug

set PATH=%PATH%;%GLEW_DLL_PATH%;%GLUT_DLL_PATH%
echo %PATH%

call .\win32ConsoleTest.sln
