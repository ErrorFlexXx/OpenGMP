# Script interface

OpenGMP has a script interface, that loads all scripts with supported file extensions from the given script directory path.
With the usage of a meta programming library `cpgf` some C++ classes and global functions of libraries are exported to loaded scripts, to enable a script writer to act with the actual gameserver.

## Lua Scripts (*.lua)
Each script has it's own lua stack. However, it is possible to include a script into another via the `require` command.

## Python scripts (*.py)
Each python script is running in a dedicated interpreter.
This is necessary, to ensure, that defined callback in scripts don't get overwritten. Otherwise it wouldn't be possible to define two callbacks of same type in two different python scripts.

To include one python script into another you can't use the "python-way" `import` command. Imported scripts won't be able to access global functions of OpenGMP and callbacks won't get called. To workaround this missing feature `OpenGMP` implements an "C" style `#include` directive, that pastes code into another.
To use the directive you simply write `#include <relativePath>` or `#include "relativePath"` into your python script at global scope.
You have to be aware, that function/callback definitions, which are equally named, will be overwritten. So the last defined function will be the winner.