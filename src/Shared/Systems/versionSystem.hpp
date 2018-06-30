#pragma once
#include "../Components/version.hpp"
#include <string>

namespace OpenGMP
{
    namespace Systems
    {
        class VersionSystem
        {
        public:
            static uint32_t BuildVersionInt(const uint8_t &major, const uint16_t &minor, const uint16_t &patch);
            static void GetVersionFromInt(const uint32_t &version, uint8_t &major, uint16_t &minor, uint16_t &patch);
            static bool CheckVersionsCompatibility(const uint32_t &version1, const uint32_t &version2);
            static std::string GetVersionString(const uint32_t &version);

            static const Components::Version version;
        };
    }
}
