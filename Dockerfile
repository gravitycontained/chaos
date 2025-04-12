# Use the official Microsoft Windows Server Core image as the base
FROM mcr.microsoft.com/windows/servercore:ltsc2019

# Set shell to PowerShell
SHELL ["powershell", "-Command", "$ErrorActionPreference = 'Stop'; $ProgressPreference = 'SilentlyContinue';"]

# Install Visual Studio Build Tools
RUN Invoke-WebRequest -Uri 'https://aka.ms/vs/17/release/vs_buildtools.exe' -OutFile 'vs_buildtools.exe' ; \
    Start-Process -FilePath 'vs_buildtools.exe' -ArgumentList '--quiet', '--wait', '--norestart', '--nocache', \
    '--installPath', 'C:\BuildTools', \
    '--add', 'Microsoft.VisualStudio.Workload.VCTools', \
    '--add', 'Microsoft.VisualStudio.Component.Windows10SDK.19041', \
    '--add', 'Microsoft.VisualStudio.Component.VC.Tools.x86.x64', \
    '--includeRecommended' \
    -NoNewWindow -Wait -PassThru | Out-String ; \
    if (Test-Path 'vs_buildtools.exe') { Remove-Item -Force 'vs_buildtools.exe' } \
    if (-not (Test-Path 'C:\BuildTools\MSBuild\Current\Bin\MSBuild.exe')) { throw 'Visual Studio Build Tools installation failed' }
	
	
# Install Git
RUN Invoke-WebRequest -Uri 'https://github.com/git-for-windows/git/releases/download/v2.43.0.windows.1/PortableGit-2.43.0-32-bit.7z.exe' -OutFile 'git.exe' ; \
    Start-Process -FilePath 'git.exe' -ArgumentList '-y', '-gm2', '-nr', '-o"C:\Git"' -NoNewWindow -Wait ; \
    Remove-Item -Force 'git.exe'

# Add Git to the system PATH
RUN $env:PATH = 'C:\Git\cmd;' + $env:PATH ; \
    [Environment]::SetEnvironmentVariable('PATH', $env:PATH, [EnvironmentVariableTarget]::Machine)


# Download and setup vcpkg directly
RUN [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12 ; \
    Invoke-WebRequest -Uri 'https://github.com/microsoft/vcpkg/archive/refs/heads/master.zip' -OutFile 'vcpkg.zip' ; \
    Expand-Archive -Path 'vcpkg.zip' -DestinationPath 'C:\' ; \
    Rename-Item -Path 'C:\vcpkg-master' -NewName 'vcpkg' ; \
    Remove-Item -Force 'vcpkg.zip' ; \
    cmd /C C:\vcpkg\bootstrap-vcpkg.bat

# Add vcpkg to system PATH
RUN $env:PATH = 'C:\vcpkg;' + $env:PATH ; \
    [Environment]::SetEnvironmentVariable('PATH', $env:PATH, [EnvironmentVariableTarget]::Machine)
	
ENV VCPKG_DEFAULT_TRIPLET=x64-windows-static
	
# Install all required packages using vcpkg
RUN vcpkg install brotli:x64-windows-static bzip2:x64-windows-static freetype:x64-windows-static sfml:x64-windows-static stb:x64-windows-static glew:x64-windows-static gmp:x64-windows-static libflac:x64-windows-static libpng:x64-windows-static libogg:x64-windows-static nlohmann-json:x64-windows-static zlib:x64-windows-static curl:x64-windows-static termcolor:x64-windows-static

# Integrate vcpkg with MSBuild
RUN vcpkg integrate install

# Create project directory
WORKDIR "C:\\project"

# Copy the rest of your project files
COPY . .

# Build the project using MSBuild

RUN & "C:\BuildTools\MSBuild\Current\Bin\MSBuild.exe" QL.vcxproj /property:Configuration=Release /property:Platform=x64

CMD ["cmd", "/K"]
