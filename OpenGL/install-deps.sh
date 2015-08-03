#!/bin/sh

# Install required packages in Ubuntu:
# 1. SOIL(www.lonesock.net/soil.html) -- Load images for OpenGL Texture
# 2. glm library -- C++ library for OpenGL GLSL type-based mathematics
# 3. assimp -- 3D model import library supporting kinds of model format
# 4. glew -- OpenGL Extension Wrangler to get specific OpenGL abilities
sudo apt-get install libsoil-dev libglm-dev libassimp-dev libglew-dev

# If `apt-cache search libglfw3-dev` returns no results, go to `glfw.org` for download.
#sudo apt-get install libglfw3-dev
