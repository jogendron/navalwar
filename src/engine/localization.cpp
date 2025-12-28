#include "engine/localization.hpp"
#include "engine/path_factory.hpp"

#include <cstdlib>
#include <locale>
#include <fstream>
#include <sstream>

#include <json/json.h>

using namespace Engine;

Localization::Localization(
    std::shared_ptr<Logger> logger,
    const std::string & gameName,
    const std::string & locale
) 
:   _logger (logger),
    _locale(locale)
{
    if (_locale.empty() || _locale == "auto")
    {
        _locale = std::locale("").name();

        if (! isSupportedLocale(gameName, _locale))
            _locale = std::getenv("LANG");

        _logger->logInformation("Detected locale \"" + _locale + "\"");  
    }
    
    if (! isSupportedLocale(gameName, _locale))
    {
        _logger->logWarning(
            "Unsupported locale \"" + _locale + "\". " +
            "Defaulting to \"" + DEFAULT_LOCALE + "\""
        );

        _locale = DEFAULT_LOCALE;
    }

    std::string translationsPath = getTranslationsFilePath(gameName, _locale);

    std::ifstream stream(
        PathFactory::createPath(translationsPath).c_str(),
        std::ios::in | std::ios::binary
    );

    Json::Value root;
    Json::CharReaderBuilder reader;
    std::string errors;
    
    if (!Json::parseFromStream(reader, stream, &root, &errors)) 
        throw std::runtime_error("Cannot parse config file");

    for (const auto& key : root.getMemberNames()) {
        _translations[key] = root[key].asString();
    }
}
   
Localization::~Localization()
{
}

const std::string Localization::getTranslation(const std::string & key) const
{
    std::string translation = "";
    auto it = _translations.find(key);
    
    if (it != _translations.end())
        translation = it->second;

    return translation;
}

const std::string Localization::getTranslationsFilePath(const std::string & gameName, const std::string & locale) const
{
    std::string language = locale;

    if (locale.length() > 2)
        language = locale.substr(0, 2);

    std::ostringstream oss;
    oss << "../share/" << gameName << "/translations/";
    oss << language << ".json";

    return oss.str();
}

bool Localization::isSupportedLocale(const std::string & gameName, const std::string & locale) const
{
    bool supported = false;

    std::string translationsPath = getTranslationsFilePath(gameName, locale);
    
    std::ifstream stream(
        PathFactory::createPath(translationsPath).c_str(),
        std::ios::in | std::ios::binary
    );

    if (stream.good())
        supported = true;

    stream.close();

    return supported;
}