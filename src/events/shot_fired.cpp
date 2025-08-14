#include "events/shot_fired.hpp"

Events::ShotFired::ShotFired(PlayerType initiator, const std::string & positionName)
:   Engine::Event(),
    _initiator(initiator),
    _positionName(positionName)
{
}

Events::ShotFired::~ShotFired()
{
}

const PlayerType Events::ShotFired::getInitiator() const
{
    return _initiator;
}

const std::string & Events::ShotFired::getPositionName() const
{
    return _positionName;
}