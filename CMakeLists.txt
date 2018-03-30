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
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /MP /bigobj")
    add_definitions(-DNOMINMAX)
endif()

if(MSVC)
    set(USE_MSVC_RUNTIME_LIBRARY_DLL ON)
endif()

#Set library output dir
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Add used libraries to project
add_subdirectory(lib/RakNet)
include_directories(lib/RakNet/Source)
add_subdirectory(lib/ZenLib)
include_directories(lib/ZenLib)
	# Temporarily disabled - cpgf breaks with v8.
	# add_subdirectory(lib/v8)
	# include_directories(lib/v8/include)
add_subdirectory(lib/lua)
include_directories(lib/lua/src)
include_directories(lib/lua/etc)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/lib/lua) #luaconf.h generated from lua cmake file.
add_subdirectory(lib/python-cmake-buildsystem)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/lib/Python-2.7.6/Include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/lib/python-cmake-buildsystem/bin) # generated from python cmake file.
add_subdirectory(lib/cpgf)
include_directories(lib/cpgf/include)
include_directories(lib/json)
include_directories(lib/tinydir)
include_directories(src)

#Server
file(GLOB serverSources
	"src/Server/*.cpp"
	"src/Server/*.hpp"
	"src/Server/ScriptController/*.cpp"
	"src/Server/ScriptController/*.hpp"
	"src/Server/Utils/*.cpp"
	"src/Server/Utils/*.hpp"
	"src/Server/WorldObjects/*.cpp"
	"src/Server/WorldObjects/*.hpp"
	"src/Shared/*.cpp"
	"src/Shared/*.hpp"
	"src/Shared/GameObjects/*.cpp"
	"src/Shared/GameObjects/*.hpp"
	"src/Shared/Types/*.cpp"
	"src/Shared/Types/*.hpp"
	"src/Shared/WorldObjects/*.cpp"
	"src/Shared/WorldObjects/*.hpp"
	"src/Shared/WorldObjects/Instances/*.cpp"
	"src/Shared/WorldObjects/Instances/*.hpp"
	"src/Shared/WorldObjects/WorldGlobals/*.cpp"
	"src/Shared/WorldObjects/WorldGlobals/*.hpp"
)

# Build commands server
message("Will build server.")
add_executable(server ${serverSources})
target_link_libraries(server RakNetLibStatic liblua libpython-shared libCpgf utils )

# Dirty hack for libpython shared lib not moved automatically by python cmake project.
if(UNIX)
	set(PYTHON_OUT_SHARED_LIB ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib/python-cmake-buildsystem/lib/libpython2.7.so)
else()
	set(PYTHON_OUT_SHARED_LIB ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib/python-cmake-buildsystem/lib/python2.7.dll)
endif(UNIX)
add_custom_command(TARGET server
		   PRE_LINK
		   COMMAND ${CMAKE_COMMAND} -E copy ${PYTHON_OUT_SHARED_LIB} ${CMAKE_CURRENT_BINARY_DIR})

# Build commands client (Windows only)
if(MSVC)
  message("Will build client.")
else()
  message("Client on Gothic2 base cannot be built on Linux systems. Sorry. msvc compiler required.")
endif()
