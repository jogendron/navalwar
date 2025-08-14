#include "events/shot_result_announced.hpp"

Events::ShotResultAnnounced::ShotResultAnnounced(
    PlayerType initiator,
    const std::string & positionName, 
    ShotResult shotResult
)
:   Engine::Event(),
    _initiator(initiator),
    _positionName(positionName),
    _shotResult(shotResult)
{
}

Events::ShotResultAnnounced::~ShotResultAnnounced()
{
}

const PlayerType Events::ShotResultAnnounced::getInitiator() const
{
    return _initiator;
}

const std::string & Events::ShotResultAnnounced::getPositionName() const
{
    return _positionName;
}

const Events::ShotResult Events::ShotResultAnnounced::getShotResult() const
{
    return _shotResult;
}
