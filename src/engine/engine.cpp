#include "engine/engine.hpp"
#include "engine/path_factory.hpp"
#include <iostream>
#include <sstream>
#include <map>

static std::string storedGameName = "";

Engine::Engine::Engine(const std::string & gameName) 
{
    if (gameName.empty())
        throw std::runtime_error("Game name cannot be empty");

    std::ostringstream oss;
    oss << "../etc/" << gameName << "/config.json";
    _configuration = std::make_shared<Configuration>(gameName);

    _logger = std::make_shared<Logger>();
    setLogLevel(_configuration->getLogLevel());

    _eventBus = std::make_shared<EventBus>();

    _window = SDL_CreateWindow(
        _configuration->getWindowTitle().c_str(),
        _configuration->getResolution().getWidth(),
        _configuration->getResolution().getHeight(),
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (! _window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        throw std::runtime_error("Cannot create SDL window");
    }

    _renderer = SDL_CreateRenderer(_window, NULL);

    if (! _renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
        throw std::runtime_error("Cannot create SDL window");
    }

    SDL_SetRenderLogicalPresentation(
        _renderer,
        _configuration->getResolution().getWidth(),
        _configuration->getResolution().getHeight(),
        SDL_LOGICAL_PRESENTATION_LETTERBOX
    ); // Enable content to be stretched with letterboxing
    SDL_SetRenderVSync(_renderer, 1);
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND); // Enable alpha blending

    _resourceManager = std::make_shared<ResourceManager>(_renderer);

    _localization = std::make_shared<Localization>(
        _logger,
        gameName,
        _configuration->getLocale()
    );
}

Engine::Engine::~Engine()
{
    _resourceManager->clear();

    if (_renderer)
        SDL_DestroyRenderer(_renderer);

    if (_window)
        SDL_DestroyWindow(_window);

    TTF_Quit();
    SDL_Quit();
}

void Engine::Engine::init(int argc, char * argv[], const std::string & gameName)
{
    PathFactory::init();

    if (! SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot initialize SDL: %s\n", SDL_GetError());
        throw std::runtime_error("Cannot initialize SDL");
    }

    if (! TTF_Init())
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot initialize SDL_TTF: %s\n", SDL_GetError());
        throw std::runtime_error("Cannot initialize SDL_TTF");
    }

    storedGameName = gameName;
}

Engine::Engine & Engine::Engine::getInstance()
{
    static Engine instance(storedGameName);
    return instance;
}

SDL_Window * Engine::Engine::getWindow()
{
    return _window;
}

SDL_Renderer * Engine::Engine::getRenderer()
{
    return _renderer;
}

std::shared_ptr<Engine::Configuration> Engine::Engine::getConfiguration()
{
    return _configuration;
}

std::shared_ptr<Engine::EventBus> Engine::Engine::getEventBus()
{
    return _eventBus;
}

std::shared_ptr<Engine::Logger> Engine::Engine::getLogger()
{
    return _logger;
}

std::shared_ptr<Engine::ResourceManager> Engine::Engine::getResourceManager()
{
    return _resourceManager;
}

std::shared_ptr<Engine::Localization> Engine::Engine::getLocalization() const
{
    return _localization;
}

Uint64 Engine::Engine::getTicks()
{
    return SDL_GetTicks();
}

void Engine::Engine::run(std::shared_ptr<Game> game)
{
    bool running = true;

    while (running)
    {
        SDL_Event event;

        // Get events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            else
            {
                // Convert mouse coordinates from window to logical coordinates
                if (
                    event.type == SDL_EVENT_MOUSE_BUTTON_DOWN 
                    || event.type == SDL_EVENT_MOUSE_BUTTON_UP
                )
                {
                    float logicalX, logicalY;
                    SDL_RenderCoordinatesFromWindow(
                        _renderer, 
                        event.button.x, 
                        event.button.y, 
                        &logicalX, 
                        &logicalY
                    );
                    event.button.x = logicalX;
                    event.button.y = logicalY;
                }
                else if (event.type == SDL_EVENT_MOUSE_MOTION)
                {
                    float logicalX, logicalY;
                    SDL_RenderCoordinatesFromWindow(
                        _renderer, 
                        event.motion.x, 
                        event.motion.y, 
                        &logicalX, 
                        &logicalY
                    );
                    event.motion.x = logicalX;
                    event.motion.y = logicalY;
                }

                game->processEvent(event);
            }
        }

        // Update
        game->update();

        // Render
        SDL_RenderClear(Engine::Engine::getInstance().getRenderer());
        game->render();
        SDL_RenderPresent(Engine::Engine::getInstance().getRenderer());
    }
}

void Engine::Engine::setLogLevel(const std::string & logLevel)
{
    std::map<std::string, SDL_LogPriority> logLevels = {
        {"Critical", SDL_LOG_PRIORITY_CRITICAL},
        {"Error", SDL_LOG_PRIORITY_ERROR},
        {"Warning", SDL_LOG_PRIORITY_WARN},
        {"Information", SDL_LOG_PRIORITY_INFO},
        {"Debug", SDL_LOG_PRIORITY_DEBUG}
    };

    SDL_LogPriority sdlLogLevel = SDL_LOG_PRIORITY_ERROR;
    auto it = logLevels.find(logLevel);

    if (it != logLevels.end())
        sdlLogLevel = it->second;
    else
        std::cerr << "Unknown log level: " << sdlLogLevel << ". Defaulting to Error." << std::endl;
    
    SDL_SetLogPriority(SDL_LOG_CATEGORY_CUSTOM, sdlLogLevel);
}