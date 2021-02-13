#include "rendering/OpenGL/RenderingDeviceGL.hpp"

#include <SDL_render.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl.h>
#include <glad/glad.h>

#include "logger/Logger.hpp"
#include "rendering/OpenGL/ProgramGL.hpp"
#include "rendering/OpenGL/RenderingDeviceInfoGL.hpp"
#include "rendering/OpenGL/ShaderGL.hpp"
#include "rendering/OpenGL/ShaderManagerGL.hpp"

#include "SDL_video.h"

RenderingDeviceGL::RenderingDeviceGL(SDL_Window* window) : _window(window), _context(nullptr) {
}

bool RenderingDeviceGL::init() {
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    _context = SDL_GL_CreateContext(_window);
    if (_context == nullptr) {
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        LOG_ERROR("[RenderingDeviceGL] Could not initialize GLAD");
        return false;
    } else {
        LOG("[RenderingDeviceGL] OpenGL version %d.%d", GLVersion.major, GLVersion.minor);
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(_window, _context);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool wasSuccess = true;
    wasSuccess &= _renderingDeviceInfo.init();
    wasSuccess &= _shaderManager.init();

    int width, height;
    SDL_GetWindowSize(_window, &width, &height);
    glViewport(0, 0, width, height);

    return wasSuccess;
}

RenderingDeviceGL::~RenderingDeviceGL() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(_context);
    SDL_DestroyRenderer(_renderer);
}

void RenderingDeviceGL::preRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(_window);
    ImGui::NewFrame();

    static float r = 0;
    static float rDir = 1.0f;
    static float g = 0;
    static float gDir = 1.0f;
    static float b = 0;
    static float bDir = 1.0f;

    r += rand() % 50 == 0 ? 0.01f * rDir : 0.0f;
    g += rand() % 50 == 0 ? 0.01f * gDir : 0.0f;
    b += rand() % 50 == 0 ? 0.01f * bDir : 0.0f;

    (r >= 1.0f) ? rDir = -1.0f : ((r <= 0.0f) ? rDir = 1.0f : (void)0);
    (g >= 1.0f) ? gDir = -1.0f : ((g <= 0.0f) ? gDir = 1.0f : (void)0);
    (b >= 1.0f) ? bDir = -1.0f : ((b <= 0.0f) ? bDir = 1.0f : (void)0);

    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderingDeviceGL::postRender() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(_window);
}