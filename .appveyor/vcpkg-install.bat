cinst swig gradle maven jdk8 groovy
cinst cmake --installargs 'ADD_CMAKE_TO_PATH=System'

cd C:\tools\vcpkg
git pull

ECHO vcpkg bootstrapping...
.\bootstrap-vcpkg.bat
ECHO vcpkg bootstrapped

.\vcpkg integrate install
ECHO vcpkg integrated

.\vcpkg install opencv libxmlpp sdl2 sdl2-image sdl2-ttf boost-core boost-asio boost-system
ECHO Deps installed

cd %APPVEYOR_BUILD_FOLDER%
