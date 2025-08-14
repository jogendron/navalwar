#include "engine/logger.hpp"
#include <SDL3/SDL_log.h>

Engine::Logger::Logger()
{
}

Engine::Logger::~Logger()
{
}

void Engine::Logger::logError(const std::string & message)
{
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", message.c_str());
}

void Engine::Logger::logWarning(const std::string & message)
{
    SDL_LogWarn(SDL_LOG_CATEGORY_CUSTOM, "%s", message.c_str());
}

void Engine::Logger::logInformation(const std::string & message)
{
    SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "%s", message.c_str());
}

void Engine::Logger::logDebug(const std::string & message)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_CUSTOM, "%s", message.c_str());
}