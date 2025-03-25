#ifndef __BATTLESHIP_ENGINE_CONFIGURATION_HPP
#define __BATTLESHIP_ENGINE_CONFIGURATION_HPP

#include "resolution.hpp"
#include <stdexcept>
#include <string>

namespace Engine
{
    class Configuration
    {
        public:
            Configuration(const std::string & path);
            ~Configuration();

            const std::string & getWindowTitle() const;
            const Resolution & getResolution() const;

        private:
            std::string _windowTitle;
            Resolution _resolution;
    };    
}

#endif