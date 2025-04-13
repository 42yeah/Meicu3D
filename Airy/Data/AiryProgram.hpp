//+-------------------------------------------------------------------------------
//    AiryProgram.hpp - Program wrapper for Airy - Emballage pour Program
//                      Copyleft 2025 42yeah

#pragma once

#include "../External/glad/glad.h"
#include "AiryShader.hpp"
#include "../Pervasives/AiryObject.hpp"

#include <glm/glm.hpp>
#include <cassert>
#include <optional>
#include <unordered_map>

class Program : public Object {
public:
    Program() : mValid(false), mProgram(GL_NONE), mLinkLog(), mLocationCache() {}
    ~Program() {
        Finalize();
    }

public:
    bool Link(const Ref<Shader> &vertexShader, const Ref<Shader> &fragmentShader);

    void Finalize();

    bool Valid() const {
        return mValid;
    }

    GLuint NativeHandle() const {
        return mProgram;
    }

    const std::string &LinkLog() const {
        return mLinkLog;
    }

    void Use();

public:
    bool Uniform1i(const char *szUniformName, int iVal);
    bool Uniform1f(const char *szUniformName, float fVal);
    bool Uniform2f(const char *szUniformName, const glm::vec2 &vec2);
    bool Uniform3f(const char *szUniformName, const glm::vec3 &vec3);
    bool Uniform4f(const char *szUniformName, const glm::vec4 &vec4);
    bool UniformMat2x2f(const char *szUniformName, const glm::mat2 &mat2);
    bool UniformMat3x3f(const char *szUniformName, const glm::mat3 &mat3);
    bool UniformMat4x4f(const char *szUniformName, const glm::mat4 &mat4);

private:
    const std::optional<GLint> &FindUniform(const char *szUniformName);

private:
    bool mValid;

    GLuint mProgram;

    std::string mLinkLog;

    std::unordered_map<const char *, std::optional<GLint> > mLocationCache;
};
