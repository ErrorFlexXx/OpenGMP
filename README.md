# OpenGMP

This project is an open source gothic 2 - the night of the raven multiplayer implementation.
Currently it's more like a draft than a working multiplayer solution.

## Building the programs
The repository has to be cloned with --recursive parameter in order to clone all referenced submodules of this project.
The build system for the server project is implemented with a tool called cmake.
OpenGMP-Server can be built on windows and linux operating systems.

### Building the server
To build the server on a linux system, the following tools have to be installed:
* git
* cmake
* build-essential
On debian based systems the software can be installed with the following command:
```
sudo apt install git cmake build-essential
```
On a windows system it's needed to have a program for CMake, Git and some build environment like VisualStudio.
Instead of calling ```make``` you want to open the generated .sln file on windows.

```
git clone https://github.com/ErrorFlexXx/OpenGMP.git
cd OpenGMP
mkdir build
cd build
cmake ..
make -j4 # Or open generated sln on windows. 4 are used threads to compile.
```

### Building the client
Currently there is only one client implementation and it's designed for the original Gothic II the night of the raven.
Therefore it has to be compiled with a msvc microsoft compiler. To create this project open the .sln project located at 
src/Client/OpenGMP-Client.

### Known issues
On Ubuntu systems there is a problem with the python2.7 packages, that causes the server to crash, if a phython script is going to be loaded.
If the program crashs with a message like: `ImportError: No module named _sysconfigdata_nd` one can place a symbolic link to solve the problem.
```bash
sudo ln -fs /usr/lib/python2.7/plat-x86_64-linux-gnu/_sysconfigdata_nd.py /usr/lib/python2.7/
```

## Special thanks to
 * A special thanks goes to the projects GUC and SumpfkrautOnline. The base structure of the project is mostly adopted from there.
 * Another one to all projects that are used as library in this project.


