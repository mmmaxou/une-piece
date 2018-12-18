#ifndef PROGRAM_UP_HPP__
#define PROGRAM_UP_HPP__

#pragma once

#include <map>

#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

using namespace glimac;

namespace UP
{

/**
 * @brief Data structure for the Shader an Asset
 *
 */
struct AssetProgramMulti
{
  Program _Program;

  GLint uMVPMatrix;
  GLint uMVMatrix;
  GLint uNormalMatrix;
  std::map<std::string, GLint> uMapTextures;

  AssetProgramMulti(const FilePath &applicationPath)
      : _Program(loadProgram(
            applicationPath.dirPath() + "shaders/3D.vs.glsl",
            applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl"))
  {
    uMVPMatrix = glGetUniformLocation(_Program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(_Program.getGLId(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(_Program.getGLId(), "uNormalMatrix");

    // Textures
    GLint uTexture_diffuse1;
    GLint uTexture_specular1;
    uTexture_diffuse1 = glGetUniformLocation(_Program.getGLId(), "uTexture_diffuse1");
    uTexture_specular1 = glGetUniformLocation(_Program.getGLId(), "uTexture_specular1");
    uMapTextures.insert(std::pair<std::string, GLint>(std::string("uTexture_diffuse1"), uTexture_diffuse1));
    uMapTextures.insert(std::pair<std::string, GLint>(std::string("uTexture_specular1"), uTexture_specular1));
  }
};

/**
 * @brief Data structure for the Shader an Asset
 *
 */
struct AssetProgram
{
  Program _Program;

  GLint uMVPMatrix;
  GLint uMVMatrix;
  GLint uNormalMatrix;
  GLint uTextureRepeat;
  std::map<std::string, GLint> uMapTextures;

  AssetProgram(const FilePath &applicationPath)
      : _Program(loadProgram(
            applicationPath.dirPath() + "shaders/3D.vs.glsl",
            applicationPath.dirPath() + "shaders/normals.fs.glsl"))
  {
    uMVPMatrix = glGetUniformLocation(_Program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(_Program.getGLId(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(_Program.getGLId(), "uNormalMatrix");
    uTextureRepeat = glGetUniformLocation(_Program.getGLId(), "uTextureRepeat");

    // Textures
    GLint uTexture = glGetUniformLocation(_Program.getGLId(), "uTexture");
    uMapTextures.insert(std::pair<std::string, GLint>(std::string("uTexture"), uTexture));
  }
};

/**
 * @brief Data structure for the Shader of a Static Image
 *
 */
struct StaticImageProgram
{
  Program _Program;
  GLuint _uTexture;
  GLuint _uModelMatrix;

  StaticImageProgram(const FilePath &applicationPath)
      : _Program(loadProgram(
            applicationPath.dirPath() + "shaders/tex2D.vs.glsl",
            applicationPath.dirPath() + "shaders/tex2D.fs.glsl"))
  {
    _uTexture = glGetUniformLocation(_Program.getGLId(), "uTexture");
    _uModelMatrix = glGetUniformLocation(_Program.getGLId(), "uModelMatrix");
  }
};

} // namespace UP

#endif
