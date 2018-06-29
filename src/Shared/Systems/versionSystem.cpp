#include "versionSystem.hpp"
#include <sstream>

using namespace OpenGMP::Systems;

const Version VersionSystem::version = BuildVersionInt(0, 0, 0);

uint32_t VersionSystem::BuildVersionInt(const uint8_t &major, const uint16_t &minor, const uint16_t &patch)
{
    int versionInt = 0;

    versionInt |= ((int)major << 24);
    versionInt |= (((int)minor << 12) & 0x00FFF000);
    versionInt |= (((int)patch << 0)  & 0x00000FFF);

    return versionInt;
}

void VersionSystem::GetVersionFromInt(const uint32_t &version, uint8_t &major, uint16_t &minor, uint16_t &patch)
{
    major = uint8_t  (version >> 24);
    minor = uint16_t((version >> 12) & 0x00000FFF);
    patch = uint16_t((version >>  0) & 0x00000FFF);
}

bool VersionSystem::CheckVersionsCompatibility(const uint32_t &version1, const uint32_t &version2)
{
    uint8_t  major1, major2;
    uint16_t minor1, minor2;
    uint16_t patch1, patch2;

    GetVersionFromInt(version1, major1, minor1, patch1);
    GetVersionFromInt(version2, major2, minor2, patch2);

    return (major1 == major2 && minor1 == minor2);
}

std::string VersionSystem::GetVersionString(const uint32_t &version)
{
    std::stringstream os;
    uint8_t major;
    uint16_t minor;
    uint16_t patch;

    GetVersionFromInt(version, major, minor, patch);
    os << (int)major << "." << (int)minor << "-" << (int)patch;
    return os.str();
}
