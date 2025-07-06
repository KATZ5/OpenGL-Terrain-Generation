#pragma once
#include <SDL3/SDL.h>
#include <iostream>

#include "glad.h"
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

bool SDLAppInit(SDLApp &app);
void SDLAppQuit(SDLApp &app);
void mainloop(SDLApp &app);
