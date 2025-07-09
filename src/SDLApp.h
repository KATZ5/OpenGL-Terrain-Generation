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
  int width = 1280;
  int height = 720;

  ~SDLApp() {
    if (window) {
      SDL_DestroyWindow(window);
    }

    if (glContext) {
      SDL_GL_DestroyContext(glContext);
    }
  }

} SDLApp;

struct ShaderSources {
  std::string vertexShaderSource;
  std::string fragmentShaderSource;
};

bool SDLAppInit(SDLApp &app);
ShaderSources readShaders(const std::string &vertPath, const std::string &fragPath);
unsigned int createShaderProgram(const char *vertexSource, const char *fragmentSource);
void SDLAppQuit(SDLApp &app);
void mainloop(SDLApp &app);
