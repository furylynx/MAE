cinst swig gradle maven jdk8 groovy msys2
cinst cmake --installargs 'ADD_CMAKE_TO_PATH=System'

rem get-content C:\Tools\msys64\msys2.ini | %{$_ -replace "#MSYS2_PATH_TYPE","MSYS2_PATH_TYPE"}
rem get-content C:\Tools\msys64\mingw64.ini | %{$_ -replace "#MSYS2_PATH_TYPE","MSYS2_PATH_TYPE"}

PATH C:\msys64\%MSYSTEM%\bin;C:\msys64\usr\bin;%PATH%

rem Upgrade the MSYS2 platform
bash -lc "pacman --noconfirm --sync --refresh --refresh pacman"
bash -lc "pacman --noconfirm --sync --refresh --refresh --sysupgrade --sysupgrade"

rem Install required tools
bash -xlc "pacman --noconfirm -S --needed make ming-w64-%MSYS2_ARCH%-cmake ming-w64-%MSYS2_ARCH%-toolchain swig gradle"

rem Install the relevant native dependencies
bash -xlc "pacman --noconfirm -S --needed mingw-w64-%MSYS2_ARCH%-libxml++2.6 mingw-w64-%MSYS2_ARCH%-opencv mingw-w64-%MSYS2_ARCH%-boost mingw-w64-%MSYS2_ARCH%-SDL2 mingw-w64-%MSYS2_ARCH%-SDL2_image mingw-w64-%MSYS2_ARCH%-SDL2_ttf"

rem Invoke subsequent bash in the build tree
cd %APPVEYOR_BUILD_FOLDER%
set CHERE_INVOKING=yes
