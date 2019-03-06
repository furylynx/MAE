cd c:\projects\MAE\libmae
cmake . -DCMAKE_TOOLCHAIN_FILE=C:\Tools\vcpkg\scripts\buildsystems\vcpkg.cmake -DMAE_STATIC=true -G "Visual Studio 15 2017 Win64"
cmake --build . --target ALL_BUILD --config Release
cd c:\projects\MAE\libmae_demo
cmake . -DCMAKE_TOOLCHAIN_FILE=C:\Tools\vcpkg\scripts\buildsystems\vcpkg.cmake -DMAE_STATIC=true -G "Visual Studio 15 2017 Win64"
cmake --build . --target ALL_BUILD --config Release
cd c:\projects\MAE\libmae_eventing
cmake . -DCMAKE_TOOLCHAIN_FILE=C:\Tools\vcpkg\scripts\buildsystems\vcpkg.cmake -DMAE_STATIC=true -G "Visual Studio 15 2017 Win64"
cmake --build . --target ALL_BUILD --config Release
