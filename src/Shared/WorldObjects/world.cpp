#include "world.hpp"
#include "baseVob.hpp"

using namespace std;

World::World(const std::string worldName, const std::string worldFilename)
    : m_worldClock()
    , m_weatherCtrl(this)
    , m_barrierCtrl(this)
    , m_worldName(worldName)
    , m_worldFilename(worldFilename)
{

}

World::~World()
{
}

WorldClock &World::GetWorldClock()
{
    return m_worldClock;
}

WeatherController &World::GetWeatherCtrl()
{
    return m_weatherCtrl;
}

BarrierController &World::GetBarrierCtrl()
{
    return m_barrierCtrl;
}

string World::GetWorldname() const
{
    return m_worldName;
}

bool World::AddVob(BaseVob *vob)
{
    int id; //Static collection assigned ID
    bool result;

    result = m_vobsDynamic.Add(vob, id);
    result = result && m_vobsById.Add(vob);
    return result;
}

bool World::RemoveVob(BaseVob *vob)
{
    int id = vob->GetID();

    m_vobsById.Remove(vob);
    m_vobsDynamic.Remove(id);
    return true;
}
