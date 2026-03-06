#ifndef __NAVALWAR_ENGINE_CONFIGURATION_HPP
#define __NAVALWAR_ENGINE_CONFIGURATION_HPP

#include "localization.hpp"
#include "resolution.hpp"

#include <memory>
#include <stdexcept>
#include <string>

namespace Engine
{
    class Configuration
    {
        public:
            Configuration(const std::string & gameName);
            ~Configuration();

            const std::string & getGameName() const;
            const std::string & getWindowTitle() const;
            const Resolution & getResolution() const;
            const std::string & getLogLevel() const;
            const std::string & getLocale() const;

        private:
            std::string _gameName;
            std::string _windowTitle;
            Resolution _resolution;
            std::string _logLevel;
            std::string _locale;
    };    
}

#endif