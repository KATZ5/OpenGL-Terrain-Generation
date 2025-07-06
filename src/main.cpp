#include "SDLApp.h"
#include <glm/glm.hpp>

int main() {
  SDLApp app;
  if (!SDLAppInit(app)) {
    std::cerr << "Initalization failed";
    return 0;
  }
  mainloop(app);

  return 0;
}
