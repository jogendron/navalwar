#include "engine/engine.hpp"
#include "engine/path_factory.hpp"

Engine::Engine::Engine()
{
    _configuration = std::make_shared<Configuration>(
        "../etc/battleship/config.json"
    );

    _window = SDL_CreateWindow(
        _configuration->getWindowTitle().c_str(),
        _configuration->getResolution().getWidth(),
        _configuration->getResolution().getHeight(),
        SDL_WINDOW_OPENGL
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

    SDL_SetRenderVSync(_renderer, 1);
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND); // Enable alpha blending

    _resourceManager = std::make_shared<ResourceManager>(_renderer);
}

Engine::Engine::~Engine()
{
    if (_renderer)
        SDL_DestroyRenderer(_renderer);

    if (_window)
        SDL_DestroyWindow(_window);
}

void Engine::Engine::init(int argc, char * argv[])
{
    PathFactory::init(std::string(argv[0]));

    if (! SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot initialize SDL: %s\n", SDL_GetError());
        throw std::runtime_error("Cannot initialize SDL");
    }
}

void Engine::Engine::quit()
{
    SDL_Quit();
}

Engine::Engine & Engine::Engine::getInstance()
{
    static Engine instance;
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

std::shared_ptr<Engine::ResourceManager> Engine::Engine::getResourceManager()
{
    return _resourceManager;
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
                running = false;
            else
                game->processEvent(event);
        }

        // Update
        game->update();

        // Render
        SDL_RenderClear(Engine::Engine::getInstance().getRenderer());
        game->render();
        SDL_RenderPresent(Engine::Engine::getInstance().getRenderer());
    }
}