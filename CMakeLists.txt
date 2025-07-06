cmake_minimum_required(VERSION 3.15)
project(app)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED )

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
# Use SDL3 static to keep things self-contained
# Default to static SDL3 unless overridden by user
option(SDL_STATIC "Build SDL as a static library" OFF)
option(SDL_SHARED "Build SDL as a shared library" ON)

# Optional: suppress SDL test targets
option(SDL_TEST "Build SDL test programs" OFF)

# Add SDL3
add_subdirectory(external/SDL3 EXCLUDE_FROM_ALL)
add_subdirectory(external/glm EXCLUDE_FROM_ALL)
# Sources
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(app WIN32 ${SOURCES} src/glad.c)

# Link SDL3
target_link_libraries(app SDL3::SDL3 glm::glm)

# Include SDL3 headers
target_include_directories(app PRIVATE external/SDL3/include external/glm)

