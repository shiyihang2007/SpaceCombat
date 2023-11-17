

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "shader.h"
#include "texture.h"


// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no
// public constructor is defined.
class ResourceManager {
  public:
	// resource storage
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;
	// loads (and generates) a shader program from file loading vertex,
	// fragment (and geometry) shader's source code. If gShaderFile is not
	// nullptr, it also loads a geometry shader
	static auto LoadShader(const char *vShaderFile, const char *fShaderFile,
						   const char *gShaderFile, const std::string &name)
		-> Shader;
	// retrieves a stored sader
	static auto GetShader(const std::string &name) -> Shader;
	// loads (and generates) a texture from file
	static auto LoadTexture(const char *file, bool alpha,
							const std::string &name) -> Texture2D;
	// retrieves a stored texture
	static auto GetTexture(const std::string &name) -> Texture2D;
	// properly de-allocates all loaded resources
	static void Clear();

  private:
	// private constructor, that is we do not want any actual resource manager
	// objects. Its members and functions should be publicly available
	// (static).
	ResourceManager() {}
	// loads and generates a shader from file
	static auto loadShaderFromFile(const char *vShaderFile,
								   const char *fShaderFile,
								   const char *gShaderFile = nullptr)
		-> Shader;
	// loads a single texture from file
	static auto loadTextureFromFile(const char *file, bool alpha) -> Texture2D;
};

#endif
