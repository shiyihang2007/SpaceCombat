

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "resource_manager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Instantiate static variables
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;


auto ResourceManager::LoadShader(const char *vShaderFile,
								 const char *fShaderFile,
								 const char *gShaderFile,
								 const std::string &name) -> Shader {
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

auto ResourceManager::GetShader(const std::string &name) -> Shader {
	return Shaders[name];
}

auto ResourceManager::LoadTexture(const char *file, bool alpha,
								  const std::string &name) -> Texture2D {
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

auto ResourceManager::GetTexture(const std::string &name) -> Texture2D {
	return Textures[name];
}

void ResourceManager::Clear() {
	// (properly) delete all shaders
	for (const auto &iter : Shaders) {
		glDeleteProgram(iter.second.ID);
	}
	// (properly) delete all textures
	for (const auto &iter : Textures) {
		glDeleteTextures(1, &iter.second.ID);
	}
}

auto ResourceManager::loadShaderFromFile(const char *vShaderFile,
										 const char *fShaderFile,
										 const char *gShaderFile) -> Shader {
	// debug: 输出着色器文件路径
	//    std::cerr << "[debug] vShaderFile:" << vShaderFile << "\n";
	//    std::cerr << "[debug] fShaderFile:" << fShaderFile << "\n";
	//    std::cerr << "[debug] gShaderFile:" << (gShaderFile == nullptr ?
	//    "nullptr" : gShaderFile) << "\n"; std::cerr << "\n--
	//    ------------------------- --\n";
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try {
		// open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// if geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr) {
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	} catch (std::exception &e) {
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	const char *gShaderCode = geometryCode.c_str();
	// debug: 输出着色器代码
	//    std::cerr << "[debug] vShaderCode:" << vShaderCode << "\n";
	//    std::cerr << "[debug] fShaderCode:" << fShaderCode << "\n";
	//    std::cerr << "[debug] gShaderCode:" << gShaderCode << "\n";
	//    std::cerr << "\n-- ------------------------- --\n";
	// 2. now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode,
				   gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

auto ResourceManager::loadTextureFromFile(const char *file, bool alpha)
	-> Texture2D {
	// create texture object
	Texture2D texture;
	if (alpha) {
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// load image
	int width;
	int height;
	int nrChannels;
	unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
	// now generate texture
	texture.Generate(width, height, data);
	// and finally free image data
	stbi_image_free(data);
	return texture;
}
