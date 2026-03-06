#include "engine/path_factory.hpp"

#ifdef __APPLE__

    #include <mach-o/dyld.h>

    std::filesystem::path getExecutableDir() {
        uint32_t size = 0;
        _NSGetExecutablePath(nullptr, &size);

        std::string path(size, '\0');
        _NSGetExecutablePath(path.data(), &size);

        return std::filesystem::path(path).parent_path();
    }

#elif defined(_WIN32)

    #include <windows.h>

    std::filesystem::path getExecutableDir() {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        return std::filesystem::canonical(buffer);
    }

#else // Linux or BSD

    #include <unistd.h>
    #include <limits.h>

    std::filesystem::path getExecutableDir() {
        char buffer[PATH_MAX];
        ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer));

        return std::filesystem::path(std::string(buffer, len)).parent_path();
    }

#endif

using namespace Engine;

std::filesystem::path PathFactory::_exeParentDirectory;

void PathFactory::init()
{
    _exeParentDirectory = getExecutableDir();
}

std::filesystem::path PathFactory::createPath(const std::string & path)
{
    return _exeParentDirectory /
        std::filesystem::path(path);
}