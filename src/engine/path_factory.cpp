#include "engine/path_factory.hpp"

using namespace Engine;

std::filesystem::path PathFactory::_exeParentDirectory;

void PathFactory::init(const std::string & firstArgument)
{
    _exeParentDirectory = std::filesystem::path(firstArgument).parent_path();
}

std::filesystem::path PathFactory::createPath(const std::string & path)
{
    return _exeParentDirectory /
        std::filesystem::path(path);
}