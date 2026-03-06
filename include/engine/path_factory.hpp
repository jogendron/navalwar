#ifndef __NAVALWAR_ENGINE_PATH_FACTORY_HPP
#define __NAVALWAR_ENGINE_PATH_FACTORY_HPP

#include <filesystem>
#include <string>

namespace Engine
{
    class PathFactory
    {
        public:
            PathFactory() = delete;
            ~PathFactory() = delete;

            static void init();
            static std::filesystem::path createPath(const std::string & path);

        private:
            static std::filesystem::path _exeParentDirectory;
    };
}

#endif