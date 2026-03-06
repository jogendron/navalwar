#ifndef __NAVALWAR_ENGINE_LOCALIZATION_CONFIGURATION_HPP
#define __NAVALWAR_ENGINE_LOCALIZATION_CONFIGURATION_HPP

#include "engine/logger.hpp"

#include <map>
#include <memory>
#include <string>

namespace Engine
{
    class Localization
    {
        public:
            Localization(
                std::shared_ptr<Logger> logger,
                const std::string & gameName,
                const std::string & locale
            );
            ~Localization();

            const std::string getTranslation(const std::string & key) const;

        private:
            const std::string DEFAULT_LOCALE = "en_CA.UTF-8";

            std::shared_ptr<Logger> _logger;
            std::string _locale;
            std::map<std::string, std::string> _translations;

            const std::string getTranslationsFilePath(
                const std::string & gameName, 
                const std::string & locale
            ) const;

            
            bool isSupportedLocale(const std::string & gameName, const std::string & locale) const;
    };
}

#endif