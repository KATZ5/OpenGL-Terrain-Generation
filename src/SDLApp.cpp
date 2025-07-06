#include "SDLApp.h"

bool SDLAppInit(SDLApp &app) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "Failed to initilaize SDL: " << SDL_GetError();
    return 0;
  }

  app.window =
      SDL_CreateWindow(app.title, app.width, app.height, SDL_WINDOW_OPENGL);

  if (app.window == NULL) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    return 0;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  app.glContext = SDL_GL_CreateContext(app.window);
  SDL_GL_MakeCurrent(app.window, app.glContext);

  gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
  return 1;
}

void SDLAppQuit(SDLApp &app) {
  SDL_DestroyWindow(app.window);
  SDL_GL_DestroyContext(app.glContext);
}

void mainloop(SDLApp &app) {
  while (app.running) {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        app.running = false;
      }
    }
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(app.window);
  }
}
