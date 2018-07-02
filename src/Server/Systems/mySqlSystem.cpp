#include "mySqlSystem.hpp"
#include "utils/logger.h"
#include <cpgf/metatraits/gmetaconverter_string.h>
#include <cpgf/gmetadefine.h>
#include <cpgf/goutmain.h>
#include <cpgf/gmetaclass.h>
#include <cpgf/gvariant.h>
#include <stdarg.h>
#include <iostream>

using namespace OpenGMP::Systems;

MySqlSystem::MySqlSystem()
{}

void MySqlSystem::TestFunctionVariadic(cpgf::GMetaVariadicParam *params)
{
    LogInfo() << "TestFunctionVariadic!";
    for(size_t i = 0; i < params->paramCount; ++i)
        LogInfo() << " " << cpgf::fromVariant<int>(*(params->params[i]));
}
