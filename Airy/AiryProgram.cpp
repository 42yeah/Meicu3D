//+-------------------------------------------------------------------------------
//    AiryProgram.cpp - Implementation - Implementation
//                      Copyleft 2025 42yeah

#include "AiryProgram.hpp"

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
    mLinkLog = "";
    mValid = false;
}
