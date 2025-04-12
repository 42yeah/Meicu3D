//+-------------------------------------------------------------------------------
//    AiryShader.cpp - Implementation - Implementation
//                     Copyleft 2025 42yeah

#include "AiryShader.hpp"

#include <fstream>
#include <sstream>

bool Shader::Compile() {
    if (mValid) {
        return true;
    }
    std::ifstream reader(mPath);
    if (!reader.good()) {
        mCompileLog = "Cannot read from file";
        return false;
    }

    std::stringstream ss;
    ss << reader.rdbuf();
    std::string src = ss.str();
    const char *szRaw = src.c_str();

    mShader = glCreateShader(mType);
    glShaderSource(mShader, 1, &szRaw, nullptr);
    glCompileShader(mShader);

    GLint compileStatus;
    glGetShaderiv(mShader, GL_COMPILE_STATUS, &compileStatus);

    char infoLog[1024] = {0};
    glGetShaderInfoLog(mShader, sizeof(infoLog), nullptr, infoLog);
    mCompileLog = infoLog;

    if (!compileStatus) {
        glDeleteShader(mShader);
        return false;
    }

    mValid = true;
    return true;
}

void Shader::Finalize() {
    if (mValid && mShader != GL_NONE) {
        glDeleteShader(mShader);
    }
    mCompileLog = "";
    mValid = false;
}
