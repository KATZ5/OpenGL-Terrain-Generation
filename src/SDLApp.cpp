#include "SDLApp.h"
Shaders readShaders(const std::string &vertPath, const std::string &fragPath) {
  std::string line;
  std::stringstream ss[2];
  std::ifstream vertShader(vertPath);
  std::ifstream fragShader(fragPath);
  if (!vertShader.is_open()) {
    std::cout << "Failed to open vertex shaders: " << vertPath << std::endl;

  } else {
    while (getline(vertShader, line)) {
      std::cout << line << std::endl;
      ss[0] << line << '\n';
    }
  }
  if (!fragShader.is_open()) {
    std::cout << "Failed to open fragment shaders: " << fragPath << std::endl;
  } else {
    while (getline(fragShader, line)) {

      std::cout << line << std::endl;
      ss[1] << line << '\n';
    }
  }
  return Shaders{ss[0].str(), ss[1].str()};
}
bool SDLAppInit(SDLApp &app) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "Failed to initilaize SDL: " << SDL_GetError();
    return false;
  }

  app.window = SDL_CreateWindow(app.title,
                                app.width,
                                app.height,
                                SDL_WINDOW_OPENGL);

  if (app.window == NULL) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  app.glContext = SDL_GL_CreateContext(app.window);
  SDL_GL_MakeCurrent(app.window, app.glContext);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    std::cerr << "Failed to initilaize GLAD" << std::endl;
    return false;
  }
  glViewport(0, 0, app.width, app.height);
  return true;
}

void SDLAppQuit(SDLApp &app) {
  SDL_DestroyWindow(app.window);
  SDL_GL_DestroyContext(app.glContext);
}

void mainloop(SDLApp &app) {
  float vertices[] = {
      0.5f, 0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f,
      -0.5f, 0.5f, 0.0f};

  unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0};
  // create VBO and bind it
  // create the vertext shader and compile it

  Shaders shaders = readShaders("../assets/shaders/basic.vert", "../assets/shaders/basic.frag");
  const char *vertSource = shaders.vertexShaderSource.c_str();
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertSource, NULL);
  glCompileShader(vertexShader);

  // check if vertext shader compilation was successful
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // create the fragment shader and compile it
  const char *fragSource = shaders.fragmentShaderSource.c_str();
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragSource, NULL);
  glCompileShader(fragmentShader);

  // check if fragment shader compilation was successful
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // creting the shader program
  unsigned int shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // chack if linking shader program failed
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  const int stride = 3 * sizeof(float);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (app.running) {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        app.running = false;
      }
    }

    glClearColor(0.2f, 0.5f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    SDL_GL_SwapWindow(app.window);
  }
}
