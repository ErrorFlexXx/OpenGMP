#pragma once

#include <string>
#include "../GameObjects/staticCollection.hpp"
#include "../GameObjects/dynamicCollection.hpp"
#include "WorldGlobals/worldClock.hpp"
#include "WorldGlobals/weatherController.hpp"
#include "WorldGlobals/barrierController.hpp"

//Forwared declarations:
class WorldClock;
class WeatherController;
class BarrierController;
class BaseVob;

class World
{
public:
    virtual ~World();

    WorldClock &GetWorldClock();
    WeatherController &GetWeatherCtrl();
    BarrierController &GetBarrierCtrl();
    std::string GetWorldname() const;
    virtual bool AddVob(BaseVob *vob);
    virtual bool RemoveVob(BaseVob *vob);

protected:
    World(const std::string worldName, const std::string worldFilename);

private:
    WorldClock m_worldClock;
    WeatherController m_weatherCtrl;
    BarrierController m_barrierCtrl;
    DynamicCollection <BaseVob> m_vobsDynamic;
    StaticCollection <BaseVob> m_vobsById;
    std::string m_worldName;        //!< Name of the world.
    std::string m_worldFilename;    //!< Filename of the world.
};
