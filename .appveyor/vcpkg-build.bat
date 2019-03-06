cd %APPVEYOR_BUILD_FOLDER%\libmae
cmake . -DCMAKE_TOOLCHAIN_FILE=C:\Tools\vcpkg\scripts\buildsystems\vcpkg.cmake -DMAE_STATIC=true -G %CMAKE_GENERATOR%
cmake --build . --target ALL_BUILD --config Release

cd %APPVEYOR_BUILD_FOLDER%\libmae_demo
cmake . -DCMAKE_TOOLCHAIN_FILE=C:\Tools\vcpkg\scripts\buildsystems\vcpkg.cmake -DMAE_STATIC=true -G %CMAKE_GENERATOR%
cmake --build . --target ALL_BUILD --config Release

cd %APPVEYOR_BUILD_FOLDER%\libmae_eventing
cmake . -DCMAKE_TOOLCHAIN_FILE=C:\Tools\vcpkg\scripts\buildsystems\vcpkg.cmake -DMAE_STATIC=true -G %CMAKE_GENERATOR%
cmake --build . --target ALL_BUILD --config Release

cd %APPVEYOR_BUILD_FOLDER%
