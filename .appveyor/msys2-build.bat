cd %APPVEYOR_BUILD_FOLDER%

cd libmae\
cmake . -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=%MPREFIX%
make
make install


cd libmae_demo\
cmake . -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=%MPREFIX%
make
make install


cd libmae_eventing\
cmake . -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=%MPREFIX%
make
make install
