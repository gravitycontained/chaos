@echo off
msbuild.exe QL.vcxproj /property:Configuration=Release /property:Platform=x64

if %ERRORLEVEL% EQU 0 (
	echo [90mbuild succeeded, running...
	echo [97m
	
	.\x64\Release\QL.exe
) else (
	echo [91mBuild failed!
	echo:
)
