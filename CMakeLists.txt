cmake_minimum_required(VERSION 3.1)

project(OpenGMP)

# Compiler setup
set(CMAKE_CXX_STANDARD 14)

if (CMAKE_COMPILER_IS_GNUCC)
    # add warning flags
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -Wall -Wextra")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-type") # missing return is error

    # Fix up C++ standard
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0)
        message(WARNING "Compilation wasn't tested on GCC versions prior to 6.x and might not be successful!")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
    endif()
endif()

if(MINGW)
    set(COMPILER_PREFIX "i686-mingw32")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /MP /bigobj")
    set(USE_MSVC_RUNTIME_LIBRARY_DLL ON)
    add_definitions(-DNOMINMAX)
endif()

# ---------------- Doxygen documentation ------------

find_package(Doxygen)

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ALL
        ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
endif(DOXYGEN_FOUND)

# ---------------------------------------------------

#Set library output dir
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Add library includes directories:
include_directories(lib/RakNet/Source)
include_directories(lib/RakNet/DependentExtensions)
include_directories(lib/ZenLib)
include_directories(lib/lua/src)
include_directories(lib/lua/etc)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/lib/lua) #luaconf.h generated from lua cmake file.
include_directories(lib/cpgf/include)
include_directories(lib/json)
include_directories(lib/tinydir)
include_directories(src)

add_subdirectory(lib/RakNet)
add_subdirectory(lib/ZenLib)
add_subdirectory(lib/lua)

if(UNIX)
	add_subdirectory(lib/python-cmake-buildsystem)
	include_directories(${CMAKE_CURRENT_BINARY_DIR}/lib/python-cmake-buildsystem/bin) # generated from python cmake file.
	include_directories(${CMAKE_CURRENT_BINARY_DIR}/lib/Python-2.7.6/Include)
else()
	find_package(PythonLibs 2.7 EXACT REQUIRED)
endif()
add_subdirectory(lib/cpgf)

#Server
file(GLOB serverSources
    "src/Server/*.cpp"
    "src/Server/*.hpp"
    "src/Server/ScriptController/*.cpp"
    "src/Server/ScriptController/*.hpp"
    "src/Server/Utils/*.cpp"
    "src/Server/Utils/*.hpp"
    "src/Server/Utils/*.h"
    "src/Server/Objects/*.cpp"
    "src/Server/Objects/*.hpp"
    "src/Server/Systems/*.cpp"
    "src/Server/Systems/*.hpp"
    "src/Shared/*.cpp"
    "src/Shared/*.hpp"
    "src/Shared/Components/*.cpp"
    "src/Shared/Components/*.hpp"
    "src/Shared/Objects/*.cpp"
    "src/Shared/Objects/*.hpp"
    "src/Shared/Systems/*.cpp"
    "src/Shared/Systems/*.hpp"
    "src/Shared/GameObjects/*.cpp"
    "src/Shared/GameObjects/*.hpp"
    "src/Shared/Types/*.cpp"
    "src/Shared/Types/*.hpp"
    "src/Shared/Types/Messages/*.cpp"
    "src/Shared/Types/Messages/*.hpp"
)

# Build commands server
message("Will build server.")
add_executable(OpenGMP-Server ${serverSources})
target_link_libraries(OpenGMP-Server RakNetLibStatic liblua libpython-shared libCpgf utils mysqlclient)

# Copy generated python library before linkage.
if(UNIX)
	set(PYTHON_OUT_SHARED_LIB ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib/python-cmake-buildsystem/lib/libpython2.7.so)
else()
	set(PYTHON_OUT_SHARED_LIB ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib/python-cmake-buildsystem/lib/python2.7.dll)
endif()
add_custom_command(TARGET OpenGMP-Server
		   PRE_LINK
		   COMMAND ${CMAKE_COMMAND} -E copy ${PYTHON_OUT_SHARED_LIB} ${CMAKE_CURRENT_BINARY_DIR})

# Copy support scripts:
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib/BashSupportScripts/binFileToAsciHexInitList.sh
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Build commands client (Windows only)
if(MSVC)
  message("Will build client.")
else()
  message("Client on Gothic2 base cannot be built on Linux systems. Sorry. msvc compiler required.")
endif()
