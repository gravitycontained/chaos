@echo off
msbuild.exe Uzumaki.vcxproj /property:Configuration=Release /property:Platform=x64

if %ERRORLEVEL% EQU 0 (
	echo [90mbuild succeeded, running...
	echo [97m
	
	xcopy /s /y .\x64\Release\Uzumaki.exe .\Uzumaki.exe
	.\Uzumaki.exe
) else (
	echo [91mBuild failed!
	echo:
	pause
)
