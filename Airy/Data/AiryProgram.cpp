//+-------------------------------------------------------------------------------
//    AiryProgram.cpp - Implementation - Implementation
//                      Copyleft 2025 42yeah

#include "AiryProgram.hpp"

#include <spdlog/spdlog.h>
#include <glm/gtc/type_ptr.hpp>

bool Program::Link(const Ref<Shader> &vertexShader,
                   const Ref<Shader> &fragmentShader) {
    Finalize();

    vertexShader->Compile();
    fragmentShader->Compile();

    if (!vertexShader->Valid() || !fragmentShader->Valid())
        return false;

    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertexShader->NativeHandle());
    glAttachShader(mProgram, fragmentShader->NativeHandle());
    glLinkProgram(mProgram);

    char infoLog[1024] = {0};
    glGetProgramInfoLog(mProgram, sizeof(infoLog), nullptr, infoLog);
    mLinkLog = infoLog;

    GLint linkStatus;
    glGetProgramiv(mProgram, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        glDeleteProgram(mProgram);
        return false;
    }

    mValid = true;
    return true;
}

void Program::Finalize() {
    if (mValid) {
        glDeleteProgram(mProgram);
    }
    mLocationCache.clear();
    mLinkLog = "";
    mValid = false;
}

void Program::Use() {
    glUseProgram(mProgram);
}

bool Program::Uniform1i(const char *szUniformName, int iVal) {
    const std::optional<GLint> &location = FindUniform(szUniformName);
    if (!location || *location < 0)
        return false;

    glUniform1i(static_cast<GLuint>(*location), iVal);
    return true;
}

bool Program::Uniform1f(const char *szUniformName, float fVal) {
    const std::optional<GLint> &location = FindUniform(szUniformName);
    if (!location || *location < 0)
        return false;

    glUniform1f(static_cast<GLuint>(*location), fVal);
    return true;
}

bool Program::Uniform2f(const char *szUniformName, const glm::vec2 &vec2) {
    const std::optional<GLint> &location = FindUniform(szUniformName);
    if (!location || *location < 0)
        return false;

    glUniform2fv(static_cast<GLuint>(*location), 1, glm::value_ptr(vec2));
    return true;
}

bool Program::Uniform3f(const char *szUniformName, const glm::vec3 &vec3) {
    const std::optional<GLint> &location = FindUniform(szUniformName);
    if (!location || *location < 0)
        return false;

    glUniform3fv(static_cast<GLuint>(*location), 1, glm::value_ptr(vec3));
    return true;
}

bool Program::Uniform4f(const char *szUniformName, const glm::vec4 &vec4) {
    const std::optional<GLint> &location = FindUniform(szUniformName);
    if (!location || *location < 0)
        return false;

    glUniform4fv(static_cast<GLuint>(*location), 1, glm::value_ptr(vec4));
    return true;
}

bool Program::UniformMat2x2f(const char *szUniformName, const glm::mat2 &mat2) {
    const std::optional<GLint> &location = FindUniform(szUniformName);
    if (!location || *location < 0)
        return false;

    glUniformMatrix2fv(static_cast<GLuint>(*location), 1, GL_FALSE, glm::value_ptr(mat2));
    return true;
}

bool Program::UniformMat3x3f(const char *szUniformName, const glm::mat3 &mat3) {
    const std::optional<GLint> &location = FindUniform(szUniformName);
    if (!location || *location < 0)
        return false;

    glUniformMatrix3fv(static_cast<GLuint>(*location), 1, GL_FALSE, glm::value_ptr(mat3));
    return true;
}

bool Program::UniformMat4x4f(const char *szUniformName, const glm::mat4 &mat4) {
    const std::optional<GLint> &location = FindUniform(szUniformName);
    if (!location || *location < 0)
        return false;

    glUniformMatrix4fv(static_cast<GLuint>(*location), 1, GL_FALSE, glm::value_ptr(mat4));
    return true;
}

bool Program::HasUniform(const char *szUniformName) {
    std::optional<GLint> location = FindUniform(szUniformName, true);
    return (*location >= 0);
}

const std::optional<GLint> &Program::FindUniform(const char *szUniformName, bool silent) {
    std::optional<GLint> &cachedLocation = mLocationCache[szUniformName];
    if (cachedLocation) {
        // Don't bother locating again
        return cachedLocation;
    }
    cachedLocation = glGetUniformLocation(mProgram, szUniformName);
    if (!silent && *cachedLocation < 0) {
        spdlog::warn("Failed to find uniform variable: {}", szUniformName);
    }
    return cachedLocation;
}
