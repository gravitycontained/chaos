@echo off
for /r %%f in (*.cpp *.hpp) do (
	echo %%f
	clang-format.exe -i %%f
)