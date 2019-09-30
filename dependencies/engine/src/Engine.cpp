#include "Engine.hpp"

#include <cstdlib>
#include <ctime>

#include <SDL.h>

#include "Scene.hpp"
#include "TextureManager.hpp"


Engine::Engine() : _padding() {}// : _spriteSystem(*this), _randomMovementSystem(*this) {}
Engine::~Engine() {}

bool Engine::initialize() {
#ifdef DEBUG
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
#endif

	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "SDL_Init Error: %s", SDL_GetError());
		return false;
	}

	_window = SDL_CreateWindow("ConceptV2", 100, 100, 755, 600, SDL_WINDOW_SHOWN);
	if (_window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "SDL_CreateWindow Error: %s", SDL_GetError());
		SDL_Quit();
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr) {
		SDL_DestroyWindow(_window);
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_Quit();
		return false;
	}

	_textureManager = std::make_unique<TextureManager>();
    _eventDispatcher = std::make_unique<EventDispatcher>();

//  _entityManager.initWithCapacity(3);
//	_transformSystem.initWithCapacity(10000);
//	_spriteSystem.initWithCapacity(10000);
//	_randomMovementSystem.initWithCapacity(10000);

    _eventDispatcher->initialize();

	_textureManager->setRenderer(_renderer);
    _eventDispatcher->registerForApplicationEvents(this);

	return true;
}

void Engine::cleanup() {
    _eventDispatcher->unregisterForApplicationEvents(this);

	if(_renderer)
		SDL_DestroyRenderer(_renderer);
	if(_window)
		SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Engine::run() {
	_isRunning = true;
	_lastGetTicksTime = SDL_GetTicks();
	mainLoop();
}

void Engine::setScene(std::unique_ptr<Scene>&& scene) {
	if(_runningScene != nullptr) {
		_runningScene->onDestroy();
	}

	_runningScene = std::move(scene);

	if(_runningScene != nullptr) {
		_runningScene->attachEngine(this);
		_runningScene->onCreated();
	}
}

void Engine::mainLoop() {

	while (_isRunning) {
		const unsigned currentTime = SDL_GetTicks();
		float delta = static_cast<float>(currentTime - _lastGetTicksTime) / 1000.0f;
		_lastGetTicksTime = currentTime;

        _eventDispatcher->update();

		if (_runningScene) {
		    _runningScene->update(delta);
		}

//		_randomMovementSystem.update(delta);

		// Render Scene
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
		SDL_RenderClear(_renderer);

//		_spriteSystem.tempDraw(_renderer);

		SDL_RenderPresent(_renderer);
	}
}

void Engine::onQuit() {
    shutdown();
}

void Engine::shutdown() {
    _isRunning = false;
}
