#include "engine/configuration.hpp"
#include "engine/path_factory.hpp"

#include <fstream>
#include <sstream>
#include <vector>

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

    Json::CharReaderBuilder reader;
    std::string errors;
    
    if (!Json::parseFromStream(reader, stream, &_root, &errors)) 
        throw std::runtime_error("Cannot parse config file");
        
    stream.close();

    _windowTitle = _root["window"]["title"].asString();

    _resolution = Resolution(
        _root["window"]["resolution"]["width"].asInt(),
        _root["window"]["resolution"]["height"].asInt()
    );

    _logLevel = _root["logLevel"].asString();
    
    _locale = _root["locale"].asString();
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

const std::string Configuration::getStringValue(const std::string & key) const
{
    Json::Value value = getValue(key);
    return value.asString(); 
}

const int Configuration::getIntValue(const std::string & key) const
{
    Json::Value value = getValue(key);
    return value.asInt();
}

const Json::Value Configuration::getValue(const std::string & key) const
{
    Json::Value current = _root;
    std::string value = "";

    size_t start = 0;
    size_t end = key.find('.');
    std::string subkey;

    while (end != std::string::npos) 
    {
        subkey = key.substr(start, end - start);

        if (current.isMember(subkey))
            current = current[subkey];
        else
            throw std::runtime_error("Could not read key " + key + " from config file");
        
        start = end + 1;
        end = key.find('.', start);
    }

    subkey = key.substr(start);

    if (current.isMember(subkey))
        current = current[subkey];
    else
        throw std::runtime_error("Could not read key " + key + " from config file");

    return current;
}