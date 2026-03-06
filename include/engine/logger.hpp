#ifndef __NAVALWAR_ENGINE_LOGGER_HPP
#define __NAVALWAR_ENGINE_LOGGER_HPP

#include <string>

namespace Engine
{
    class Logger
    {
        public:
            Logger();
            ~Logger();

            void logError(const std::string & message);
            void logWarning(const std::string & message);
            void logInformation(const std::string & message);
            void logDebug(const std::string & message);
    };
}

#endif