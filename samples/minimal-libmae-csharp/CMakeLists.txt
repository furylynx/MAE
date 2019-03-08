cmake_minimum_required(VERSION 3.10)

# Set package infos
set(MYEXEC minimal-libmae-csharp)

project(${MYEXEC} CSharp)

FILE(GLOB SOURCE_FILES src/main/csharp/minimallibmaecsharp/MinimalLibmaeCsharp.cs)

ADD_EXECUTABLE(${MYEXEC} ${SOURCE_FILES})

set_property(TARGET ${MYEXEC} PROPERTY WIN32_EXECUTABLE FALSE)

set_property(TARGET ${MYEXEC} PROPERTY VS_DOTNET_REFERENCES
        	"System"
            )

find_package(mae CONFIG HINTS "$ENV{MAE_HOME}")

set_target_properties(${MYEXEC} PROPERTIES
    VS_DOTNET_REFERENCE_maecsharplib "${MAE_INSTALL_PREFIX}/bin/maecsharplib.dll")
