@echo off
set /p vcpkgPath="Enter path of vcpkg packages (<enter> to default) : "

IF "%vcpkgPath%"=="" (
	set "vcpkgPath=C:\dev\packages\vcpkg\installed"
)

@echo on
vcpkg install --triplet x64-windows-static --x-install-root="%vcpkgPath%"

pause