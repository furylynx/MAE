cd %APPVEYOR_BUILD_FOLDER%\libmae
cmake . -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=%MPREFIX%
make
make install


cd %APPVEYOR_BUILD_FOLDER%\libmae_demo
cmake . -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=%MPREFIX%
make
make install


cd %APPVEYOR_BUILD_FOLDER%\libmae_eventing
cmake . -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=%MPREFIX%
make
make install
