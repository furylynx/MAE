cinst swig gradle maven jdk8 groovy
cinst cmake --installargs 'ADD_CMAKE_TO_PATH=System'
cd C:\Tools\vcpkg
git pull
.\bootstrap-vcpkg.bat
vcpkg integrate install
vcpkg install opencv libxmlpp sdl2 sdl2-image sdl2-ttf boost-core boost-asio boost-system
cd %APPVEYOR_BUILD_FOLDER%
