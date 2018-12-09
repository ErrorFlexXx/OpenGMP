# OpenGMP

This project is an open source gothic 2 - the night of the raven multiplayer implementation.
Currently it's more like a draft than a working multiplayer solution.

## Building the programs
The repository has to be cloned with --recursive parameter in order to clone all referenced submodules of this project.
The build system for the server project is implemented with a tool called cmake.
OpenGMP-Server can be built on linux operating systems. The client has to be built on windows.

### Building the server
To build the server on a linux system, the following tools have to be installed:
* git
* cmake
* build-essential
* libssl1.0-dev
* libmysqlclient-dev
On debian based systems the software can be installed with the following command:
```
sudo apt install git cmake build-essential libssl1.0-dev libmysqlclient-dev
```
```
git clone --recursive https://github.com/ErrorFlexXx/OpenGMP.git
cd OpenGMP
mkdir build
cd build
cmake ..
make -j4 # 4 are used threads to compile.
```
Since OpenGMP has builtin encryption by default, it needs to create encryption keys on the first start.
By default OpenGMP-Server will try to create the keys itself. However, if there are any problems while creating the keys, one can set
the key directory manually with the following start parameter: `-kd` or `--key-dir` to a custom directory.

Note: All settings, which are given as parameter are saved in a configuration file of the currently logged in user.
Parameters, which are given to the application, will be remembered and be the new default for any later starts.
To create or renew keys manually, one can start the server either with `-gk` or `--generate-keys` parameter to create a new public and private key.

Note: The private key has to be kept secret, to support a basic security of the encrypted communication.


### Building the client
Currently there is only one client implementation and it's designed for the original Gothic II the night of the raven.
Therefore it has to be compiled with a msvc microsoft compiler. 

To create the project, you'll first have to compile the RakNet library. Open the project `lib/Raknet/Lib/LibStatic/LibStatic.sln` and compile a release and debug build of the project.

After this one can open the .sln project located at src/Client/OpenGMP-Client and compile it.

#### Updating or creating new translations
All texts in the project are covered in GNU GetText Strings. At runtime environment variables are read to determine, which translation file should be loaded.
The program will search for translations in the root directory (currently Gothic II)/locale/xx\_XX/LC\_MESSAGES/OpenGMP.mo, where xx stands for the letter code (e.g. de for german).
If the required translation can't be found, gettext will display the default english texts.

To update translation files or create a translation for a new language, one can install poedit. Afterwards open the *.po file and click update from source or
to create a new translation click File->New->Select Language->Extract from source.

### Building the Launcher
On windows, there can be a need to add the path to `jom.exe` from the Qt installation to the path variable.
Additionally Qt might complain about rc.exe cannot be run. In this case add the path to your windows kit (if using microsoft compoilers) to the path variable (on the left side projects -> systemenvironment). In my case the path is `C:\Program Files (x86)\Windows Kits\10\bin\10.0.15063.0\x86`.

## Scripting
Read more about scripting in the [ServerScripts](https://www.github.com/ErrorFlexXx/OpenGMP/tree/master/ServerScripts) directory.

## Known issues
### Server (Linux build):
#### python missing link
On Ubuntu systems there is a problem with the python2.7 packages, that causes the server to crash, if a phython script is going to be loaded.
If the program crashs with a message like: `ImportError: No module named _sysconfigdata_nd` one can place a symbolic link to solve the problem.
```bash
sudo ln -fs /usr/lib/python2.7/plat-x86_64-linux-gnu/_sysconfigdata_nd.py /usr/lib/python2.7/
```
#### Missing installation routine
Currently there is no installation routine for the server under linux. Because of linux is not searching required libraries in the OpenGMP-Server binary dir, we have to add the directory to the search path, to get OpenGMP-Server load the created libraries.
```
cd build # cd to directory, where OpenGMP-Server and libs are located.
export LD_LIBRARY_PATH=.
./OpenGMP-Server # Start the server.
```

## Special thanks to
 * A special thanks goes to the projects GUC and SumpfkrautOnline. The base structure of the project is mostly adopted from there.
 * Another one to all projects that are used as library in this project.


