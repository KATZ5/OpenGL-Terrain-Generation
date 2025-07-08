#pragma once
#include "glad.h"
#include <SDL3/SDL.h>
#include <fstream>
#include <iostream>
#include <sstream>
typedef struct SDLApp {
  SDL_Window *window = NULL;
  SDL_GLContext glContext = NULL;
  bool running = true;
  const char *title = "OPENGL";
  int width = 800;
  int height = 600;

  ~SDLApp() {
    if (window) {
      SDL_DestroyWindow(window);
    }

    if (glContext) {
      SDL_GL_DestroyContext(glContext);
    }
  }

} SDLApp;

typedef struct Shaders {
  std::string vertexShaderSource;
  std::string fragmentShaderSource;
} Shaders;

bool SDLAppInit(SDLApp &app);
Shaders readShaders(const std::string &vertPath, const std::string &fragPath);
void SDLAppQuit(SDLApp &app);
void mainloop(SDLApp &app);
