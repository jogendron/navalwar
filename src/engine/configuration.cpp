#include "engine/configuration.hpp"
#include "engine/path_factory.hpp"

#include <fstream>
#include <sstream>
#include <vector>
#include <json/json.h>

using namespace Engine;

Configuration::Configuration(
    const std::string & gameName
)
:   _gameName(gameName)
{
    std::ostringstream oss;
    oss << "../etc/" << gameName << "/config.json";

    std::string configPath = oss.str();

    std::ifstream stream(
        PathFactory::createPath(configPath).c_str(),
        std::ios::in | std::ios::binary
    );
    
    if (! stream.is_open())
        throw std::runtime_error("Cannot open config file");

    Json::Value root;
    Json::CharReaderBuilder reader;
    std::string errors;
    
    if (!Json::parseFromStream(reader, stream, &root, &errors)) 
        throw std::runtime_error("Cannot parse config file");

    _windowTitle = root["window"]["title"].asString();

    _resolution = Resolution(
        root["window"]["resolution"]["width"].asInt(),
        root["window"]["resolution"]["height"].asInt()
    );

    _logLevel = root["logLevel"].asString();
    
    _locale = root["locale"].asString();
}

Configuration::~Configuration()
{
}

const std::string & Configuration::getGameName() const
{
    return _gameName;
}

const std::string & Configuration::getWindowTitle() const
{
    return _windowTitle;
}

const Resolution & Configuration::getResolution() const
{
    return _resolution;
}

const std::string & Configuration::getLogLevel() const
{
    return _logLevel;
}

const std::string & Configuration::getLocale() const
{
    return _locale;
}